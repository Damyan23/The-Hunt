// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Items/ItemDefinition.h"
#include "InventorySlot.h"
#include "InventoryComponent.generated.h"

class UInventorySubsystem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THEHUNT_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSlotUpdated, int32, SlotIndex, UTexture2D*, Icon);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddItem(UItemDefinition* Item);
	void RemoveItem(FInventorySlot* Slot);

public:
	UPROPERTY(EditAnywhere, Category = "Inventory")
	int32 Rows = 4;

	UPROPERTY(EditAnywhere, Category = "Inventory")
	int32 Columns = 6;

	UPROPERTY(EditAnywhere, Category = "Inventory")
	TArray<FInventorySlot> Slots;

	UPROPERTY(BlueprintAssignable)
	FOnSlotUpdated OnSlotUpdated;
};
