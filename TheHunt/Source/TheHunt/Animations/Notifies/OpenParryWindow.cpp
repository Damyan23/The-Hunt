// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/Notifies/OpenParryWindow.h"

#include "Enemy/EnemyCharacter.h"


void UOpenParryWindow::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(MeshComp->GetOwner());
	if (Enemy)
	{
		Enemy->GetAbilitySystemComponent()->AddLooseGameplayTag(
			FGameplayTag::RequestGameplayTag(FName("State.Parryable")));
		Enemy->OpenParryWindow();
	}
}

void UOpenParryWindow::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                 const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(MeshComp->GetOwner());
	if (Enemy)
	{
		Enemy->GetAbilitySystemComponent()->RemoveLooseGameplayTag(
			FGameplayTag::RequestGameplayTag(FName("State.Parryable")));
		Enemy->CloseParryWindow();
	}
}
