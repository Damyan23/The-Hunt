// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/InventorySubsystem.h"
#include "Inventory/InventoryComponent.h"

void UInventorySubsystem::RegisterInventory(AActor* actor, UInventoryComponent* inventory)
{
	if (actor && inventory)
	{
		Inventories.Add(actor, inventory);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("When adding an inventory, either it was inavlid or the actor"));
	}
}

void UInventorySubsystem::AddItemToActor(AActor* Target, UItemDefinition* Item)
{
	TObjectPtr<UInventoryComponent>* Found = Inventories.Find(Target);
	if (Found && *Found)
	{
		(*Found)->AddItem(Item);
	}
}
