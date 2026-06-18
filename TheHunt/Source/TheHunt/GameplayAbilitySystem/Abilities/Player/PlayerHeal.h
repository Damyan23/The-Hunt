// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "PlayerHeal.generated.h"


UCLASS()
class THEHUNT_API UPlayerHeal : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UPlayerHeal();

	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		bool bReplicateEndAbility,
		bool bWasCancelled) override;

protected:
	// The GE that applies healing — magnitude set from the consumable's heal amount via SetByCaller
	UPROPERTY(EditDefaultsOnly, Category = "Heal")
	TSubclassOf<UGameplayEffect> HealEffect;

	// The SetByCaller tag the heal GE reads its magnitude from (e.g. Data.HealAmount)
	UPROPERTY(EditDefaultsOnly, Category = "Heal")
	FGameplayTag HealMagnitudeTag;

	// Tag applied while healing, so other abilities can block on it
	UPROPERTY(EditDefaultsOnly, Category = "Heal")
	FGameplayTag HealingStateTag;

	// Animation played when healing
	UPROPERTY(EditAnywhere, Category = "Healing")
	UAnimMontage* HealMontage = nullptr;

	// Called when the montage hits the "apply heal" notify
	UFUNCTION()
	void OnHealNotify(FGameplayEventData Payload);

	// Montage lifecycle
	UFUNCTION()
	void OnMontageCompleted();
	UFUNCTION()
	void OnMontageCancelled();

private:
	UPROPERTY()
	class APlayerCharacter* Player = nullptr;

	bool bHealApplied = false;
};