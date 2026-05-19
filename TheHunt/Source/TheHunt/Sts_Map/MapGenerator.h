// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/MapNode.h"
#include "UObject/Object.h"
#include "MapGenerator.generated.h"

/**
 * 
 */
UCLASS()
class THEHUNT_API UMapGenerator : public UObject
{
	GENERATED_BODY()

public:

	void Generate(FVector2D BoardSize, float MinDistance, float SamplesBeforeRejection);

	TArray<FVector2D> PoissonDiskSample(FVector2D BoundingBox, float MinDist, float SamplesBeforeRejection);
	TArray<FVector2D> PoissonDiskSample(
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
		TArray<FVector2D>& OutRuinPoints);

	float PointToSegmentDistance(FVector2D Point, FVector2D SegStart, FVector2D SegEnd);

	TArray<TPair<int32, int32>> BuildDelaunayConnections(TArray<FVector2D>& Points);

	TArray<int32> AStar(TArray<TPair<int32, int32>> Edges, TArray<FVector2D>& Points, FVector2D BoundingBox, TArray<int32> ForcedPoints);

	TMap <int32, TArray<int32>> GetNodesAndTheirConnections(TArray<TPair<int32, int32>> Edges);

	TArray<TArray<int32>> GeneratePaths(TArray<TPair<int32, int32>> Edges, TArray<FVector2D>& Points, FVector2D BoundingBox, int32 NumPaths, int32 MinConvergencePoints = 2, int32 MaxConvergencePoints = 4, int32 MinRemovedPoints = 6, int32 MaxRemovedPoints = 10);

	TMap<int32, AMapNode*> BuildMapGraph(TArray<TArray<int32>>& AllPaths, TArray<FVector2D>& Points, UWorld* World, FVector Origin,TSubclassOf<AMapNode> NodeClass, AActor* Owner);

	void GetStartAndEndPoint(int32& StartPointIndex, int32& EndPointIndex, FVector2D BoundingBox, TArray<FVector2D>& Points);
private:
	bool IsValid(FVector2D BoundingBox, FVector2D Candidate, TArray<FVector2D>& Points, float MinDistance);

	float CellSize;
	TMap<TPair<int32, int32>, int32> EdgeUsage;
	TArray<TArray<int32>> Grid;
	TSet<int32> FirstPathNodes;
};
