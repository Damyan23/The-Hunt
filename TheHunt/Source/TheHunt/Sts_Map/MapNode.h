// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Class.h"
#include "MapNode.generated.h"

UENUM (BlueprintType)
enum ENodeType
{
	Combat,
	Shop,
	Event
};

USTRUCT()
struct FMapNode 
{
	GENERATED_BODY()
	
	int32 ID;
	FVector2D Position;
	TArray<int32> Connections;
	ENodeType NodeType;
};
