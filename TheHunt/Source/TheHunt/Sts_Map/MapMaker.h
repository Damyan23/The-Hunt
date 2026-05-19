// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Nodes/MapNode.h"
#include "Nodes/MapNodeConnectionWidget.h"
#include "Nodes/MapNodeData.h"
#include "Engine/StaticMeshActor.h"
#include "Components/SplineMeshComponent.h"
#include "CableComponent.h"
#include "MapMaker.generated.h"

UCLASS()
class THEHUNT_API AMapMaker : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMapMaker();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void ClearMap();

	// Header
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	FVector2D BoardSize = FVector2D(1000.f, 1000.f);

	UPROPERTY(EditAnywhere, Category = "Path")
	float MinDistPath = 50.f;

	UPROPERTY(EditAnywhere, Category = "Path")
	float SamplesBeforeRejectionPath = 30.f;

	UPROPERTY(EditAnywhere, Category = "Foliage")
	float MinDistFoliage = 50.f;

	UPROPERTY(EditAnywhere, Category = "Foliage")
	float SamplesBeforeRejectionFoliage = 30.f;

	UPROPERTY(EditAnywhere, Category = "Foliage")
	float MinDistToExistingFoliage = 50.f;

	UPROPERTY(EditAnywhere, Category = "Foliage")
	float PathClearanceRadius = 50.f;
	
	UPROPERTY(EditAnywhere, Category = "Houses")
	float SpawnChanceHouses = 0.05f;
	UPROPERTY(EditAnywhere, Category = "Houses")
	float ClearanceRadiusHouses = 300.f;

	UPROPERTY(EditAnywhere, Category = "Ruins")
	float SpawnChanceRuins = 0.05f;
	UPROPERTY(EditAnywhere, Category = "Ruins")
	float ClearanceRadiusRuins= 300.f;

	UPROPERTY(EditAnywhere, Category = "Path")
	TSubclassOf<AActor> SplinePathActorClass;

	UPROPERTY()
	TArray<AActor*> SpawnedPathActors;

	UFUNCTION(CallInEditor, Category = "Map")
	void Regenerate();

	UFUNCTION()
	void SpawnEnvironment(TArray<FVector2D>& SpawnPoints, TArray<FVector2D>& HousePoints, TArray<FVector2D>& RuinPoints);

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMapNodeData* NodeEventData;

	// MapMaker.h
	UPROPERTY(EditAnywhere)
	TSubclassOf<UMapNodeConnectionsWidget> ConnectionsWidgetClass;

	UPROPERTY()
	UMapNodeConnectionsWidget* ConnectionsWidget;
};
