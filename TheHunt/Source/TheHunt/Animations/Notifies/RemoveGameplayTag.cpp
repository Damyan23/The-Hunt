// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/Notifies/RemoveGameplayTag.h"

#include "GameplayAbilitySystem/BaseCharacter.h"

void URemoveGameplayTag::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (ABaseCharacter* Character = Cast<ABaseCharacter>(MeshComp->GetOwner()))
	{
		Character->GetAbilitySystemComponent()->RemoveLooseGameplayTag(TagToRemove);
	}
}
