#include "PlayerHeal.h"
#include "InputPlayer/PlayerCharacter.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "AbilitySystemComponent.h"
#include "Items/ItemDefinition.h"

UPlayerHeal::UPlayerHeal()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UPlayerHeal::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Player = Cast<APlayerCharacter>(ActorInfo->AvatarActor.Get());

	UE_LOG(LogTemp, Warning, TEXT("shouldd activate it"));

	if (!Player || !Player->HealingItem || !HealEffect)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	bHealApplied = false;

	// Mark healing state so other abilities can block on it
	if (UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get())
		ASC->AddLooseGameplayTag(HealingStateTag);

	if (!HealMontage)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	UAbilityTask_WaitGameplayEvent* HealEvent =
		UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
			this, FGameplayTag::RequestGameplayTag("Event.Heal.Apply"));
	HealEvent->EventReceived.AddDynamic(this, &UPlayerHeal::OnHealNotify);
	HealEvent->ReadyForActivation();

	// Play the montage; completion/interruption end the ability
	UAbilityTask_PlayMontageAndWait* Montage =
		UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
			this, NAME_None, HealMontage, 1.f, NAME_None, true);
	Montage->OnCompleted.AddDynamic(this, &UPlayerHeal::OnMontageCompleted);
	Montage->OnBlendOut.AddDynamic(this, &UPlayerHeal::OnMontageCompleted);
	Montage->OnInterrupted.AddDynamic(this, &UPlayerHeal::OnMontageCancelled);
	Montage->OnCancelled.AddDynamic(this, &UPlayerHeal::OnMontageCancelled);
	Montage->ReadyForActivation();
}

void UPlayerHeal::OnHealNotify(FGameplayEventData Payload)
{
	// This fires at the "gulp" frame — apply the heal now, not at activation
	if (!Player || !HealEffect || bHealApplied) return;

	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
	if (!ASC) return;

	const float HealAmount = Player->HealingItem->ConsumableData.HealAmount; // adjust field

	FGameplayEffectContextHandle Context = ASC->MakeEffectContext();
	FGameplayEffectSpecHandle Spec = ASC->MakeOutgoingSpec(HealEffect, 1.f, Context);
	if (Spec.IsValid())
	{
		Spec.Data->SetSetByCallerMagnitude(HealMagnitudeTag, HealAmount);
		ASC->ApplyGameplayEffectSpecToSelf(*Spec.Data.Get());
		bHealApplied = true;

		Player->ConsumeHealItem();
	}
}

void UPlayerHeal::OnMontageCompleted()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UPlayerHeal::OnMontageCancelled()
{
	// Interrupted before the gulp → no heal applied, item not consumed (punishing)
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}

void UPlayerHeal::EndAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility,
	bool bWasCancelled)
{
	// Always clear the healing tag when the ability ends
	if (ActorInfo && ActorInfo->AbilitySystemComponent.IsValid())
		ActorInfo->AbilitySystemComponent->RemoveLooseGameplayTag(HealingStateTag);

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}