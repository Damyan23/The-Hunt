// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ItemEffect.generated.h"

/**
 * 
 */
UCLASS()
class THEHUNT_API UItemEffect : public UObject
{
	GENERATED_BODY()
	
	UFUNCTION ()
	virtual void ApplyEffect(AActor* target);
};
