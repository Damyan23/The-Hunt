// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "ItemDefinitionDescription.generated.h"

/**
 * 
 */
UCLASS()
class THEHUNT_API UItemDefinitionDescription : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemName;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UImage> ItemIcon;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemDescription;
};
