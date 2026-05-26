// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/UI/InventoryWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/SizeBox.h"
#include "InputPlayer/PlayerCharacter.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

    SetUserFocus(GetOwningPlayer());
    GI = Cast<UTheHuntGameInstance>(GetWorld()->GetGameInstance());
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
}
