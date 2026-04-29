// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapNode.h"
#include "UObject/Object.h"
#include "CompGeom/Delaunay2.h"
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
	TArray<TPair<int32, int32>> BuildDelaunayConnections(TArray<FVector2D>& Points);
	TArray<int32> GetPath(TArray<TPair<int32, int32>> Nodes, TArray<FVector2D>& Points, FVector2D BoundingBox);
	TMap <int32, TArray<int32>> GetNodesAndTheirConnections(TArray<TPair<int32, int32>> Edges);
private:
	bool IsValid(FVector2D BoundingBox, FVector2D Candidate, TArray<FVector2D>& Points, float MinDistance);

	float CellSize;
	TArray<TArray<int32>> Grid;
};
