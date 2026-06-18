// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/Notifies/SendGameplayEvent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Sts_Map/Node Events/UIEventData.h"

void USendGameplayEvent::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (!MeshComp || !EventTag.IsValid()) return;

	AActor* Owner = MeshComp->GetOwner();
	if (!Owner) return;

	FGameplayEventData Payload;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Owner, EventTag, Payload);
}
