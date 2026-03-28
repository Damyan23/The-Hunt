// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilitySystem/Abilities/BasicBlockingAbility.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "InputPlayer/PlayerCharacter.h"

void UBasicBlockingAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
  const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
  const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (BlockMontage)
	{
		UAbilityTask_PlayMontageAndWait* Task = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
			this,
			FName("BlockMontage"),
			BlockMontage
		);
		Task->OnCompleted.AddDynamic(this, &UBasicBlockingAbility::OnMontageCompleted);
		Task->OnInterrupted.AddDynamic(this, &UBasicBlockingAbility::OnMontageCompleted);
		Task->OnCancelled.AddDynamic(this, &UBasicBlockingAbility::OnMontageCompleted);
		Task->ReadyForActivation();
	}
}

void UBasicBlockingAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	// Remove blocking tag
	GetAbilitySystemComponentFromActorInfo()->RemoveLooseGameplayTags(
		FGameplayTagContainer(FGameplayTag::RequestGameplayTag("State.Blocking")));

	UAnimInstance* AnimInstance = ActorInfo->GetAnimInstance();
	if (BlockMontage && AnimInstance && AnimInstance->Montage_IsPlaying(BlockMontage))
	{
		// Jump to exit section
		AnimInstance->Montage_JumpToSection(FName("BlockExit"), BlockMontage);

		// Wait for exit to finish then actually end the ability
		FOnMontageEnded EndDelegate;
		EndDelegate.BindUObject(this, &UBasicBlockingAbility::OnBlockExitFinished);
		AnimInstance->Montage_SetEndDelegate(EndDelegate, BlockMontage);

		return;
	}

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UBasicBlockingAbility::OnMontageCompleted()
{
	Super::EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
}

void UBasicBlockingAbility::OnBlockExitFinished(UAnimMontage* Montage, bool bInterrupted)
{
	// Now actually end the ability
	Super::EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
