// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "Engine/DataAsset.h"
#include "PerkData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class UPerkData : public UPrimaryDataAsset
{
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Perk")
    FText Name;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Perk")
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Perk")
    UTexture2D* Icon;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Perk")
    TSubclassOf<UGameplayEffect> Effect;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Perk")
    float Duration = 30.f;
};
