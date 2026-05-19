// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/UI/InventorySlotWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "InputPlayer/PlayerCharacter.h"
#include "Inventory/InventorySubsystem.h"

void UInventorySlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button->SetVisibility(ESlateVisibility::HitTestInvisible);
	ToggleBoundKeyUI(ESlateVisibility::Hidden);
}

void UInventorySlotWidget::SetIcon(UTexture2D* Icon)
{
	UE_LOG(LogTemp, Warning, TEXT("It goes into the slot script"));

	if (IsValid(SlotIcon))
	{
		SlotIcon->SetBrushFromTexture(Icon);
	}
}

void UInventorySlotWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	OnSlotHovered.Broadcast(SlotIndex);
}

void UInventorySlotWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	OnSlotHovered.Broadcast(-1);
}

void UInventorySlotWidget::ToggleBoundKeyUI(const ESlateVisibility OverlayVisiblity) const
{
	BoundKeyOverlay->SetVisibility(OverlayVisiblity);
	BoundKeyNumber->SetVisibility(OverlayVisiblity);
}

void UInventorySlotWidget::SetBoundToKey(int32 KeyIndex)
{
	ToggleBoundKeyUI(ESlateVisibility::Visible);
	BoundKeyNumber->SetText(FText::AsNumber(KeyIndex));
	BoundToKey = KeyIndex;
}