// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Class.h"
#include "ItemType.generated.h"

/**
 * 
 */
UENUM()
enum class EItemType : uint8
{
	Weapon,
	Consumable,
	Item,
	Rune
};
