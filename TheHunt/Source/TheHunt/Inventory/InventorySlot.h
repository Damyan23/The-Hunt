#pragma once
#include "CoreMinimal.h"
#include "Items/ItemDefinition.h"
#include "InventorySlot.generated.h"

USTRUCT(BlueprintType)
struct THEHUNT_API FInventorySlot
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<UItemDefinition> ItemDefinition;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsOccupied = false;

    void AddItem(UItemDefinition* Item)
    {
        ItemDefinition = Item;
        bIsOccupied = true;
    }

    void ClearSlot()
    {
        ItemDefinition = nullptr;   
        bIsOccupied = false;
    }
};