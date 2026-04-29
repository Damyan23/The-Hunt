#include "InventorySlotLibrary.h"

void UInventorySlotLibrary::ClearInventorySlot(UPARAM(ref) FInventorySlot& Slot)
{
    // Reuse the C++ helper
    Slot.ClearSlot();
}