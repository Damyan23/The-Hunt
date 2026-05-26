// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/InventoryComponent.h"
#include "Inventory/InventorySubsystem.h"
#include "InventorySlot.h"
#include "InputPlayer/PlayerCharacter.h"
#include "Items/ItemFunctionLibrary.h"
#include "Items/Weapon/MeleeWeapon.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	OnSlotClickedWithKey.AddDynamic(this, &UInventoryComponent::OnSlotKeyBound);
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	UInventorySubsystem* Subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UInventorySubsystem>();
	Subsystem->RegisterInventory(GetOwner(), this);
}

void UInventoryComponent::OnComponentCreated()
{
	Super::OnComponentCreated();

	for (int i = 0; i < NumberOfSlots; i++)
		Slots.Add(FInventorySlot(nullptr, false, i));
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventoryComponent::AddItem(FString ItemID, int32 Amount)
{
	UItemDefinition* ItemDefinition = UItemFunctionLibrary::FindItemById(ItemID);
	if (!ItemDefinition) return;

	int PossibleSlot = CheckForExistingItemInSlot(ItemDefinition);
	int AvailableSlot = PossibleSlot >= 0 ? PossibleSlot : CheckForEmptySlots();

	if (AvailableSlot < 0) return;

	FInventorySlot& FreeSlot = Slots[AvailableSlot];
	FreeSlot.AddItem(ItemDefinition, Amount);

	UE_LOG(LogTemp, Warning, TEXT("AddItem: Slot %d, Quantity: %d"), AvailableSlot, FreeSlot.Quantity);

	OnItemAdded.Broadcast(FreeSlot);
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

	FInventorySlot& Slot = Slots[Index];;
	if (!Slot.bIsOccupied) return;

	UItemDefinition* ItemDef = Slot.ItemDefinition;

	if (!ItemDef) return;

	APlayerCharacter* Player = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (ItemDef->ItemType == EItemType::Weapon)
	{
		TSubclassOf<AMeleeWeapon> WeaponClass = ItemDef->GetWeaponClass();
		if (WeaponClass)
		{
			Player->EquipWeapon(WeaponClass);
		}
	}

	RemoveItem(&Slot);
}

void UInventoryComponent::DropItem(UPARAM(ref) FInventorySlot& Slot)
{
	UItemDefinition* ItemDefinition = Slot.ItemDefinition;

	UWorld* World = GetWorld();
	if (!World) return;

	if (!ItemDefinition) return;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetOwner());

	// Trace start above the actor and trace straight down to hit the ground
	const FVector TraceStart = GetOwner()->GetActorLocation() + FVector(0.f, 0.f, 50.f);
	constexpr float TraceDistance = 2000.f;
	const FVector TraceEnd = TraceStart - FVector(0.f, 0.f, TraceDistance);

	FCollisionQueryParams GroundTraceParams;
	GroundTraceParams.AddIgnoredActor(GetOwner());

	FHitResult GroundHit;
	const bool bGroundHit = World->LineTraceSingleByChannel(GroundHit, TraceStart, TraceEnd, ECC_Visibility, GroundTraceParams);

	if (bGroundHit)
	{
		// Spawn a bit in front of the player (scale the forward vector)
		constexpr float SpawnForwardOffset = 100.f; // how far in front of the player to spawn
		constexpr float SpawnUpOffset = 0.f;        // slight lift to avoid embedding in ground

		const FVector Forward = GetOwner()->GetActorForwardVector(); // unit vector
		const FVector SpawnLocation = GroundHit.Location + Forward * SpawnForwardOffset;
		const FRotator SpawnRotation = FRotator::ZeroRotator;

		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		AInteractable* Item = World->SpawnActor<AInteractable>(
			ItemDefinition->ItemClass,
			SpawnLocation,
			SpawnRotation,
			SpawnParameters
		);

		if (Item)
		{
			Item->ItemID = ItemDefinition->ItemID;
			Item->ItemDefinition = ItemDefinition;
		}
	}

	Slot.ClearSlot();
	OnItemRemoved.Broadcast(Slot);
}

