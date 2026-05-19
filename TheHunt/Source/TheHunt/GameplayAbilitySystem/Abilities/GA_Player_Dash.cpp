// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilitySystem/Abilities/GA_Player_Dash.h"
#include "Abilities/Tasks/AbilityTask_ApplyRootMotionConstantForce.h"
#include "InputPlayer/PlayerCharacter.h"

void UGA_Player_Dash::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                      const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                      const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	APlayerCharacter* Player = Cast<APlayerCharacter>(ActorInfo->AvatarActor.Get());
	FVector DashDirection = Player->GetVelocity();
	DashDirection.Set(DashDirection.X, DashDirection.Y, 0);
	DashDirection = DashDirection.GetSafeNormal();
	
	//Player->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	if (DashDirection.Size() == 0)
	{
		DashDirection = -Player->GetActorForwardVector();
	}

	CommitAbility(Handle, ActorInfo, ActivationInfo);

	UAbilityTask_ApplyRootMotionConstantForce* DashTask = UAbilityTask_ApplyRootMotionConstantForce::ApplyRootMotionConstantForce(
		this, FName("Dash"), DashDirection, DashStrength, DashDuration,
		false, StrengthOverTimeCurve,
		ERootMotionFinishVelocityMode::ClampVelocity,
		FVector::ZeroVector,
		600.f,   // max velocity after dash ends
		false
	);

	DashTask->OnFinish.AddDynamic(this, &UGA_Player_Dash::OnDashFinished);
	DashTask->ReadyForActivation();
}

void UGA_Player_Dash::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGA_Player_Dash::OnDashFinished()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
