// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
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
	
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<USizeBox> SizeBox;
	void SetIcon(UTexture2D* Icon) const;
	UFUNCTION()
	void OnButtonClicked();

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSlotClicked, int32, Index);
	UPROPERTY()
	FOnSlotClicked OnSlotClicked;
	int32 SlotIndex;
};
