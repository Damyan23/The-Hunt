// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/UI/InventoryWidget.h"

#include "Components/SizeBox.h"
#include "InputPlayer/PlayerCharacter.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

    SetUserFocus(GetOwningPlayer());
}

void UInventoryWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    if (HoveredSlotIndex == -1 && WeaponDescription->IsVisible())
    {
        WeaponDescription->SetVisibility(ESlateVisibility::Hidden);
    }
}

void UInventoryWidget::SetupUI()
{
    if (!InventoryComponent || !WrapBox) return;
    SetIsFocusable(true);

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
        FirstSlot->SlotIndex = 0;
        FirstSlot->OnSlotClicked.AddDynamic(this, &UInventoryWidget::OnSlotClicked);
        FirstSlot->OnSlotHovered.AddDynamic(this, &UInventoryWidget::OnSlotHovered);
        WrapBox->AddChildToWrapBox(FirstSlot);
        Slots.Add(FirstSlot);

    }

    // create the rest
    for (int i = 1; i < Rows * Columns; i++)
    {
        if (UInventorySlotWidget* SlotWidget = CreateWidget<UInventorySlotWidget>(GetWorld(), SlotWidgetClass))
        {
            SlotWidget->SlotIndex = i;
            SlotWidget->OnSlotClicked.AddDynamic(this, &UInventoryWidget::OnSlotClicked);
            SlotWidget->OnSlotHovered.AddDynamic(this, &UInventoryWidget::OnSlotHovered);
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

void UInventoryWidget::OnSlotClicked(const int32 Index)
{
    InventoryComponent->UseItem(Index);
}

void UInventoryWidget::OnSlotHovered(const int32 Index)
{
    HoveredSlotIndex = Index;
    if (Index >= 0)
    {
        FInventorySlot& HoveredSlot = InventoryComponent->Slots[Index];
        if (TObjectPtr<UItemDefinition> ItemDef = HoveredSlot.ItemDefinition)
        {
            switch (ItemDef->ItemType)
            {
            case EItemType::Weapon:
                WeaponDescription->SetVisibility(ESlateVisibility::Visible);
                WeaponDescription->SetDescription(InventoryComponent->GetHoveredSlotItemDefinition(Index));
            }
        }
    }

    SetUserFocus(GetOwningPlayer());
}

FReply UInventoryWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
    if (HoveredSlotIndex == -1) return FReply::Unhandled();

    FKey Key = InKeyEvent.GetKey();
    int32 HotbarSlot = -1;

    if (Key == EKeys::One)   HotbarSlot = 1;
    if (Key == EKeys::Two)   HotbarSlot = 2;
    if (Key == EKeys::Three) HotbarSlot = 3;
    if (Key == EKeys::Four)  HotbarSlot = 4;

    if (HotbarSlot != -1)
    {
        Slots[HoveredSlotIndex]->SetBoundToKey(HotbarSlot);
        for (int i = 0; i < InventoryComponent->Slots.Num(); ++i)
        {
            if (i == HoveredSlotIndex) continue;

            if (Slots[i]->BoundToKey == HotbarSlot)
                Slots[i]->ToggleBoundKeyUI(ESlateVisibility::Hidden);
        }
        InventoryComponent->OnSlotClickedWithKey.Broadcast(HoveredSlotIndex, HotbarSlot);
        return FReply::Handled();
    }

    return FReply::Unhandled();
}
