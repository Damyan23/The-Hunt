// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Nodes/MapNode.h"
#include "Nodes/MapNodeConnectionWidget.h"
#include "Nodes/MapNodeData.h"

#include "MapManager.generated.h"

USTRUCT()
struct FMapGeneratorSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) FVector2D BoardSize;

	// ============================================================
	// PATHS SETTINGS
	// ============================================================
	UPROPERTY(EditAnywhere) float MinDistancePath = 100.f;
	UPROPERTY(EditAnywhere) int SamplesBeforeRejectionPath = 30;
	UPROPERTY(EditAnywhere) int NumberOfPaths = 5;
	UPROPERTY(EditAnywhere) int MinConvergencePoints = 1;
	UPROPERTY(EditAnywhere) int MaxConvergencePoints = 2;
	UPROPERTY(EditAnywhere) int MinRemovedPoints = 4;
	UPROPERTY(EditAnywhere) int MaxRemovedPoints = 8;

	// ============================================================
	// NODES SETTINGS
	// ============================================================
	UPROPERTY(EditAnywhere) float NodeClearanceRadius = 200.f;

	// ============================================================
	// FOLIAGE SETTINGS
	// ============================================================
	UPROPERTY(EditAnywhere) float MinDistFoliage = 80.f;
	UPROPERTY(EditAnywhere) float PathClearanceRadius = 150.f;
	UPROPERTY(EditAnywhere) float SamplesBeforeRejectionFoliage = 30;

	// ============================================================
	// STRUCTURES SETTINGS
	// ============================================================
	UPROPERTY(EditAnywhere) float LargeObjectSpawnChance = 0.1f;
	UPROPERTY(EditAnywhere) float LargeObjectClearanceRadius = 200.f;
	UPROPERTY(EditAnywhere) float RuinsSpawnChance = 0.05f;
	UPROPERTY(EditAnywhere) float RuinsClearanceRadius = 150.f;
};

UCLASS()
class THEHUNT_API AMapManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMapManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void ClearMap();

public:	

	UPROPERTY(EditAnywhere, Category = "Map Generation")
	FMapGeneratorSettings GeneratorSettings;
	
	UPROPERTY(EditAnywhere, Category = "Path")
	TSubclassOf<AActor> SplinePathActorClass;

	UPROPERTY()
	TArray<AActor*> SpawnedPathActors;

	UFUNCTION(CallInEditor, Category = "Map")
	void Regenerate();

	UFUNCTION()
	void SpawnEnvironment(TArray<FVector2D>& SpawnPoints, TArray<FVector2D>& HousePoints, TArray<FVector2D>& RuinPoints);

	void SetNodeTypes(TMap<int32, AMapNode*>& MapGraph, int32 StartIndex, int32 EndIndex);

	UPROPERTY(EditAnywhere)
	UStaticMesh* FoliageMesh;

	UPROPERTY(EditAnywhere, Category = "Environment")
	UStaticMesh* SmallStoneMesh;

	UPROPERTY(EditAnywhere, Category = "Environment")
	UStaticMesh* BigStoneMesh;

	UPROPERTY(EditAnywhere, Category = "Environment")
	UStaticMesh* RuinsMesh;

	UPROPERTY(EditAnywhere, Category = "Environment")
	UStaticMesh* HouseMesh;

	UPROPERTY()
	UInstancedStaticMeshComponent* FoliageISMC;

	UPROPERTY()
	UInstancedStaticMeshComponent* HouseISMC;
	UPROPERTY()
	UInstancedStaticMeshComponent* RuinsISMC;

	UPROPERTY()
	UInstancedStaticMeshComponent* SmallStoneISMC;

	UPROPERTY()
	UInstancedStaticMeshComponent* BigStoneISMC;


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AMapNode> MapNodeClass;

	UPROPERTY()
	TArray<AMapNode*> SpawnedNodes;

	UPROPERTY()
	TObjectPtr<AMapNode> StartNode;

	UPROPERTY(EditAnywhere, Category = "Map")
	TObjectPtr<UMapNodeData> NodeEventData;

	// MapMaker.h
	UPROPERTY(EditAnywhere)
	TSubclassOf<UMapNodeConnectionsWidget> ConnectionsWidgetClass;

	UPROPERTY()
	UMapNodeConnectionsWidget* ConnectionsWidget;

	TArray<AActor*> SpawnedVisualizationNodes;

	UFUNCTION(BlueprintCallable)
	void SaveMapState(TArray<FVector2D>& FoliagePoints, TArray<FVector2D>& HousePoints, TArray<FVector2D>& RuinPoints);

	// In MapManager.h
	UPROPERTY(EditAnywhere, Category = "Map")
	FRotator NodeRotation = FRotator(0.f, -90.f, 0.f); // tune to taste

private:
	void RebuildMapFromSave();
};
