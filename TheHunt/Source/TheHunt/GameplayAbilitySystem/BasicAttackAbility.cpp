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

	UE_LOG(LogTemp, Warning, TEXT("numb: %i"), ComboAttacks.Num());

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
	UE_LOG(LogTemp, Warning, TEXT("=== COMBO WINDOW OPENED === Index: %d"), CurrentComboIndex);
	bComboWindowOpen = true;
}

void UBasicAttackAbility::CloseComboWindow()
{
	UE_LOG(LogTemp, Warning, TEXT("=== COMBO WINDOW CLOSED === Index: %d | Queued: %s"),
		CurrentComboIndex, bNextAttackQueued ? TEXT("YES") : TEXT("NO"));
	bComboWindowOpen = false;
}

void UBasicAttackAbility::QueueNextAttack()
{
	UE_LOG(LogTemp, Warning, TEXT("=== QUEUE NEXT ATTACK === Window Open: %s"),
		bComboWindowOpen ? TEXT("YES") : TEXT("NO"));
	if (bComboWindowOpen)
		bNextAttackQueued = true;
}

void UBasicAttackAbility::OnAttackFinished(UAnimMontage* Montage, bool bInterrupted)
{
	UE_LOG(LogTemp, Warning, TEXT("=== ATTACK FINISHED === Index: %d | Interrupted: %s"),
		CurrentComboIndex, bInterrupted ? TEXT("YES") : TEXT("NO"));
	CurrentComboIndex = 0;
	bNextAttackQueued = false;
	bComboWindowOpen = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UBasicAttackAbility::TriggerNextAttack()
{
	if (!bNextAttackQueued || CurrentComboIndex >= ComboAttacks.Num() - 1) return;

	UAnimInstance* AnimInstance = CurrentActorInfo->GetAnimInstance();
	if (!AnimInstance) return;

	UAnimMontage* PreviousMontage = ComboAttacks[CurrentComboIndex];

	CurrentComboIndex++;
	bNextAttackQueued = false;
	bComboWindowOpen = false;

	UAnimMontage* NextMontage = ComboAttacks[CurrentComboIndex];
	if (!NextMontage) return;

	// Clear end delegate on previous montage BEFORE stopping it
	FOnMontageEnded EmptyDelegate;
	AnimInstance->Montage_SetEndDelegate(EmptyDelegate, PreviousMontage);

	// Now stop it safely
	AnimInstance->Montage_Stop(0.1f, PreviousMontage);

	float Duration = AnimInstance->Montage_Play(NextMontage);
	if (Duration > 0.f)
	{
		FOnMontageEnded EndDelegate;
		EndDelegate.BindUObject(this, &UBasicAttackAbility::OnAttackFinished);
		AnimInstance->Montage_SetEndDelegate(EndDelegate, NextMontage);
	}
}
