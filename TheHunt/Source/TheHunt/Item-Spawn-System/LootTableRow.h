// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Class.h"
#include "Items/ItemDefinition.h"
#include "Items/ItemRarity.h"
#include "Items/ItemType.h"
#include "LootTableRow.generated.h"

USTRUCT()
struct THEHUNT_API FLootTableRow : public FTableRowBase
{
	GENERATED_BODY()

	virtual void OnDataTableChanged(const UDataTable* InDataTable, const FName InRowName) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UItemDefinition> ItemDefinition;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EItemRarity Rarity = EItemRarity::Common;

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EItemType ItemType = EItemType::Weapon;
	
};
