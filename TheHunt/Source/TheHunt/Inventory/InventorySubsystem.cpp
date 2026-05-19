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
		UE_LOG(LogTemp, Warning, TEXT("When adding an inventory, either it was invalid or the actor was"));
	}
}

void UInventorySubsystem::AddItemToActor(AActor* Target, FString ItemID, int32 Amount)
{
	TObjectPtr<UInventoryComponent>* Found = Inventories.Find(Target);
	if (Found && *Found)
	{
		(*Found)->AddItem(ItemID, Amount);
	}
}

void UInventorySubsystem::RemoveItem(AActor* Target, int32 SlotIndex)
{
	TObjectPtr<UInventoryComponent>* Found = Inventories.Find(Target);
	if (Found && *Found)
	{
		(*Found)->RemoveItem(&(*Found)->Slots[SlotIndex]);
	}
}
