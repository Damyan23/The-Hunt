// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "BasicBlockingAbility.generated.h"

/**
 * 
 */
UCLASS()
class THEHUNT_API UBasicBlockingAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	bool bIsExiting = false;

	UFUNCTION()
	void OnMontageCompleted();

	void OnMontageBlendOut(UAnimMontage* Montage, bool bInterrupted);

	UFUNCTION()
	void OnBlockExitFinished(UAnimMontage* Montage, bool bInterrupted);

	UFUNCTION()
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	TObjectPtr<UAnimMontage> BlockMontage;

	// The effect applied to the hit target
	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	TSubclassOf<UGameplayEffect> BlockEffect;

	FTimerHandle BlockExitTimerHandle;

public:
	/** Called externally (e.g. by AI controller) to trigger the block exit transition. */
	void RequestBlockExit();

private:
	/** Returns the correct AnimInstance for the avatar (weapon mesh for player, body mesh for enemies). */
	UAnimInstance* GetPlayingAnimInstance() const;
};