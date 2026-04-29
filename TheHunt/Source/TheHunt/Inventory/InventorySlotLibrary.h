#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "InventorySlot.h"
#include "InventorySlotLibrary.generated.h"

UCLASS()
class THEHUNT_API UInventorySlotLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    static void ClearInventorySlot(UPARAM(ref) FInventorySlot& Slot);
};