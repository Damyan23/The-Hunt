// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "TransitionWidget.generated.h"

/**
 * 
 */
UCLASS()
class THEHUNT_API UTransitionWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
	UImage* DissolveImage;

	UPROPERTY()
	UMaterialInstanceDynamic* DissolveMID;

	// duration-based lerp state
	float DissolveStart = 0.f;
	float DissolveEnd = 0.f;
	float DissolveElapsed = 0.f;
	float DissolveDuration = 1.f;
	bool  bDissolving = false;

	UFUNCTION(BlueprintCallable)
	void PlayDissolve(float From, float To, float Duration);

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
