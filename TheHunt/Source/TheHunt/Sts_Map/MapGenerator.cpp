// Fill out your copyright notice in the Description page of Project Settings.


#include "Sts_Map/MapGenerator.h"

#include "MathUtil.h"
#include "AnimNodes/AnimNode_SequenceEvaluator.h"

void UMapGenerator::Generate(FVector2D BoardSize, float MinDistance, float SamplesBeforeRejection)
{

}

TArray<FVector2D> UMapGenerator::PoissonDiskSample(FVector2D BoundingBox, float MinDist, float SamplesBeforeRejection)
{
	CellSize = MinDist / FMathf::Sqrt(2);

	const float GridWidth = FMathf::Ceil(BoundingBox.X / CellSize);
	const float GridHeight = FMathf::Ceil(BoundingBox.Y / CellSize);

	TArray<FVector2D> Points;
	TArray<FVector2D> SpawnPoints;

	// Populate array
	for (int32 i = 0; i < GridWidth; i++)
	{
		TArray<int32> Column;
		for (int32 j = 0; j < GridHeight; j++)
		{
			Column.Add(0);
		}
		Grid.Add(Column);
	}

	SpawnPoints.Add(BoundingBox / 2);
	while (SpawnPoints.Num() > 0)
	{
		int SpawnIndex = FMath::RandRange(0, SpawnPoints.Num() - 1);
		FVector2D SpawnCenter = SpawnPoints[SpawnIndex];

		bool bCandidateAccepted = false;

		for (int i = 0; i < SamplesBeforeRejection; i++)
		{
			float angle = FMath::FRand() * PI * 2;
			FVector2D Dir = FVector2D(FMath::Sin(angle), FMath::Cos(angle));

			FVector2D NewSpawnPoint = SpawnCenter + Dir * FMath::RandRange(MinDist, MinDist * 2);

			if (IsValid(BoundingBox, NewSpawnPoint, Points, MinDist))
			{
				Points.Add(NewSpawnPoint);
				SpawnPoints.Add(NewSpawnPoint);
				Grid[(int32)(NewSpawnPoint.X / CellSize)][(int32)(NewSpawnPoint.Y / CellSize)] = Points.Num();

				bCandidateAccepted = true;
				break;
			}
		}

		if (!bCandidateAccepted)
		{
			SpawnPoints.RemoveAt(SpawnIndex);
		}
	}

	return Points;
}

bool UMapGenerator::IsValid(FVector2D BoundingBox, FVector2D Candidate, TArray<FVector2D>& Points, float MinDist)
{
	if (Candidate.X >= 0 && Candidate.X < BoundingBox.X && Candidate.Y >= 0 && Candidate.Y < BoundingBox.Y)
	{
		int CellX = (int)(Candidate.X / CellSize);
		int CellY = (int)(Candidate.Y / CellSize);

		int SearchStartX = FMath::Max(0, CellX - 2);
		int SearchEndX = FMath::Min(CellX + 2, Grid.Num() - 1);
		int SearchStartY = FMath::Max(0, CellY - 2);
		int SearchEndY = FMath::Min(CellY + 2, Grid[0].Num() - 1);

		for (int x = SearchStartX; x <= SearchEndX; x++)
		{
			for (int y = SearchStartY; y <= SearchEndY; y++)
			{
				int PointIndex = Grid[x][y] - 1;
				if (PointIndex != -1)
				{
					float Distance = (Candidate - Points[PointIndex]).Length();
					if (Distance < MinDist)
					{
						return false;
					}
				}
			}
		}
		return true;
	}
	return false;
}

TArray<TPair<int32, int32>> UMapGenerator::BuildDelaunayConnections(TArray<FVector2D>& Points)
{
	TArray<UE::Math::TVector2<double>> Vertices;
	for (FVector2D& Point : Points)
		Vertices.Add(UE::Math::TVector2<double>(Point.X, Point.Y));

	UE::Geometry::FDelaunay2 Delaunay;
	bool bSuccess = Delaunay.Triangulate(Vertices, {});

	TArray<TPair<int32, int32>> Edges;
	if (!bSuccess) return Edges;

	// Triangles gives you FIndex3i — three point indices per triangle
	// Extract the 3 edges from each triangle
	TSet<TPair<int32, int32>> EdgeSet; // use a set to avoid duplicates

	for (UE::Geometry::FIndex3i& Tri : Delaunay.GetTriangles())
	{
		// Each triangle has 3 edges: AB, BC, CA
		TArray<TPair<int32, int32>> TriEdges = {
			{ FMath::Min(Tri.A, Tri.B), FMath::Max(Tri.A, Tri.B) },
			{ FMath::Min(Tri.B, Tri.C), FMath::Max(Tri.B, Tri.C) },
			{ FMath::Min(Tri.C, Tri.A), FMath::Max(Tri.C, Tri.A) }
		};

		for (auto& Edge : TriEdges)
			EdgeSet.Add(Edge);
	}

	for (auto& Edge : EdgeSet)
		Edges.Add(Edge);

	return Edges;
}

