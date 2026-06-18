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

	UE_LOG(LogTemp, Warning, TEXT("gets intialized"));
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

/*
void UInventoryComponent::AddItem(FString ItemID, int32 Amount)
{
	UItemDefinition* ItemDefinition = UItemFunctionLibrary::FindItemById(ItemID);
	if (!ItemDefinition) return;

	int AvailableSlot;
	if (ItemDefinition->bIsStackable)
	{
		int PossibleSlot = CheckForExistingItemInSlot(ItemDefinition);
		AvailableSlot = PossibleSlot >= 0 ? PossibleSlot : CheckForEmptySlots();
	}
	else
	{
		AvailableSlot = CheckForEmptySlots();
	}


	if (AvailableSlot < 0) return;

	FInventorySlot& FreeSlot = Slots[AvailableSlot];
	FreeSlot.AddItem(ItemDefinition, Amount);

	OnItemAdded.Broadcast(FreeSlot);
}
*/
void UInventoryComponent::AddItemUsingItemDefinition(UItemDefinition* ItemDefinition, float Amount)
{
	if (!ItemDefinition) return;
	// No duplication here — the def passed in is already the unique instance
	int AvailableSlot = ItemDefinition->bIsStackable
		? (CheckForExistingItemInSlot(ItemDefinition) >= 0 ? CheckForExistingItemInSlot(ItemDefinition) : CheckForEmptySlots())
		: CheckForEmptySlots();
	if (AvailableSlot < 0) return;
	Slots[AvailableSlot].AddItem(ItemDefinition, Amount);
	OnItemAdded.Broadcast(Slots[AvailableSlot]);
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

void UInventoryComponent::EquipRuneToWeapon(URuneBase* Rune, int32 SlotIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("=== EquipRuneToWeapon Called ==="));
	UE_LOG(LogTemp, Warning, TEXT("  SlotIndex: %d"), SlotIndex);
	UE_LOG(LogTemp, Warning, TEXT("  Rune: %s"), Rune ? *Rune->GetName() : TEXT("NULL"));

	if (!Rune)
	{
		UE_LOG(LogTemp, Warning, TEXT("  FAILED: Rune is null"));
		return;
	}

	if (!Slots.IsValidIndex(SlotIndex))
	{
		UE_LOG(LogTemp, Warning, TEXT("  FAILED: SlotIndex %d is out of range (Slots.Num: %d)"), SlotIndex, Slots.Num());
		return;
	}

	FInventorySlot& Slot = Slots[SlotIndex];
	UE_LOG(LogTemp, Warning, TEXT("  Slot occupied: %s"), Slot.bIsOccupied ? TEXT("YES") : TEXT("NO"));
	UE_LOG(LogTemp, Warning, TEXT("  ItemDefinition: %s"), Slot.ItemDefinition ? *Slot.ItemDefinition->GetName() : TEXT("NULL"));
	UE_LOG(LogTemp, Warning, TEXT("  Slot %d ItemDef: %s (%p)"),
		SlotIndex,
		Slot.ItemDefinition ? *Slot.ItemDefinition->GetName() : TEXT("NULL"),
		static_cast<void*>(Slot.ItemDefinition));


	if (!Slot.bIsOccupied || !Slot.ItemDefinition)
	{
		UE_LOG(LogTemp, Warning, TEXT("  FAILED: Slot not occupied or no item definition"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("  ItemType: %d (Weapon = %d)"), (int32)Slot.ItemDefinition->ItemType, (int32)EItemType::Weapon);

	if (Slot.ItemDefinition->ItemType != EItemType::Weapon)
	{
		UE_LOG(LogTemp, Warning, TEXT("  FAILED: Item is not a weapon"));
		return;
	}

	// Add rune to item definition
	bool bSlotFound = false;
	for (int32 i = 0; i < Slot.ItemDefinition->WeaponData.Runes.Num(); i++)
	{
		if (!Slot.ItemDefinition->WeaponData.Runes[i])
		{
			Slot.ItemDefinition->WeaponData.Runes[i] = Rune;
			bSlotFound = true;
			UE_LOG(LogTemp, Warning, TEXT("  Rune placed in slot %d"), i);
			break;
		}
	}
	if (!bSlotFound)
	{
		UE_LOG(LogTemp, Warning, TEXT("  FAILED: No empty rune slots in item definition"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("  Rune added to item definition. Total runes: %d"), Slot.ItemDefinition->WeaponData.Runes.Num());

	// Check if weapon is currently equipped
	ABaseCharacter* Owner = Cast<ABaseCharacter>(GetOwner());
	UE_LOG(LogTemp, Warning, TEXT("  Owner: %s"), Owner ? *Owner->GetName() : TEXT("NULL"));

	if (!Owner)
	{
		UE_LOG(LogTemp, Warning, TEXT("  No owner — rune saved to item definition only"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("  Owner Weapon: %s"), Owner->Weapon ? *Owner->Weapon->GetName() : TEXT("NULL"));

	if (!Owner->Weapon)
	{
		UE_LOG(LogTemp, Warning, TEXT("  No weapon equipped — rune saved to item definition only"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("  Weapon ItemDef: %s"), Owner->Weapon->ItemDefinition ? *Owner->Weapon->ItemDefinition->GetName() : TEXT("NULL"));
	UE_LOG(LogTemp, Warning, TEXT("  Slot ItemDef:   %s"), *Slot.ItemDefinition->GetName());
	UE_LOG(LogTemp, Warning, TEXT("  Pointers match: %s"), Owner->Weapon->ItemDefinition == Slot.ItemDefinition ? TEXT("YES") : TEXT("NO"));

	if (Owner->Weapon->ItemDefinition == Slot.ItemDefinition)
	{
		bool bSuccess = Owner->Weapon->EquipRune(Rune);
		UE_LOG(LogTemp, Warning, TEXT("  EquipRune on live weapon: %s"), bSuccess ? TEXT("SUCCESS") : TEXT("FAILED - no empty slots"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("  Weapon equipped but item definition pointer mismatch — rune saved to definition only"));
	}

	UE_LOG(LogTemp, Warning, TEXT("=== EquipRuneToWeapon Done ==="));
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
	// Rune on weapon
	if (Source.ItemDefinition->ItemType == EItemType::Rune
		&& Target.ItemDefinition
		&& Target.ItemDefinition->ItemType == EItemType::Weapon)
	{
		URuneBase* Rune = Source.ItemDefinition->GetRune();
		if (Rune)
			EquipRuneToWeapon(Rune, TargetIndex);     

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

void UInventoryComponent::RemoveFromItemQuantity(int SlotIndex, float Amount)
{
	if (!Slots.IsValidIndex(SlotIndex)) return;

	FInventorySlot& Slot = Slots[SlotIndex];
	if (!Slot.bIsOccupied) return;

	Slot.RemoveQuantity(Amount);
	OnItemAdded.Broadcast(Slot);
}

void UInventoryComponent::LoadInventory(const TArray<FInventorySlot>& LoadedSlots)
{
	UE_LOG(LogTemp, Warning, TEXT("Inventory loaded"));
	Slots = LoadedSlots;
	OnInventoryLoaded.Broadcast();
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

