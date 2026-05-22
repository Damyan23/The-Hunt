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

	FGameplayAbilitySpec* Spec = PlayerCharacter->AbilitySystemComponent->FindAbilitySpecFromClass(UBasicAttackAbility::StaticClass());
	if (!Spec) return;

	UBasicAttackAbility* AttackAbility = Cast<UBasicAttackAbility>(Spec->GetPrimaryInstance());
	if (!AttackAbility) return;

	AttackAbility->OpenComboWindow();
}
