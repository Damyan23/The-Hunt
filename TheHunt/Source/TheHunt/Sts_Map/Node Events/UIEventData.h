// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapEventData.h"
#include "UIEventData.generated.h"

/**
 * 
 */
UCLASS()
class THEHUNT_API UUIEventData : public UMapEventData
{
	GENERATED_BODY()
	
	virtual void OnEnter_Implementation(APlayerController* PC) override;
	virtual void OnComplete_Implementation(APlayerController* PC) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	TSubclassOf<UUserWidget> EventWidget;

	UPROPERTY()
	TObjectPtr<UUserWidget> Widget;
};
