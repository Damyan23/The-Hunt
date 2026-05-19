// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Sound/SoundBase.h"
#include "ItemType.h"
#include "ItemDef_Enums/WeaponData.h"
#include "ItemSoundSet.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FGenericItemSoundSet
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<USoundBase*> PickupSounds;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<USoundBase*> DropSounds;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<USoundBase*> EquipSounds;
};

USTRUCT(BlueprintType)
struct FWeaponSoundSet
{
    GENERATED_BODY()

    // Generic fallback sounds for all weapons
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Generic")
    FGenericItemSoundSet GenericItemSounds;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Generic")
    TArray<USoundBase*> HitSounds;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Generic")
    TArray<USoundBase*> BlockSounds;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Generic")
    TArray<USoundBase*> SwingSounds;

    // Per weapon type overrides
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Overrides")
    TMap<EWeaponType, FGenericItemSoundSet> WeaponTypeOverrides;
};