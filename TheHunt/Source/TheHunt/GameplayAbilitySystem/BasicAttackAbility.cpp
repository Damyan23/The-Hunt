	// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilitySystem/BasicAttackAbility.h"

#include "InputPlayer/PlayerCharacter.h"

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

        if (AttackMontage)
        {
            UAnimInstance* AnimInstance = nullptr;
            APlayerCharacter* Player = Cast<APlayerCharacter>(ActorInfo->AvatarActor.Get());

            if (Player && Player->Weapon)
                AnimInstance = Player->Weapon->WeaponMesh->GetAnimInstance();
            else
                AnimInstance = ActorInfo->GetAnimInstance();

            if (AnimInstance)
            {
                float MontageDuration = AnimInstance->Montage_Play(AttackMontage);

                if (MontageDuration > 0.0f)
                {
                    FOnMontageEnded EndDelegate;
                    EndDelegate.BindUObject(this, &UBasicAttackAbility::OnMontageEnded);
                    AnimInstance->Montage_SetEndDelegate(EndDelegate, AttackMontage);
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

    void UBasicAttackAbility::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
    {
        UE_LOG(LogTemp, Warning, TEXT("Montage ended - Interrupted: %s"), bInterrupted ? TEXT("Yes") : TEXT("No"));
        EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
    }

