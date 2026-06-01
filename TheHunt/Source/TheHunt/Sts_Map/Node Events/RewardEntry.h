// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/ItemDefinition.h"
#include "RewardEntry.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FRewardEntry
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UItemDefinition> ItemDefinition;

    UPROPERTY(EditDefaultsOnly, meta = (ToolTip = "Higher weight = more likely to be picked"))
    float Weight = 1.f;
};