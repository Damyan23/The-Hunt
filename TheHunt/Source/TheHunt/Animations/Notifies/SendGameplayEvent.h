// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "SendGameplayEvent.generated.h"

/**
 * 
 */
UCLASS()
class THEHUNT_API USendGameplayEvent : public UAnimNotify
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Event")
	FGameplayTag EventTag;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
		const FAnimNotifyEventReference& EventReference) override;
};
