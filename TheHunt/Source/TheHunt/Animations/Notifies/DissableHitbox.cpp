// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/Notifies/DissableHitbox.h"

#include "GameplayAbilitySystem/BaseCharacter.h"

void UDissableHitbox::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                             const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ABaseCharacter* Character = Cast<ABaseCharacter>(MeshComp->GetOwner());

	if (Character && Character->Weapon)
	{
		Character->Weapon->DisableHitbox();
	}
}
