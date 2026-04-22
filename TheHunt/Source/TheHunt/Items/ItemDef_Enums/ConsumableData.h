// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ConsumableData.generated.h"

USTRUCT(BlueprintType)
struct FConsumableData
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly)
    float HealAmount = 0.f;
};
