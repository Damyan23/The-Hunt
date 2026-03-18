	// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilitySystem/BasicAttackAbility.h"

UBasicAttackAbility::UBasicAttackAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

	void UBasicAttackAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData)
	{
		Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

		ApplyCost(Handle, ActorInfo, ActivationInfo);

		if (AttackMontage)
		{
			if (UAnimInstance* AnimInstance = ActorInfo->GetAnimInstance())
			{
				AnimInstance->Montage_Play(AttackMontage);
				UAbilityTask_PlayMontageAndWait* Task = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
					this,
					FName("Attack"),
					AttackMontage
				);

				Task->OnCompleted.AddDynamic(this, &UBasicAttackAbility::OnMontageCompleted);
				Task->OnInterrupted.AddDynamic(this, &UBasicAttackAbility::OnMontageCompleted);
				Task->OnCancelled.AddDynamic(this, &UBasicAttackAbility::OnMontageCompleted);
				Task->ReadyForActivation();
			}
		}
		else
		{
			EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
		}
	}

	void UBasicAttackAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
		bool bReplicateEndAbility, bool bWasCancelled)
	{
		Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	}

	void UBasicAttackAbility::OnMontageCompleted()
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
	}


