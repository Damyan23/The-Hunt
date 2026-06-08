// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "RotatePlayer.generated.h"

/**
 * 
 */
UCLASS()
class THEHUNT_API URotatePlayer : public UAnimNotifyState
{
	GENERATED_BODY()
	
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;

public:
	UPROPERTY(EditAnywhere)
	float InterpSpeed = 700;
};
