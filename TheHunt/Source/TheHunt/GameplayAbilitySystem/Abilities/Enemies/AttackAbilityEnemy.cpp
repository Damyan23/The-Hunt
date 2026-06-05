#include "AttackAbilityEnemy.h"

#include "Enemy/EnemyCharacter.h"
#include "GameplayAbilitySystem/BaseCharacter.h"
#include "Items/Weapon/MeleeWeapon.h"

UAttackAbilityEnemy::UAttackAbilityEnemy()
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UAttackAbilityEnemy::ActivateAbility(
    const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo,
    const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
        return;
    }
    Cast<AEnemyCharacter>(ActorInfo->OwnerActor)->StartStaminaRegenDelay();

    UAnimInstance* AnimInstance = ActorInfo->GetAnimInstance();
    if (!AnimInstance || !AttackMontage)
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
        return;
    }


    float Duration = AnimInstance->Montage_Play(AttackMontage);
    if (Duration > 0.f)
    {
        FOnMontageEnded EndDelegate;
        EndDelegate.BindUObject(this, &UAttackAbilityEnemy::OnMontageEnded);
        AnimInstance->Montage_SetEndDelegate(EndDelegate, AttackMontage);
    }
    else
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
    }
}

void UAttackAbilityEnemy::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, bInterrupted);
}