TArray<int32> UMapGenerator::GetPath(TArray<TPair<int32, int32>> Nodes, TArray<FVector2D>& Points, FVector2D BoundingBox)
{
	const int32 GridWidth = FMath::CeilToInt(BoundingBox.X / CellSize);
	const int32 GridHeight = FMath::CeilToInt(BoundingBox.Y / CellSize);

	int32 StartingCell = Grid[GridWidth / 2][GridHeight - 1];

	int32 StartingPointIndex = -1;
	int32 EndPointIndex = -1;

	if (StartingCell != 0)
	{
		StartingPointIndex = StartingCell - 1;
	}
	else
	{
		float ClosestDistance = FLT_MAX;
		FVector2D CenterTop = FVector2D(BoundingBox.X / 2.f, BoundingBox.Y);
		for (int i = 1; i < GridWidth; i++)
		{
			int LeftX = GridWidth / 2 - i;
			int RightX = GridWidth / 2 + i;

			if (LeftX >= 0 && Grid[LeftX][GridHeight - 1] != 0)
			{
				int32 PointIndex = Grid[LeftX][GridHeight - 1] - 1;
				float Dist = FVector2D::Distance(Points[PointIndex], CenterTop);
				if (Dist < ClosestDistance)
				{
					ClosestDistance = Dist;
					StartingPointIndex = PointIndex;
				}
			}

			if (RightX < GridWidth && Grid[RightX][GridHeight - 1] != 0)
			{
				int32 PointIndex = Grid[RightX][GridHeight - 1] - 1;
				float Dist = FVector2D::Distance(Points[PointIndex], CenterTop);
				if (Dist < ClosestDistance)
				{
					ClosestDistance = Dist;
					StartingPointIndex = PointIndex;
				}
			}

			float NextCellDist = (i + 1) * CellSize;
			if (StartingPointIndex != -1 && NextCellDist > ClosestDistance)
				break;
		}
	}

	// Find end point (bottom row, closest to center)
	int32 EndCell = Grid[GridWidth / 2][0];
	if (EndCell != 0)
	{
		EndPointIndex = EndCell - 1;
	}
	else
	{
		float ClosestDistance = FLT_MAX;
		FVector2D CenterBottom = FVector2D(BoundingBox.X / 2.f, 0.f);
		for (int i = 1; i < GridWidth; i++)
		{
			int LeftX = GridWidth / 2 - i;
			int RightX = GridWidth / 2 + i;

			if (LeftX >= 0 && Grid[LeftX][0] != 0)
			{
				int32 PointIndex = Grid[LeftX][0] - 1;
				float Dist = FVector2D::Distance(Points[PointIndex], CenterBottom);
				if (Dist < ClosestDistance)
				{
					ClosestDistance = Dist;
					EndPointIndex = PointIndex;
				}
			}

			if (RightX < GridWidth && Grid[RightX][0] != 0)
			{
				int32 PointIndex = Grid[RightX][0] - 1;
				float Dist = FVector2D::Distance(Points[PointIndex], CenterBottom);
				if (Dist < ClosestDistance)
				{
					ClosestDistance = Dist;
					EndPointIndex = PointIndex;
				}
			}

			float NextCellDist = (i + 1) * CellSize;
			if (EndPointIndex != -1 && NextCellDist > ClosestDistance)
				break;
		}
	}

	if (StartingPointIndex == -1 || EndPointIndex == -1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not find start or end point"));
		return {};
	}

	TArray<int32> OpenList;
	TArray<int32> ClosedList;

	TMap<int32, int32> CameFrom; // key = node, value = its parent
	TMap<int32, float> GCost; // cost to reach each node

	TMap<int32, TArray<int32>> NodesAndTheirConnections = GetNodesAndTheirConnections(Nodes);

	OpenList.Add(StartingPointIndex);
	CameFrom.Add(StartingPointIndex, 0);
	GCost.Add(StartingPointIndex, 0.f);

	while (OpenList.Num() > 0)
	{
		int CurrentNodeIndex = -1;
		float LowestFCost = FLT_MAX;
		for (int i = 0; i < OpenList.Num(); ++i)
		{
			int32 CurrentPointIndex = OpenList[i];
			float G = GCost.FindOrAdd(CurrentPointIndex);
			float H = FVector2D::Distance(Points[CurrentPointIndex], Points[EndPointIndex]);
			float F = H + G;

			if (F < LowestFCost)
			{
				LowestFCost = F;
				CurrentNodeIndex = CurrentPointIndex;
			}
		}

		if (CurrentNodeIndex == EndPointIndex) break;

		OpenList.Remove(CurrentNodeIndex);
		ClosedList.Add(CurrentNodeIndex);

		for (int32 NeighborIndex : NodesAndTheirConnections[CurrentNodeIndex])
		{
			if (ClosedList.Contains(NeighborIndex)) continue;

			float NewGCost = GCost[CurrentNodeIndex] + FVector2D::Distance(Points[CurrentNodeIndex], Points[NeighborIndex]);

			if (!GCost.Contains(NeighborIndex) || NewGCost < GCost[NeighborIndex])
			{
				GCost.Add(NeighborIndex, NewGCost);
				CameFrom.Add(NeighborIndex, CurrentNodeIndex);

				if (!OpenList.Contains(NeighborIndex))
					OpenList.Add(NeighborIndex);
			}
		}
	}

	TArray<int32> Path;
	int32 Current = EndPointIndex;

	while (CameFrom.Contains(Current) && Current != StartingPointIndex)
	{
		Path.Insert(Current, 0);
		Current = CameFrom[Current];
	}
	Path.Insert(StartingPointIndex, 0);

	return Path;
}

TMap<int32, TArray<int32>> UMapGenerator::GetNodesAndTheirConnections(TArray<TPair<int32, int32>> Edges)
{
	TMap<int32, TArray<int32>> AdjacencyList;

	for (auto& Edge : Edges)
	{
		AdjacencyList.FindOrAdd(Edge.Key).Add(Edge.Value);
		AdjacencyList.FindOrAdd(Edge.Value).Add(Edge.Key); // undirected so add both directions
	}

	return AdjacencyList;
}
