// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Inventory/InventorySlot.h"
#include "Perks/PerkSlot.h"
#include "Sts_Map/Node Events/MapEventData.h"
#include "Sts_Map/Nodes/NodeTypeData.h"
#include "ProgressionSaveData.generated.h"

class UItemDefinition;
class UPerkData;
class AMeleeWeapon;

USTRUCT(BlueprintType)
struct FPlayerProgressionData
{
    GENERATED_BODY()

public:
    UPROPERTY()
    TArray<UItemDefinition*> HotbarSlots;

    UPROPERTY()
    TArray<FPerkSlot> Perks;

    UPROPERTY()
    UItemDefinition* EquippedWeaponDef = nullptr;

    UPROPERTY()
    int EquippedWeaponSlotIndex = -1;

    UPROPERTY()
    TObjectPtr<UItemDefinition> EquippedPotion;

    UPROPERTY()
    int EquippedPotionSlotIndex = -1;

    UPROPERTY()
    TArray<FInventorySlot> InventorySlots;

    UPROPERTY()
    TMap<FName, float> Attributes;
};

USTRUCT()
struct FSavedMapNode
{
    GENERATED_BODY()
    UPROPERTY() int32 Index;
    UPROPERTY() FVector Location;
    UPROPERTY() TEnumAsByte<ENodeType> Type;
    UPROPERTY() UMapEventData* Event;       // the assigned event asset
    UPROPERTY() TArray<int32> NextIndices;  // connections by index
};