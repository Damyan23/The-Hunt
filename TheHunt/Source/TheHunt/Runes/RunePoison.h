// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/RuneBase.h"
#include "RunePoison.generated.h"

/**
 * 
 */
UCLASS()
class THEHUNT_API URunePoison : public URuneBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> PoisonEffect;

	UPROPERTY(EditDefaultsOnly)
	int HitsRequired = 0;

	virtual auto OnHit(ABaseCharacter* Attacker, ABaseCharacter* Target, int8 HitCount = 0) -> void override;
};
