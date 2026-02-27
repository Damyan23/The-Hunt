// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ItemDefinition.generated.h"
//#include "ItemEffect.h"

/**
 * 
 */
UCLASS(BlueprintType)
class THEHUNT_API UItemDefinition : public UDataAsset
{
	GENERATED_BODY()

public:
	UItemDefinition();

	UPROPERTY(EditDefaultsOnly, Category = "Item")
	FName ItemID;
	
	UPROPERTY(EditAnywhere, Category = "Item")
	TArray<TSubclassOf<class UItemEffect>> Effects;
};
