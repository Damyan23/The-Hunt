// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilitySystem/Abilities/BasicBlockingAbility.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InputPlayer/PlayerCharacter.h"
#include "Items/Weapon/MeleeWeapon.h"

void UBasicBlockingAbility::ActivateAbility(
    const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo,
    const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(
        Handle,
        ActorInfo,
        ActivationInfo,
        TriggerEventData);

    bIsExiting = false;

    BlockMontages = Cast<ABaseCharacter>(GetAvatarActorFromActorInfo())->Weapon->ItemDefinition->WeaponData.Blocks;

    if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
        return;
    }


    if (BlockMontages.Num() < 3)
    {
        UE_LOG(LogTemp, Error, TEXT("Blocking ability requires 3 montages"));
        EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
        return;
    }

    GetAbilitySystemComponentFromActorInfo()->AddLooseGameplayTag(
        FGameplayTag::RequestGameplayTag("State.Blocking"));

    UAnimInstance* AnimInstance = GetPlayingAnimInstance();
    if (!AnimInstance)
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
        return;
    }

    float Duration = AnimInstance->Montage_Play(BlockMontages[0]);

    if (Duration > 0.f)
    {
        FOnMontageEnded EndDelegate;
        EndDelegate.BindUObject(this, &UBasicBlockingAbility::OnMontageEnded);
        AnimInstance->Montage_SetEndDelegate(EndDelegate, BlockMontages[0]);
        Cast<ABaseCharacter>(GetAvatarActorFromActorInfo())->GetCharacterMovement()->MaxWalkSpeed = 300.0f;
    }
}

void UBasicBlockingAbility::RequestBlockExit()
{
    if (bIsExiting)
        return;

    bIsExiting = true;

    UAnimInstance* AnimInstance = GetPlayingAnimInstance();
    if (!AnimInstance)
    {
        EndAbility(CurrentSpecHandle,
            CurrentActorInfo,
            CurrentActivationInfo,
            true,
            false);
        return;
    }

    AnimInstance->Montage_Stop(0.1f);

    float Duration = AnimInstance->Montage_Play(BlockMontages[2]);

    if (Duration > 0.f)
    {
        FOnMontageEnded EndDelegate;
        EndDelegate.BindUObject(this, &UBasicBlockingAbility::OnMontageEnded);
        AnimInstance->Montage_SetEndDelegate(EndDelegate, BlockMontages[2]);
    }
    else
    {
        EndAbility(CurrentSpecHandle,
            CurrentActorInfo,
            CurrentActivationInfo,
            true,
            false);
    }
}

UAnimInstance* UBasicBlockingAbility::GetPlayingAnimInstance() const
{
    const FGameplayAbilityActorInfo* ActorInfo = CurrentActorInfo; 
    if (!ActorInfo) return nullptr; return ActorInfo->GetAnimInstance();
}

void UBasicBlockingAbility::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
    if (bInterrupted) return;

    UAnimInstance* AnimInstance = GetPlayingAnimInstance();
    if (!AnimInstance) return;

    // Enter finished -> play Hold LOOPING
    if (Montage == BlockMontages[0] && !bIsExiting)
    {
        AnimInstance->Montage_Play(BlockMontages[1]);
        // Loop the hold section indefinitely
        AnimInstance->Montage_SetNextSection(
            AnimInstance->Montage_GetCurrentSection(BlockMontages[1]),
            AnimInstance->Montage_GetCurrentSection(BlockMontages[1]),
            BlockMontages[1]);
    }

    if (Montage == BlockMontages[2])
    {
        EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
    }
}

void UBasicBlockingAbility::EndAbility(
    const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo,
    bool bReplicateEndAbility,
    bool bWasCancelled)
{
    GetAbilitySystemComponentFromActorInfo()->RemoveLooseGameplayTag(
        FGameplayTag::RequestGameplayTag("State.Blocking"));

    bIsExiting = false;

    UAnimInstance* AnimInstance = GetPlayingAnimInstance();
    if (AnimInstance)
    {
        AnimInstance->Montage_Stop(0.1f);
    }

    Cast<ABaseCharacter>(GetAvatarActorFromActorInfo())->GetCharacterMovement()->MaxWalkSpeed = 600.0f;

    Super::EndAbility(
        Handle,
        ActorInfo,
        ActivationInfo,
        bReplicateEndAbility,
        bWasCancelled);
}