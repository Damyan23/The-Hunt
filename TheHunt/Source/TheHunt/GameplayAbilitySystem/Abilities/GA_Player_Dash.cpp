// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilitySystem/Abilities/GA_Player_Dash.h"
#include "Abilities/Tasks/AbilityTask_ApplyRootMotionConstantForce.h"
#include "InputPlayer/PlayerCharacter.h"

void UGA_Player_Dash::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
    const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    UE_LOG(LogTemp, Warning, TEXT("goes in here"));

    APlayerCharacter* Player = Cast<APlayerCharacter>(ActorInfo->AvatarActor.Get());
    if (!Player) { EndAbility(Handle, ActorInfo, ActivationInfo, false, false); return; }

    AMeleeWeapon* Weapon = Player->Weapon;
    if (!Weapon || !Weapon->ItemDefinition) { EndAbility(Handle, ActorInfo, ActivationInfo, false, false); return; }

    UAnimInstance* AnimInstance = ActorInfo->GetAnimInstance();
    UAnimMontage* DodgeMontage = Weapon->ItemDefinition->WeaponData.Dodge;

    if (!AnimInstance || !DodgeMontage) { EndAbility(Handle, ActorInfo, ActivationInfo, false, false); return; }

    float MontageDuration = AnimInstance->Montage_Play(DodgeMontage);
    if (MontageDuration > 0.f)
    {
        CommitAbility(Handle, ActorInfo, ActivationInfo);

        // Bind the end delegate so ability ends when montage finishes
        FOnMontageEnded EndDelegate;
        EndDelegate.BindUObject(this, &UGA_Player_Dash::OnDashFinished);
        AnimInstance->Montage_SetEndDelegate(EndDelegate, DodgeMontage);
    }
    else
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
    }
}

void UGA_Player_Dash::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGA_Player_Dash::OnDashFinished(UAnimMontage* Montage, bool bInterrupted)
{
    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
