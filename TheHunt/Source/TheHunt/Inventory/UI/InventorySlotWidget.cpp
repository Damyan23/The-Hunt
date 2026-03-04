// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/UI/InventorySlotWidget.h"

void UInventorySlotWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Button->OnClicked.AddDynamic(this, &UInventorySlotWidget::OnButtonClicked);
}

void UInventorySlotWidget::SetIcon(UTexture2D* Icon) const
{
	UE_LOG(LogTemp, Warning, TEXT("It goes into the slot script"));

	if (IsValid(SlotIcon))
	{
		SlotIcon->SetBrushFromTexture(Icon);
	}
}

void UInventorySlotWidget::OnButtonClicked()
{
	OnSlotClicked.Broadcast(SlotIndex);
}
