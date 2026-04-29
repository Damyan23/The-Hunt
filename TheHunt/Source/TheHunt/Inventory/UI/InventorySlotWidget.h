// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/Overlay.h"
#include "Components/TextBlock.h"
#include "InventorySlotWidget.generated.h"

class USizeBox;
/**
 * 
 */
UCLASS()
class THEHUNT_API UInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TObjectPtr<UImage> SlotIcon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TObjectPtr<UButton> Button;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UOverlay> BoundKeyOverlay;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> BoundKeyNumber;
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<USizeBox> SizeBox;
	void SetIcon(UTexture2D* Icon);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSlotClicked, int32, Index);
	UPROPERTY()
	FOnSlotClicked OnSlotClicked;

	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSlotHovered, int32, Index);
	FOnSlotHovered OnSlotHovered;
	int32 SlotIndex;

	bool bIsBoundToKey = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	int32 BoundToKey;

	void ToggleBoundKeyUI(const ESlateVisibility OverlayVisiblity) const;
	void SetBoundToKey(int32 KeyIndex);
};
