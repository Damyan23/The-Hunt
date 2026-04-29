// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/RuneBase.h"
#include "WeaponData.generated.h"

class AMeleeWeapon;

UENUM(BlueprintType)
enum class EAttackType : uint8
{
    Slash UMETA(DisplayName = "Slash"),
    Stab  UMETA(DisplayName = "Stab")
};

UENUM(BlueprintType)
enum class EWeigh : uint8
{
    Nimble UMETA(DisplayName = "Nimble"),
    Heavy  UMETA(DisplayName = "Heavy")
};

USTRUCT(BlueprintType)
struct FWeaponData
{
    GENERATED_BODY()

    FWeaponData();

    UPROPERTY(EditDefaultsOnly)
    TArray<TObjectPtr<URuneBase>> Runes;

    UPROPERTY(EditDefaultsOnly)
    EAttackType AttackType;

    UPROPERTY(EditDefaultsOnly)
    EWeigh Weight;

    UPROPERTY(EditDefaultsOnly)
    float PhysicalAttack;

    UPROPERTY(EditDefaultsOnly)
    float  MagicalAttack;

    UPROPERTY(EditDefaultsOnly)
    float StructureDamage;

    UPROPERTY(EditDefaultsOnly)
    float GuardDamageNegation;
};

