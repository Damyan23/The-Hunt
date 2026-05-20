#include "Items/Interactable.h"

#include "ItemFunctionLibrary.h"
#include "Inventory/InventorySubsystem.h"

void AInteractable::InitializeItemDefinition()
{
    ItemDefinition = UItemFunctionLibrary::FindItemById(ItemID);
}

AInteractable::AInteractable()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AInteractable::OnInteract_Implementation(AActor* Interactor)
{
    AddToInventory(Interactor);
}

void AInteractable::AddToInventory(AActor* Interactor)
{
    if (!Interactor) return;

    UInventorySubsystem* Subsystem = GetGameInstance()->GetSubsystem<UInventorySubsystem>();
    Subsystem->AddItemToActor(Interactor, ItemID, ItemDefinition->CurrentQuantity);

    AActor::Destroy();
}
