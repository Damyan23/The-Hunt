// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LootTableRow.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Actor.h"
#include "Items/ItemType.h"
#include "ItemSpawner.generated.h"

UCLASS()
class THEHUNT_API ALootSpawner : public AActor
{
	GENERATED_BODY()

public:

	ALootSpawner();

	virtual void OnConstruction(const FTransform& Transform) override;
	virtual bool ShouldTickIfViewportsOnly() const override;
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Loot")
	TObjectPtr<UDataTable> ItemRegistry;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Mesh;

	/**
	 * Allowed item rarity that the spawner can generate
	 */
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Loot Filter")
	EItemRarity AllowedRarity;

	
	 //Allowed item type that the spawner can generate
	 
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Loot Filter")
	EItemType AllowedItemTypes;

	void SpawnItem();
	
private:
	UPROPERTY(VisibleAnywhere, Category = "Debug")
	TObjectPtr<UTextRenderComponent> DebugLabel;

	UPROPERTY(VisibleAnywhere, Category = "Debug")
	TObjectPtr<UStaticMeshComponent> DebugSphere;

	FColor GetRarityColor() const;
	FString GetItemTypeLabel() const;
};