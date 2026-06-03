// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayAbilitySystem/BaseCharacter.h"
#include "Weapon/MeleeWeapon.h"
#include "RuneBase.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class THEHUNT_API URuneBase : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Rune")
	FText RuneDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Rune")
	TObjectPtr<UTexture2D> RuneIcon;

	virtual void OnEquipped(ABaseCharacter* Owner);
	virtual void OnUnequipped(ABaseCharacter* Owner);
	virtual void OnHit(ABaseCharacter* Attacker, ABaseCharacter* Target, int8 HitCount = 0);
	virtual void OnBlock (ABaseCharacter* Blocker, ABaseCharacter* Attacker, int8 BlockCount = 0);
};
