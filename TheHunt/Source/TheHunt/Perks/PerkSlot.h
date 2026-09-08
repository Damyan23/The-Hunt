// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PerkData.h"
#include "PerkSlot.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct THEHUNT_API  FPerkSlot
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UPerkData> PerkData;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    bool bIsOccupied = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    int32 SlotIndex;
};
