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

	// Delegate types
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSlotUpdated, int32, SlotIndex, UTexture2D*, Icon);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSlotClickedWithKey, int32, SlotIndex, int32, HotbarSlot);

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddItem(UItemDefinition* Item);
	void RemoveItem(FInventorySlot* Slot);
	void UseItem(const int32 Index);

	// Bound event
	UPROPERTY()
	FOnSlotClickedWithKey OnSlotClickedWithKey;
	UFUNCTION()
	void OnSlotKeyBound(int32 SlotIndex, int32 HotbarSlot);

	UPROPERTY(EditAnywhere, Category = "Inventory")
	int32 Rows = 4;

	UPROPERTY(EditAnywhere, Category = "Inventory")
	int32 Columns = 6;

	UPROPERTY(EditAnywhere, Category = "Inventory")
	TArray<FInventorySlot> Slots;

	UFUNCTION(BlueprintCallable)
	UItemDefinition* GetHoveredSlotItemDefinition(int32 SlotIndex);

	UPROPERTY(BlueprintAssignable)
	FOnSlotUpdated OnSlotUpdated;
};