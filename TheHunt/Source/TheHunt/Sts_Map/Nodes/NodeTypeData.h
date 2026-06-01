// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NodeTypeData.generated.h"

UENUM(BlueprintType)
enum ENodeType
{
    Combat,
    RandomEncounter,
    Rest,
    Perk,
    Ritual
};

/**
 * 
 */
USTRUCT(BlueprintType)
struct FNodeTypeData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TEnumAsByte<ENodeType> NodeType;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UTexture2D* Icon;
};