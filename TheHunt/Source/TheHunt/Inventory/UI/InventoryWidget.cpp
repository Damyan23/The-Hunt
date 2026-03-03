// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/UI/InventoryWidget.h"

#include "Components/SizeBox.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UInventoryWidget::SetupUI()
{
    if (!InventoryComponent || !WrapBox) return;

    InventoryComponent->OnSlotUpdated.AddDynamic(this, &UInventoryWidget::UpdateUI);

    WrapBox->ClearChildren();

    const int Columns = InventoryComponent->Columns;
    const int Rows = InventoryComponent->Rows;

    float SlotWidth = 64;
    float SlotHeight = 64;

    // create one slot to get the size
    UInventorySlotWidget* FirstSlot = CreateWidget<UInventorySlotWidget>(GetWorld(), SlotWidgetClass);
    if (FirstSlot && FirstSlot->SizeBox)
    {
        SlotWidth = FirstSlot->SizeBox->GetWidthOverride();
        SlotHeight = FirstSlot->SizeBox->GetHeightOverride();
        WrapBox->AddChildToWrapBox(FirstSlot);
        Slots.Add(FirstSlot);
    }

    // create the rest
    for (int i = 1; i < Rows * Columns; i++)
    {
        if (UInventorySlotWidget* SlotWidget = CreateWidget<UInventorySlotWidget>(GetWorld(), SlotWidgetClass))
        {
            WrapBox->AddChildToWrapBox(SlotWidget);
            Slots.Add(SlotWidget);
        }
    }

    const float TotalWidth = (SlotWidth + WrapBox->GetInnerSlotPadding().X) * Columns;
    const float TotalHeight = (SlotHeight + WrapBox->GetInnerSlotPadding().Y + 50)* Rows;

    if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(Border->Slot))
    {
        CanvasSlot->SetSize(FVector2D(TotalWidth, TotalHeight));
    }
}


void UInventoryWidget::UpdateUI(const int32 Index, UTexture2D* ItemIcon)
{
    UE_LOG(LogTemp, Warning, TEXT("Index given: %d, Slots num: %d"), Index, Slots.Num());

    if (!Slots.IsValidIndex(Index))
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid index"));
        return;
    }

    if (UInventorySlotWidget* SlotWidget = Slots[Index])
    {
        SlotWidget->SetIcon(ItemIcon);
    }
}