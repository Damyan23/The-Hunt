// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NodeTypeData.h"
#include "Engine/DataAsset.h"
#include "Sts_Map/Node Events/MapEventData.h"
#include "MapNodeData.generated.h"

USTRUCT(BlueprintType)
struct FNodeEventPool
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSoftObjectPtr<UMapEventData>> Events;
};


/**
 * 
 */
UCLASS(BlueprintType)
class THEHUNT_API UMapNodeData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<TEnumAsByte<ENodeType>, FNodeEventPool> NodeMappings;
};
