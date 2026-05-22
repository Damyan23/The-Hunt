	// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilitySystem/BasicAttackAbility.h"

#include "InputPlayer/PlayerCharacter.h"
#include "Items/Weapon/MeleeWeapon.h"
#include "Kismet/GameplayStatics.h"

	UBasicAttackAbility::UBasicAttackAbility()
	{
		InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	}

	void UBasicAttackAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData)
	{
		Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

		//ApplyCost(Handle, ActorInfo, ActivationInfo);
        CommitAbility(Handle, ActorInfo, ActivationInfo);

		UAnimInstance* AnimInstance = ActorInfo->GetAnimInstance();
		if (!AnimInstance) return;

		ComboAttacks = Cast<ABaseCharacter>(GetAvatarActorFromActorInfo())->Weapon->ItemDefinition->WeaponData.LightAttacks;

		if (ComboAttacks.IsEmpty()) return;

		// Clamp index
		CurrentComboIndex = FMath::Clamp(CurrentComboIndex, 0, ComboAttacks.Num() - 1);
		UAnimMontage* Montage = ComboAttacks[CurrentComboIndex];

		CommitAbility(Handle, ActorInfo, ActivationInfo);

		float Duration = AnimInstance->Montage_Play(Montage);
		if (Duration > 0.f)
		{
			FOnMontageEnded EndDelegate;
			EndDelegate.BindUObject(this, &UBasicAttackAbility::OnAttackFinished);
			AnimInstance->Montage_SetEndDelegate(EndDelegate, Montage);
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

	void UBasicAttackAbility::OpenComboWindow()
	{
		bComboWindowOpen = true;
		bNextAttackQueued = false;
	}

	void UBasicAttackAbility::CloseComboWindow()
	{
		bComboWindowOpen = false;
	}

	void UBasicAttackAbility::QueueNextAttack()
	{
		if (bComboWindowOpen)
			bNextAttackQueued = true;
	}

	void UBasicAttackAbility::OnAttackFinished(UAnimMontage* Montage, bool bInterrupted)
	{
		if (bNextAttackQueued && CurrentComboIndex < ComboAttacks.Num() - 1)
		{
			CurrentComboIndex++;
			bNextAttackQueued = false;
			bComboWindowOpen = false;
			// Re-activate for next combo hit
			ActivateAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, nullptr);
		}
		else
		{
			// Reset combo
			CurrentComboIndex = 0;
			bNextAttackQueued = false;
			bComboWindowOpen = false;
			EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
		}
	}
