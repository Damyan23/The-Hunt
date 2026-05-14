// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemSoundSet.h"
#include "ItemType.h"
#include "WeaponType.h"
#include "Engine/DataAsset.h"
#include "Kismet/GameplayStatics.h"
#include "Items/ItemDefinition.h"
#include "ItemSoundData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class THEHUNT_API UItemSoundData : public UDataAsset
{
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Sounds")
    FWeaponSoundSet WeaponSounds;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Sounds")
    TMap<EItemType, FGenericItemSoundSet> ItemSounds;

    // Gets weapon inventory sounds - uses override if exists, falls back to generic
    UFUNCTION(BlueprintCallable)
    TArray<USoundBase*> GetPickupSounds(UItemDefinition* ItemDef);

    UFUNCTION(BlueprintCallable)
    TArray<USoundBase*> GetEquipSounds(UItemDefinition* ItemDef);

    UFUNCTION(BlueprintCallable)
    TArray<USoundBase*> GetDropSounds(UItemDefinition* ItemDef);

    UFUNCTION(BlueprintCallable)
    void PlayRandomSoundAtLocation(const TArray<USoundBase*>& Sounds, UWorld* World, FVector Location);

    UFUNCTION(BlueprintCallable)
    void PlayRandomSound2D(const TArray<USoundBase*>& Sounds, UObject* WorldContext, float StartTime = 0);
};