// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseEventWidget.generated.h"


class UUIEventData;
/**
 * 
 */
UCLASS()
class THEHUNT_API UBaseEventWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UUIEventData* EventData;

    UFUNCTION(BlueprintImplementableEvent)
    void InitWidget(UUIEventData* Data);
};
