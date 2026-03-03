// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/WrapBox.h"
#include "Inventory/InventoryComponent.h"
#include "Inventory/InventorySlot.h"
#include "Inventory/UI/InventorySlotWidget.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Border.h"
#include "Engine/Texture2D.h"
#include "InventoryWidget.generated.h"

class UBorder;
/**
 * 
 */
UCLASS()
class THEHUNT_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	TArray<UInventorySlotWidget*> Slots;

protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UWrapBox> WrapBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TObjectPtr<UInventoryComponent> InventoryComponent;

	UPROPERTY(EditAnywhere, Category = "Inventory")
	TSubclassOf<UUserWidget> SlotWidgetClass;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UBorder> Border;

	void SetupUI();

private:
	UFUNCTION()
	void UpdateUI(const int32 Index, UTexture2D* ItemIcon);
};
