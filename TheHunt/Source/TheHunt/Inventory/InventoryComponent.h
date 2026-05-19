#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Items/ItemDefinition.h"
#include "InventorySlot.h"
#include "InventoryComponent.generated.h"

class UInventorySubsystem;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class THEHUNT_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()


public:
	UInventoryComponent();

protected:
	virtual void BeginPlay() override;
	virtual void OnComponentCreated() override;

	// Delegate types
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSlotUpdated, int32, SlotIndex, UTexture2D*, Icon);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSlotClickedWithKey, int32, SlotIndex, int32, HotbarSlot);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemAdded, FInventorySlot, InventorySlot);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemRemoved, FInventorySlot, InventorySlot);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSlotMoved, FInventorySlot, InventorySlot);
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddItem(FString ItemID, int32 Amount);
	void RemoveItem(FInventorySlot* Slot);
	void UseItem(const int32 Index);	

	UFUNCTION(BlueprintCallable)
	void DropItem(UPARAM(ref) FInventorySlot& Slot);

	UPROPERTY(BlueprintAssignable)
	FOnItemAdded OnItemAdded;

	UPROPERTY(BlueprintAssignable)
	FOnItemAdded OnItemRemoved;


	UPROPERTY(BlueprintAssignable)
	FOnSlotMoved OnSlotMoved;

	// Bound event
	UPROPERTY()
	FOnSlotClickedWithKey OnSlotClickedWithKey;
	UFUNCTION(BlueprintCallable)
	void OnSlotKeyBound(int32 SlotIndex, int32 HotbarSlot);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 NumberOfSlots;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	TArray<FInventorySlot> Slots;

	UFUNCTION(BlueprintCallable)
	UItemDefinition* GetHoveredSlotItemDefinition(int32 SlotIndex);

	UPROPERTY(BlueprintAssignable)
	FOnSlotUpdated OnSlotUpdated;

	UFUNCTION(BlueprintCallable)
	void UpdateSlotOnDragAndDrop(int32 SourceIndex, int32 TargetIndex);


	UFUNCTION(BlueprintCallable, BlueprintPure)
	static int32 GetHotbarIndexFromKey(FKey Key);
private:
	int CheckForEmptySlots();
	int CheckForExistingItemInSlot(UItemDefinition* ItemDefinition);

	void MoveSlot(FInventorySlot& From, FInventorySlot& To);
	void SwapSlots(FInventorySlot& A, FInventorySlot& B);
};