void UInventoryComponent::OnSlotKeyBound(int32 SlotIndex, int32 HotbarSlot)
{
	if (SlotIndex < 0 || SlotIndex > Slots.Num()) return;
	APlayerCharacter* Player = Cast<APlayerCharacter>(GetOwner());

	if (!Player) return;

	FInventorySlot& SelectedSlot = Slots[SlotIndex];;

	Player->BindItemToSlot(SelectedSlot.ItemDefinition, HotbarSlot);
}

UItemDefinition* UInventoryComponent::GetHoveredSlotItemDefinition(int32 SlotIndex)
{
	if (SlotIndex < 0 || SlotIndex > Slots.Num()) return nullptr;

	return Slots[SlotIndex].ItemDefinition;
}

void UInventoryComponent::UpdateSlotOnDragAndDrop(int32 SourceIndex, int32 TargetIndex)
{
	if (!Slots.IsValidIndex(SourceIndex) || !Slots.IsValidIndex(TargetIndex)) return;
	if (SourceIndex == TargetIndex) return;

	FInventorySlot& Source = Slots[SourceIndex];
	FInventorySlot& Target = Slots[TargetIndex];

	if (!Source.ItemDefinition) return;

	// Rune on weapon
	if (Source.ItemDefinition->ItemType == EItemType::Rune
		&& Target.ItemDefinition
		&& Target.ItemDefinition->ItemType == EItemType::Weapon)
	{
		APlayerCharacter* Player = Cast<APlayerCharacter>(
			GetWorld()->GetFirstPlayerController()->GetPawn());
		if (Player && Player->Weapon)
			Player->EquipRuneToWeapon(Source.ItemDefinition);

		Source.ClearSlot();
		OnItemRemoved.Broadcast(Source);
		return;
	}

	if (!Target.bIsOccupied)
	{
		MoveSlot(Source, Target);
	}
	else if (Target.ItemDefinition == Source.ItemDefinition)
	{
		Target.Quantity += Source.Quantity;
		Source.ClearSlot();
		OnItemRemoved.Broadcast(Source);
	}
	else
	{
		SwapSlots(Source, Target);
		OnSlotMoved.Broadcast(Source);
	}

	OnSlotMoved.Broadcast(Target);
}

int32 UInventoryComponent::GetHotbarIndexFromKey(FKey Key)
{
	if (Key == EKeys::One)   return 1;
	if (Key == EKeys::Two)   return 2;
	if (Key == EKeys::Three) return 3;
	if (Key == EKeys::Four)  return 4;
	return -1;
}

void UInventoryComponent::MoveSlot(FInventorySlot& From, FInventorySlot& To)
{
	To.ItemDefinition = From.ItemDefinition;
	To.Quantity = From.Quantity;
	To.bIsOccupied = true;
	From.ClearSlot();
	OnItemRemoved.Broadcast(From);
}

void UInventoryComponent::SwapSlots(FInventorySlot& A, FInventorySlot& B)
{
	FInventorySlot Temp = B;
	B.ItemDefinition = A.ItemDefinition;
	B.Quantity = A.Quantity;
	B.bIsOccupied = true;
	A.ItemDefinition = Temp.ItemDefinition;
	A.Quantity = Temp.Quantity;
	A.bIsOccupied = Temp.bIsOccupied;
}

int UInventoryComponent::CheckForEmptySlots()
{
	for (auto& Slot : Slots)
	{
		if (!Slot.bIsOccupied)
			return Slot.SlotIndex;
	}
	return -1;
}

int UInventoryComponent::CheckForExistingItemInSlot(UItemDefinition* ItemDefinition)
{
	if (!ItemDefinition) return -1;

	for (FInventorySlot& Slot : Slots)
	{
		if (!Slot.ItemDefinition) continue;
		if (Slot.ItemDefinition->ItemID.Equals(ItemDefinition->ItemID))
			return Slot.SlotIndex;
	}
	return -1;
}

