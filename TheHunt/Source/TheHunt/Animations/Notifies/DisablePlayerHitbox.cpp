// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/Notifies/DisablePlayerHitbox.h"
#include "InputPlayer/PlayerCharacter.h"

void UDisablePlayerHitbox::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                      const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (APlayerCharacter* Player = Cast<APlayerCharacter>(MeshComp->GetOwner()))
		Player->DisableHitbox();
}
