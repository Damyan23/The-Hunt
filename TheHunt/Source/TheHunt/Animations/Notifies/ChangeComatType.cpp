// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/Notifies/ChangeComatType.h"

#include "InputPlayer/PlayerCharacter.h"

void UChangeComatType::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                              const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(MeshComp->GetOwner());
}
