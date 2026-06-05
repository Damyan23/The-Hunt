#include "GameplayAbilitySystem/Abilities/Enemies/BlockAbilityEnemy.h"
#include "AbilitySystemComponent.h"

UBlockAbilityEnemy::UBlockAbilityEnemy()
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

UAnimInstance* UBlockAbilityEnemy::GetAnimInstance() const
{
    if (!CurrentActorInfo) return nullptr;
    return CurrentActorInfo->GetAnimInstance();
}

void UBlockAbilityEnemy::ActivateAbility(
    const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo,
    const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    bIsExiting = false;

    if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
        return;
    }

    UAnimInstance* AnimInstance = GetAnimInstance();
    if (!AnimInstance || !BlockMontage)
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
        return;
    }

    // Play from the start; the montage flows enter -> hold on its own
    float Duration = AnimInstance->Montage_Play(BlockMontage);
    if (Duration <= 0.f)
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
        return;
    }

    FOnMontageEnded EndDelegate;
    EndDelegate.BindUObject(this, &UBlockAbilityEnemy::OnMontageEnded);
    AnimInstance->Montage_SetEndDelegate(EndDelegate, BlockMontage);
}

void UBlockAbilityEnemy::RequestBlockExit()
{
    if (bIsExiting) return;
    bIsExiting = true;

    UAnimInstance* AnimInstance = GetAnimInstance();
    if (!AnimInstance || !BlockMontage)
    {
        EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
        return;
    }

    AnimInstance->Montage_SetNextSection(ExitSection, NAME_None, BlockMontage);
    AnimInstance->Montage_JumpToSection(ExitSection, BlockMontage);

    // Get the length of the exit section and end the ability after it plays
    float ExitLength = BlockMontage->GetSectionLength(BlockMontage->GetSectionIndex(ExitSection));

    FTimerHandle ExitTimer;
    GetWorld()->GetTimerManager().SetTimer(ExitTimer, [this]()
        {
            EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
        }, ExitLength, false);
}

void UBlockAbilityEnemy::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
    UE_LOG(LogTemp, Warning, TEXT("Block: OnMontageEnded fired, interrupted=%d bIsExiting=%d"), bInterrupted, bIsExiting);

    if (Montage != BlockMontage) return;

    // If we were exiting, end the ability regardless of interrupted flag
    if (bIsExiting)
    {
        EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
        return;
    }

    // Otherwise (montage ended without us requesting exit), also end
    if (!bInterrupted)
    {
        EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
    }
}

void UBlockAbilityEnemy::EndAbility(
    const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo,
    bool bReplicateEndAbility,
    bool bWasCancelled)
{
    bIsExiting = false;

    UE_LOG(LogTemp, Warning, TEXT("i will kill ai"))

    UAnimInstance* AnimInstance = GetAnimInstance();
    if (AnimInstance && bWasCancelled)
    {
        AnimInstance->Montage_Stop(0.1f, BlockMontage);
    }

    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}