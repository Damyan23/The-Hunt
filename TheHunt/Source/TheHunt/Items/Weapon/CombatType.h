// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatType.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ECombatType : uint8
{
    Unarmed     UMETA(DisplayName = "Unarmed"),
    LightSword  UMETA(DisplayName = "Light Sword"),
    GreatSword  UMETA(DisplayName = "Great Sword"),
    TwinSword   UMETA(DisplayName = "Twin Sword")
};