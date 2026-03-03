// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Items/ItemDefinition.h"
#include "InventorySubsystem.generated.h"


class UInventoryComponent;
/**
 * 
 */
UCLASS()
class THEHUNT_API UInventorySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void RegisterInventory(AActor* actor, UInventoryComponent* inventory);
	void AddItemToActor(AActor* Target, UItemDefinition* Item);
	
private:
	TMap<TObjectPtr<AActor>, TObjectPtr<UInventoryComponent>> Inventories; 
};
