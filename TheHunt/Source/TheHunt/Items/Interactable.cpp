#include "Items/Interactable.h"

#include "ItemFunctionLibrary.h"
#include "Inventory/InventorySubsystem.h"

void AInteractable::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

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

    if (!ItemDefinition)
    {
        UE_LOG(LogTemp, Warning, TEXT("Interactable: ItemDefinition is null - check ItemID is set correctly"));
        return;
    }

    UInventorySubsystem* Subsystem = GetGameInstance()->GetSubsystem<UInventorySubsystem>();
    if (!Subsystem)
    {
        UE_LOG(LogTemp, Warning, TEXT("Interactable: InventorySubsystem is null"));
        return;
    }

    Subsystem->AddItemToActor(Interactor, ItemID, ItemDefinition->CurrentQuantity);
    AActor::Destroy();
}
