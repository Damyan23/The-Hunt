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
    TObjectPtr<UItemDefinition> ItemDefinition;
     
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    bool bIsOccupied = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int SlotIndex;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly);
    int Quantity;

    void AddItem(UItemDefinition* Item, int32 ItemAmount)
    {
        ItemDefinition = Item;
        Quantity += ItemAmount;
        bIsOccupied = true;
    }

    void ClearSlot()
    {
     
        ItemDefinition = nullptr;   
        Quantity = 0;
        bIsOccupied = false;
    }
};