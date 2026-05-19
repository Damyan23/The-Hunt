#include "Items/Interactable.h"

#include "ItemFunctionLibrary.h"
#include "Inventory/InventorySubsystem.h"


void AInteractable::BeginPlay()
{
    Super::BeginPlay();

    InitializeItemDefinition();
}

AInteractable::AInteractable()
{
    PrimaryActorTick.bCanEverTick = false;
}


void AInteractable::InitializeItemDefinition()
{
    ItemDefinition = UItemFunctionLibrary::FindItemById(ItemID);

    if (ItemDefinition)
    {
        UE_LOG(LogTemp, Warning, TEXT("Found item definition: %s"), *ItemDefinition->GetName());
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to find item definition for ItemID: %s"), *ItemID);
    }
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
