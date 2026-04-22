// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/Notifies/OpenParryWindow_Player.h"

#include "InputPlayer/PlayerCharacter.h"
#include "Slate/SGameLayerManager.h"

void UOpenParryWindow_Player::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	APlayerCharacter* Player = Cast<APlayerCharacter>(MeshComp->GetOwner());
	if (Player)
	{
		Player->GetAbilitySystemComponent()->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag("State.Parrying"));
	}
}

void UOpenParryWindow_Player::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	APlayerCharacter* Player = Cast<APlayerCharacter>(MeshComp->GetOwner());
	if (Player)
	{
		Player->GetAbilitySystemComponent()->RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag("State.Parrying"));
	}
}
