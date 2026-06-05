#pragma once
#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AttackAbilityEnemy.generated.h"

UCLASS()
class THEHUNT_API UAttackAbilityEnemy : public UGameplayAbility
{
    GENERATED_BODY()

public:
    UAttackAbilityEnemy();

    virtual void ActivateAbility(
        const FGameplayAbilitySpecHandle Handle,
        const FGameplayAbilityActorInfo* ActorInfo,
        const FGameplayAbilityActivationInfo ActivationInfo,
        const FGameplayEventData* TriggerEventData) override;

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Attack")
    TObjectPtr<UAnimMontage> AttackMontage;

    UFUNCTION()
    void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);
};