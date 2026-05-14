// Fill out your copyright notice in the Description page of Project Settings.


#include "Sts_Map/MapGenerator.h"

#include "MathUtil.h"
#include "AnimNodes/AnimNode_SequenceEvaluator.h"
#include "CompGeom/Delaunay2.h"

void UMapGenerator::Generate(FVector2D BoardSize, float MinDistance, float SamplesBeforeRejection)
{

}

TArray<FVector2D> UMapGenerator::PoissonDiskSample(FVector2D BoundingBox, float MinDist, float SamplesBeforeRejection)
{
	Grid.Empty(); // add this
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

TArray<FVector2D> UMapGenerator::PoissonDiskSample(
	FVector2D BoundingBox,
	float MinDist,
	float SamplesBeforeRejection,
	TArray<FVector2D>& SamplePoints,
	float MinRadiusFromSample,
	TArray<TPair<FVector2D, FVector2D>> PathSegments,
	float PathClearanceRadius,
	float LargeObjectChance,
	float LargeObjectRadius,
	TArray<FVector2D>& OutLargeObjectPoints,
	float RuinChance,
	float RuinRadius,
	TArray<FVector2D>& OutRuinPoints)
{
	Grid.Empty();
	CellSize = MinDist / FMathf::Sqrt(2);

	const float GridWidth = FMathf::Ceil(BoundingBox.X / CellSize);
	const float GridHeight = FMathf::Ceil(BoundingBox.Y / CellSize);

	TArray<FVector2D> Points;
	TArray<FVector2D> SpawnPoints;

	for (int32 i = 0; i < GridWidth; i++)
	{
		TArray<int32> Column;
		for (int32 j = 0; j < GridHeight; j++)
			Column.Add(0);
		Grid.Add(Column);
	}

	for (auto& Point : SamplePoints)
		SpawnPoints.Add(Point);

	while (SpawnPoints.Num() > 0)
	{
		int32 SpawnIndex = FMath::RandRange(0, SpawnPoints.Num() - 1);
		FVector2D SpawnCenter = SpawnPoints[SpawnIndex];
		bool bCandidateAccepted = false;

		bool bIsLargeObjectCandidate = false;
		if (FMath::FRand() < LargeObjectChance)
			bIsLargeObjectCandidate = true;
		
		bool bIsRuinCandidate = false;
		if (FMath::FRand() < RuinChance && !bIsLargeObjectCandidate)
			bIsRuinCandidate = true;

		for (int32 i = 0; i < SamplesBeforeRejection; i++)
		{
			float Angle = FMath::FRand() * PI * 2;
			FVector2D Dir = FVector2D(FMath::Sin(Angle), FMath::Cos(Angle));
			FVector2D Candidate;
			float Distance = 0;

			if (SamplePoints.Contains(SpawnCenter))
			{
				Distance = MinRadiusFromSample;
			}
			else if (bIsLargeObjectCandidate)
			{
				Distance = LargeObjectRadius;
			}
			else if (bIsRuinCandidate)
			{
				Distance = RuinRadius;
			}
			else
			{
				Distance = MinDist;
			}

			
			Candidate = SpawnCenter + Dir * FMath::RandRange(Distance, Distance * 2);

			// Too close to other foliage points or out of bounds — reject
			if (!IsValid(BoundingBox, Candidate, Points, Distance)) continue;

			// Too close to any path node — reject
			bool bTooCloseToSample = false;
			for (FVector2D& Sample : SamplePoints)
			{
				float DistanceToCheck = MinRadiusFromSample;
				if (bIsLargeObjectCandidate || bIsRuinCandidate) DistanceToCheck += Distance / 2;
				if (FVector2D::Distance(Candidate, Sample) < DistanceToCheck)
				{
					bTooCloseToSample = true;
					break;
				}
			}
			if (bTooCloseToSample) continue;

			bool bTooCloseToPath = false;
			for (auto& Segment : PathSegments)
			{
				if (PointToSegmentDistance(Candidate, Segment.Key, Segment.Value) < PathClearanceRadius)
				{
					bTooCloseToPath = true;
					break;
				}
			}
			if (bTooCloseToPath) continue;

			// Too close to a large object point
			bool bTooCloseToLargeObject = false;
			for (FVector2D& LargeObj : OutLargeObjectPoints)
			{
				if (FVector2D::Distance(Candidate, LargeObj) < LargeObjectRadius)
				{
					bTooCloseToLargeObject = true;
					break;
				}
			}
			if (bTooCloseToLargeObject) continue;

			Points.Add(Candidate);
			SpawnPoints.Add(Candidate);

			if (bIsLargeObjectCandidate)
				OutLargeObjectPoints.Add(Candidate);

			if (bIsRuinCandidate)
				OutRuinPoints.Add(Candidate);

			int32 CellX = (int32)(Candidate.X / CellSize);
			int32 CellY = (int32)(Candidate.Y / CellSize);
			if (CellX < Grid.Num() && CellY < Grid[0].Num())
				Grid[CellX][CellY] = Points.Num();

			bCandidateAccepted = true;
			break;
		}

		if (!bCandidateAccepted)
			SpawnPoints.RemoveAt(SpawnIndex);
	}

	return Points;
}

float UMapGenerator::PointToSegmentDistance(FVector2D Point, FVector2D SegStart, FVector2D SegEnd)
{
	FVector2D Seg = SegEnd - SegStart;
	FVector2D ToPoint = Point - SegStart;

	float T = FVector2D::DotProduct(ToPoint, Seg) / FVector2D::DotProduct(Seg, Seg);
	T = FMath::Clamp(T, 0.f, 1.f);

	FVector2D Closest = SegStart + Seg * T;
	return FVector2D::Distance(Point, Closest);
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

TArray<int32> UMapGenerator::AStar(
	TArray<TPair<int32, int32>> Edges,
	TArray<FVector2D>& Points,
	FVector2D BoundingBox,
	TArray<int32> ForcedPoints)
{
	int StartPointIndex, EndPointIndex;
	GetStartAndEndPoint(StartPointIndex, EndPointIndex, BoundingBox, Points);

	if (StartPointIndex == -1 || EndPointIndex == -1)
		return {};

	TMap<int32, TArray<int32>> Graph = GetNodesAndTheirConnections(Edges);

	TArray<int32> Waypoints;
	Waypoints.Add(StartPointIndex);
	Waypoints.Append(ForcedPoints);
	Waypoints.Add(EndPointIndex);

	TArray<int32> FullPath;

	auto MakeEdge = [](int32 A, int32 B)
		{
			return TPair<int32, int32>(FMath::Min(A, B), FMath::Max(A, B));
		};

	for (int32 w = 0; w < Waypoints.Num() - 1; w++)
	{
		int32 SegmentStart = Waypoints[w];
		int32 SegmentEnd = Waypoints[w + 1];

		TArray<int32> OpenList;
		TSet<int32> ClosedSet;
		TMap<int32, int32> CameFrom;
		TMap<int32, float> GCost;

		OpenList.Add(SegmentStart);
		GCost.Add(SegmentStart, 0.f);
		CameFrom.Add(SegmentStart, SegmentStart);

		bool bReachedEnd = false;

		while (OpenList.Num() > 0)
		{
			int32 Current = -1;
			float BestF = FLT_MAX;

			for (int32 Node : OpenList)
			{
				float G = GCost[Node];
				float H = FVector2D::Distance(Points[Node], Points[SegmentEnd]);
				float F = G + H;

				if (F < BestF)
				{
					BestF = F;
					Current = Node;
				}
			}

			if (Current == SegmentEnd)
			{
				bReachedEnd = true;
				break;
			}

			OpenList.Remove(Current);
			ClosedSet.Add(Current);

			if (!Graph.Contains(Current)) continue;

			for (int32 Neighbor : Graph[Current])
			{
				if (ClosedSet.Contains(Neighbor)) continue;

				float Distance = FVector2D::Distance(Points[Current], Points[Neighbor]);

				TPair<int32, int32> Edge = MakeEdge(Current, Neighbor);
				float Usage = EdgeUsage.Contains(Edge) ? EdgeUsage[Edge] : 0.f;

				float Penalty = Usage * 25.f;         // smaller
				float Attraction = FirstPathNodes.Contains(Neighbor) ? 40.f : 0.f; // MUCH smaller

				float NewG = GCost[Current]
					+ Distance
					+ Penalty
					- Attraction;

				if (!GCost.Contains(Neighbor) || NewG < GCost[Neighbor])
				{
					GCost.Add(Neighbor, NewG);
					CameFrom.Add(Neighbor, Current);

					if (!OpenList.Contains(Neighbor))
						OpenList.Add(Neighbor);
				}
			}
		}

		if (!bReachedEnd)
			return {};

		TArray<int32> Segment;
		int32 Current = SegmentEnd;

		while (Current != SegmentStart)
		{
			Segment.Insert(Current, 0);
			Current = CameFrom[Current];
		}

		if (w == 0)
			Segment.Insert(SegmentStart, 0);

		FullPath.Append(Segment);
	}

	return FullPath;
}

void UMapGenerator::GetStartAndEndPoint(int32& StartPointIndex, int32& EndPointIndex, FVector2D BoundingBox, TArray<FVector2D>& Points)
{
	StartPointIndex = -1;
	EndPointIndex = -1;

	const int32 GridWidth = FMath::CeilToInt(BoundingBox.X / CellSize);
	const int32 GridHeight = FMath::CeilToInt(BoundingBox.Y / CellSize);

	int32 StartingCell = Grid[GridWidth / 2][GridHeight - 1];

	if (StartingCell != 0)
	{
		StartPointIndex = StartingCell - 1;
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
					StartPointIndex = PointIndex;
				}
			}

			if (RightX < GridWidth && Grid[RightX][GridHeight - 1] != 0)
			{
				int32 PointIndex = Grid[RightX][GridHeight - 1] - 1;
				float Dist = FVector2D::Distance(Points[PointIndex], CenterTop);
				if (Dist < ClosestDistance)
				{
					ClosestDistance = Dist;
					StartPointIndex = PointIndex;
				}
			}

			float NextCellDist = (i + 1) * CellSize;
			if (StartPointIndex != -1 && NextCellDist > ClosestDistance)
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

TArray<TArray<int32>> UMapGenerator::GeneratePaths(TArray<TPair<int32, int32>> Edges, TArray<FVector2D>& Points, FVector2D BoundingBox, int32 NumPaths, int32 MinConvergencePoints, int32 MaxConvergencePoints, int32 MinRemovedPoints, int32 MaxRemovedPoints)
{
	TArray<TArray<int32>> AllPaths;
	EdgeUsage.Empty();
	FirstPathNodes.Empty();

	if (NumPaths <= 0) return AllPaths;

	TArray<TPair<int32, int32>> RemainingEdges = Edges;
	TArray<int32> ConvergencePoints;

	for (int32 p = 0; p < NumPaths; p++)
	{
		TArray<int32> Path = AStar(RemainingEdges, Points, BoundingBox, ConvergencePoints);
		if (Path.Num() == 0) break;

		AllPaths.Add(Path);

		// Pick convergence points from first path
		if (p == 0)
		{
			while (ConvergencePoints.Num() < MinConvergencePoints)
			{
				ConvergencePoints.Empty();
				for (int32 i = 1; i < Path.Num() - 1; i++)
				{
					if (ConvergencePoints.Num() >= MaxConvergencePoints) break;
					if (FMath::FRand() < 0.3f)
						ConvergencePoints.Add(Path[i]);
				}
			}
		}

		// Count eligible nodes before attempting removal
		TArray<int32> EligibleNodes;
		for (int32 i = 1; i < Path.Num() - 1; i++)
			if (!ConvergencePoints.Contains(Path[i]))
				EligibleNodes.Add(Path[i]);

		TSet<int32> NodesToRemove;

		if (EligibleNodes.Num() >= MinRemovedPoints)
		{
			while (NodesToRemove.Num() < MinRemovedPoints)
			{
				NodesToRemove.Empty();
				for (int32 Node : EligibleNodes)
				{
					if (NodesToRemove.Num() >= MaxRemovedPoints) break;
					if (FMath::FRand() < 0.4f)
						NodesToRemove.Add(Node);
				}
			}
		}
		else
		{
			// Not enough eligible nodes — remove all of them
			for (int32 Node : EligibleNodes)
				NodesToRemove.Add(Node);
		}

		RemainingEdges = RemainingEdges.FilterByPredicate([&](const TPair<int32, int32>& Edge)
			{
				return !NodesToRemove.Contains(Edge.Key) && !NodesToRemove.Contains(Edge.Value);
			});

		UE_LOG(LogTemp, Warning, TEXT("Convergence Points: %i"), ConvergencePoints.Num());
		UE_LOG(LogTemp, Warning, TEXT("Removed Points on path %i: %i"), p, NodesToRemove.Num());
	}

	return AllPaths;
}

TMap<int32, AMapNode*> UMapGenerator::BuildMapGraph(TArray<TArray<int32>>& AllPaths, TArray<FVector2D>& Points,
	UWorld* World, FVector Origin, TSubclassOf<AMapNode> NodeClass, AActor* Owner)
{
	TMap<int32, AMapNode*> MapGraph;

	for (TArray<int32>& Path : AllPaths)
	{
		for (int32 i = 0; i < Path.Num() - 1; i++)
		{
			int32 FromIndex = Path[i];
			int32 ToIndex = Path[i + 1];

			
			// Spawn From node if it doesn't exist yet
			if (!MapGraph.Contains(FromIndex))
			{
				FVector WorldPos = FVector(Points[FromIndex].X, Points[FromIndex].Y, 0.f) + Origin;
				AMapNode* Node = World->SpawnActor<AMapNode>(NodeClass, WorldPos, FRotator::ZeroRotator);
				Node->PointIndex = FromIndex;
				MapGraph.Add(FromIndex, Node);
			}

			// Spawn To node if it doesn't exist yet
			if (!MapGraph.Contains(ToIndex))
			{
				FVector WorldPos = FVector(Points[ToIndex].X, Points[ToIndex].Y, 0.f) + Origin;
				FActorSpawnParameters SpawnParameters;
				AMapNode* Node = World->SpawnActor<AMapNode>(NodeClass, WorldPos, FRotator::ZeroRotator, SpawnParameters);
				Node->PointIndex = ToIndex;
				MapGraph.Add(ToIndex, Node);
			}
			

			// Wire the connection
			AMapNode* FromNode = MapGraph[FromIndex];
			AMapNode* ToNode = MapGraph[ToIndex];

			if (!FromNode->NextNodes.Contains(ToNode))
				FromNode->NextNodes.Add(ToNode);
		}
	}

	return MapGraph;
}
