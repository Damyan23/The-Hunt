#pragma once
#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "BlockAbilityEnemy.generated.h"

UCLASS()
class THEHUNT_API UBlockAbilityEnemy : public UGameplayAbility
{
    GENERATED_BODY()

public:
    UBlockAbilityEnemy();

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

    // Called by the StateTree task when the block should end
    void RequestBlockExit();

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Block")
    TObjectPtr<UAnimMontage> BlockMontage;

    // Section names inside the single montage
    UPROPERTY(EditDefaultsOnly, Category = "Block")
    FName HoldSection = "Hold";

    UPROPERTY(EditDefaultsOnly, Category = "Block")
    FName ExitSection = "Exit";

    UFUNCTION()
    void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

    UAnimInstance* GetAnimInstance() const;

    bool bIsExiting = false;
};