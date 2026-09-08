// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/RuneBase.h"
#include "Items/WeaponType.h"
#include "Items/Weapon/CombatType.h"
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
struct FCombatSoundData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ToolTip = "Sounds played when the weapon is swung during an attack"))
    TArray<USoundBase*> SwingSounds;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TObjectPtr<USoundBase> BlockSound;
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TObjectPtr<USoundBase> ParrySound;
};

USTRUCT(BlueprintType)
struct FWeaponData
{
    GENERATED_BODY()
    FWeaponData();

    // ---- Stats ----
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
    EWeaponType WeaponType = EWeaponType::Sword;

    UPROPERTY(EditDefaultsOnly, Category = "Stats")
    EAttackType AttackType;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
    ECombatType CombatType;

    UPROPERTY(EditDefaultsOnly, Category = "Stats")
    EWeigh Weight;

    UPROPERTY(EditDefaultsOnly, Category = "Stats")
    float PhysicalAttack;

    UPROPERTY(EditDefaultsOnly, Category = "Stats")
    float MagicalAttack;

    UPROPERTY(EditDefaultsOnly, Category = "Stats")
    float StructureDamage;

    UPROPERTY(EditDefaultsOnly, Category = "Stats")
    float GuardDamageNegation;

    // ---- Runes ----
    UPROPERTY(EditDefaultsOnly, Category = "Runes")
    TArray<TObjectPtr<URuneBase>> Runes;

    // ---- Audio ----
    UPROPERTY(EditDefaultsOnly, Category = "Audio")
    FCombatSoundData SoundData;

    // ---- Animations|Movement ----
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animations|Movement")
    TObjectPtr<UAnimMontage> EnterCombat;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animations|Movement")
    TObjectPtr<UAnimMontage> ExitCombat;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animations|Movement")
    TObjectPtr<UAnimMontage> Dodge;

    // ---- Animations|Attack ----
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animations|Attack")
    TArray<TObjectPtr<UAnimMontage>> LightAttacks;

    // ---- Animations|Hit ----
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animations|Hit")
    TObjectPtr<UAnimMontage> HitF;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animations|Hit")
    TObjectPtr<UAnimMontage> HitB;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animations|Hit")
    TObjectPtr<UAnimMontage> HitL;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animations|Hit")
    TObjectPtr<UAnimMontage> HitR;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animations|Hit")
    TObjectPtr<UAnimMontage> KnockbackF;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animations|Hit")
    TObjectPtr<UAnimMontage> KnockbackB;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animations|Hit")
    TObjectPtr<UAnimMontage> Death;

    // ---- Animations|Block ----
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animations|Block")
    TArray<TObjectPtr<UAnimMontage>> Blocks;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animations|Block")
    TObjectPtr<UAnimMontage> BlockBroken;
};
