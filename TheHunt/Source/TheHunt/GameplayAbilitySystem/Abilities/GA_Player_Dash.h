// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameFramework/RootMotionSource.h"
#include "GA_Player_Dash.generated.h"

/**
 * 
 */
UCLASS()
class THEHUNT_API UGA_Player_Dash : public UGameplayAbility
{
	GENERATED_BODY()
	
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float DashStrength = 1000.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float DashDuration = 0.2f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UCurveFloat* StrengthOverTimeCurve;
private:
	UFUNCTION()
	void OnDashFinished();
};
