// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/Notifies/DissableHitbox.h"

#include "GameplayAbilitySystem/BaseCharacter.h"

void UDissableHitbox::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                             const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	AActor* Owner = MeshComp->GetOwner();

	// If the mesh belongs to the weapon, walk up to the weapon's owner (the character)
	ABaseCharacter* Character = Cast<ABaseCharacter>(Owner);
	if (!Character)
	{
		// Owner is likely the AMeleeWeapon — get its owner (the character who spawned it)
		if (Owner)
		{
			Character = Cast<ABaseCharacter>(Owner->GetOwner());
		}
	}

	if (Character && Character->Weapon)
	{
		Character->Weapon->DisableHitbox();
	}
}
