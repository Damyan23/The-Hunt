// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Inventory/InventorySlot.h"
#include "Items/ItemSoundData.h"
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
};
