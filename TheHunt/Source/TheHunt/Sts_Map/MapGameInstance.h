// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MapGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class THEHUNT_API UMapGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
    // The map level to return to after combat/exploration
    UPROPERTY(BlueprintReadWrite)
    TSoftObjectPtr<UWorld> PendingReturnLevel;

    // The node index the player was on when they left the map
    UPROPERTY(BlueprintReadWrite)
    int32 PendingReturnNodeIndex = -1;
};
