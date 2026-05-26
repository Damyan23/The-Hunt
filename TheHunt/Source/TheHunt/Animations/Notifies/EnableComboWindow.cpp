// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/Notifies/EnableComboWindow.h"

#include "GameplayAbilitySystem/BasicAttackAbility.h"
#include "InputPlayer/PlayerCharacter.h"

void UEnableComboWindow::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(MeshComp->GetOwner());
	if (!PlayerCharacter) return;

	UAbilitySystemComponent* AbilitySystemComponent = PlayerCharacter->GetAbilitySystemComponent();
	if (!AbilitySystemComponent) return;

	if (AbilitySystemComponent->HasMatchingGameplayTag(
		FGameplayTag::RequestGameplayTag("State.Attacking")))
	{
		for (FGameplayAbilitySpec& Spec : AbilitySystemComponent->GetActivatableAbilities())
		{
			for (UGameplayAbility* Instance : Spec.GetAbilityInstances())
			{
				UBasicAttackAbility* Attack = Cast<UBasicAttackAbility>(Instance);
				if (Attack && Attack->IsActive() && !Attack->bNextAttackQueued)
				{
					UE_LOG(LogTemp, Warning, TEXT("its open"));
					Attack->OpenComboWindow();
					return;
				}
			}
		}
		return;
	}
}
