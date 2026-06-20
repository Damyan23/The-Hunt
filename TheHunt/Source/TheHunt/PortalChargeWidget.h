// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PortalChargeWidget.generated.h"

/**
 * 
 */
 // UPortalChargeWidget.h
UCLASS()
class UPortalChargeWidget : public UUserWidget
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintImplementableEvent, Category = "Portal")
    void SetPercent(float Percent);
};