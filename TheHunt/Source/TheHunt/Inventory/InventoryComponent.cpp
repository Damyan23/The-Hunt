// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/InventoryComponent.h"
#include "Inventory/InventorySubsystem.h"
#include "InventorySlot.h"
#include "InputPlayer/PlayerCharacter.h"
#include "Items/Weapon/MeleeWeapon.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	Slots.Init(FInventorySlot(), Rows * Columns);
	OnSlotClickedWithKey.AddDynamic(this, &UInventoryComponent::OnSlotKeyBound);
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	UInventorySubsystem* Subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UInventorySubsystem>();
	Subsystem->RegisterInventory(GetOwner(), this);
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventoryComponent::AddItem(UItemDefinition* Item)
{
	for (int i = 0; i < Slots.Num(); i++)
	{
		if (Slots[i].bIsOccupied) continue;

		Slots[i].AddItem(Item);
		UE_LOG(LogTemp, Warning, TEXT("Item added to inventory"), *Item->ItemID.ToString());
		OnSlotUpdated.Broadcast(i, Slots[i].ItemDefinition->ItemIcon.LoadSynchronous());
		break;
	}
}

void UInventoryComponent::RemoveItem(FInventorySlot* Slot)
{
	if (Slot == nullptr) return;
	int32 Index = Slots.IndexOfByPredicate([Slot](const FInventorySlot& S) { return &S == Slot; });
	Slot->ClearSlot();
	OnSlotUpdated.Broadcast(Index, nullptr);
}

void UInventoryComponent::UseItem(const int32 Index)
{
	if (!Slots.IsValidIndex(Index)) return;

	FInventorySlot& Slot = Slots[Index];
	if (!Slot.bIsOccupied) return;

	UItemDefinition* ItemDef = Slot.ItemDefinition;

	if (!ItemDef) return;

	APlayerCharacter* Player = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	Player->UseWeapon(ItemDef->WeaponData.WeaponClass);

	RemoveItem(&Slot);
}

void UInventoryComponent::OnSlotKeyBound(int32 SlotIndex, int32 HotbarSlot)
{
	if (SlotIndex < 0 || SlotIndex > Slots.Num()) return;
	APlayerCharacter* Player = Cast<APlayerCharacter>(GetOwner());

	if (!Player) return;

	FInventorySlot& SelectedSlot = Slots[SlotIndex];

	Player->BindItemToSlot(SelectedSlot.ItemDefinition, HotbarSlot);
}

UItemDefinition* UInventoryComponent::GetHoveredSlotItemDefinition(int32 SlotIndex)
{
	if (SlotIndex < 0 || SlotIndex > Slots.Num()) return nullptr;

	return Slots[SlotIndex].ItemDefinition;
}
