// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "BasicAttackAbility.generated.h"

/**
 * 
 */
UCLASS()
class THEHUNT_API UBasicAttackAbility : public UGameplayAbility
{
    GENERATED_BODY()

public:
    UBasicAttackAbility();

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

    // In your attack ability header
    UPROPERTY(EditDefaultsOnly, Category = "Combo")
    TArray<TObjectPtr<UAnimMontage>> ComboAttacks; // all attacks in order

    int32 CurrentComboIndex = 0;
    bool bComboWindowOpen = false;
    bool bNextAttackQueued = false;
    FTimerHandle ComboResetTimer;

    // The effect applied to the hit target
    UPROPERTY(EditDefaultsOnly, Category = "Attack")
    TSubclassOf<UGameplayEffect> DamageEffect;
    UPROPERTY(EditDefaultsOnly, Category = "Attack")
    TSubclassOf<UGameplayEffect> StaggerEffect;

    UFUNCTION()
    void OpenComboWindow();

    UFUNCTION()
    void CloseComboWindow();

    UFUNCTION()
    void QueueNextAttack();

    UFUNCTION()
    void OnAttackFinished(UAnimMontage* Montage, bool bInterrupted);

    UFUNCTION()
    void TriggerNextAttack();

};
