// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProgressionSaveData.h"
#include "Engine/GameInstance.h"
#include "Inventory/InventorySlot.h"
#include "Items/ItemSoundData.h"
#include "Sts_Map/Nodes/MapNode.h"
#include "TheHuntGameInstance.generated.h"


class UInventoryComponent; // forward declare
/**
 * 
 */
UCLASS()
class THEHUNT_API UTheHuntGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sounds")
	UItemSoundData* ItemSoundData;

	UPROPERTY() FPlayerProgressionData SavedProgression;
	bool bHasSaved = false;

	void StoreProgression(const FPlayerProgressionData& Data) { SavedProgression = Data; bHasSaved = true; }
	FPlayerProgressionData GetProgression() const { return SavedProgression; }

	UPROPERTY() TArray<FSavedMapNode> SavedMap;
	bool bHasMapState = false;

	UPROPERTY()
	TArray<FVector2D> FoliagePoints;

	UPROPERTY()
	TArray<FVector2D> HousePoints;

	UPROPERTY()
	TArray<FVector2D> RuinPoints;

	int32 CurrentNodeIndex = -1;

	UFUNCTION()
	void ResetRun();
};
