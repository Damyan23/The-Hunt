// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Engine/Texture2D.h"
#include "ItemDefinition.generated.h"
//#include "ItemEffect.h"

/**
 * 
 */
UCLASS(BlueprintType)
class THEHUNT_API UItemDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UItemDefinition();

	UPROPERTY(EditDefaultsOnly, Category = "Item")
	FName ItemID;
	
	UPROPERTY(EditDefaultsOnly, Category = "Item")
	TSoftObjectPtr<UTexture2D> ItemIcon;

	UPROPERTY(EditAnywhere, Category = "Item")
	TArray<TSubclassOf<class UItemEffect>> Effects;
};
