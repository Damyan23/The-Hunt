// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CombatEnterWidget.generated.h"

/**
 * 
 */
UCLASS()
class THEHUNT_API UCombatEnterWidget : public UUserWidget
{
	GENERATED_BODY()
	
	void TriggerLevel() const;

protected:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

public:
	UPROPERTY();
	TSoftObjectPtr<UWorld> CombatLevel;
};
