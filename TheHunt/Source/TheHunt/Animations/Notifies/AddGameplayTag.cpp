// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/Notifies/AddGameplayTag.h"

#include "GameplayAbilitySystem/BaseCharacter.h"

void UAddGameplayTag::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                             const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (ABaseCharacter* Character = Cast<ABaseCharacter>(MeshComp->GetOwner()))
	{
		Character->GetAbilitySystemComponent()->AddLooseGameplayTag(TagToAdd);
	}
}
