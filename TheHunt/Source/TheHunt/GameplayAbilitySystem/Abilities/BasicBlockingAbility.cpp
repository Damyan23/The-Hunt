// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilitySystem/Abilities/BasicBlockingAbility.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "InputPlayer/PlayerCharacter.h"
#include "Items/Weapon/MeleeWeapon.h"

void UBasicBlockingAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                            const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                            const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    bIsExiting = false;

    UE_LOG(LogTemp, Warning, TEXT("why no wrok?"));

    CommitAbility(Handle, ActorInfo, ActivationInfo);

    if (BlockMontage)
    {
        UAnimInstance* AnimInstance = GetPlayingAnimInstance();

        if (AnimInstance)
        {
            float MontageDuration = AnimInstance->Montage_Play(BlockMontage);

            if (MontageDuration > 0.0f)
            {
                GetAbilitySystemComponentFromActorInfo()->AddLooseGameplayTag(
                    FGameplayTag::RequestGameplayTag("State.Blocking"));

                FOnMontageEnded EndDelegate;
                EndDelegate.BindUObject(this, &UBasicBlockingAbility::OnMontageEnded);
                AnimInstance->Montage_SetEndDelegate(EndDelegate, BlockMontage);
            }
            else
            {
                EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
            }
        }
        else
        {
            EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
        }
    }
}

void UBasicBlockingAbility::RequestBlockExit()
{
    if (bIsExiting) return;

    UAnimInstance* AnimInstance = GetPlayingAnimInstance();
    if (!BlockMontage || !AnimInstance || !AnimInstance->Montage_IsPlaying(BlockMontage))
    {
        EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
        return;
    }

    bIsExiting = true;
    AnimInstance->Montage_JumpToSection(FName("BlockExit"), BlockMontage);

    // Get the length of the BlockExit section and set a timer to stop the montage
    int32 SectionIndex = BlockMontage->GetSectionIndex(FName("BlockExit"));
    if (SectionIndex != INDEX_NONE)
    {
        float SectionLength = BlockMontage->GetSectionLength(SectionIndex);
        float PlayRate = AnimInstance->Montage_GetPlayRate(BlockMontage);
        float ActualDuration = (PlayRate > 0.f) ? SectionLength / PlayRate : SectionLength;

        if (UWorld* World = GetWorld())
        {
            World->GetTimerManager().SetTimer(
                BlockExitTimerHandle,
                [this]()
                {
                    UAnimInstance* Anim = GetPlayingAnimInstance();
                    if (Anim && BlockMontage)
                    {
                        Anim->Montage_Stop(0.25f, BlockMontage);
                    }
                    // Montage_Stop triggers OnMontageEnded which calls EndAbility
                },
                ActualDuration,
                false
            );
        }
    }
}

void UBasicBlockingAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
    bool bReplicateEndAbility, bool bWasCancelled)
{
    if (UWorld* World = GetWorld())
    {
        World->GetTimerManager().ClearTimer(BlockExitTimerHandle);
    }

    UAnimInstance* AnimInstance = GetPlayingAnimInstance();
    if (BlockMontage && AnimInstance && AnimInstance->Montage_IsPlaying(BlockMontage))
    {
        AnimInstance->Montage_Stop(0.25f, BlockMontage);
    }

    GetAbilitySystemComponentFromActorInfo()->RemoveLooseGameplayTag(
        FGameplayTag::RequestGameplayTag("State.Blocking"));

    bIsExiting = false;

    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UBasicBlockingAbility::OnBlockExitFinished(UAnimMontage* Montage, bool bInterrupted)
{
    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UBasicBlockingAbility::OnMontageBlendOut(UAnimMontage* Montage, bool bInterrupted)
{
}

void UBasicBlockingAbility::OnMontageCompleted()
{
	Super::EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
}

void UBasicBlockingAbility::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
    if (!bIsAbilityEnding)
        EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, bInterrupted);
}

UAnimInstance* UBasicBlockingAbility::GetPlayingAnimInstance() const
{
    if (!CurrentActorInfo) return nullptr;
    return CurrentActorInfo->GetAnimInstance();
}