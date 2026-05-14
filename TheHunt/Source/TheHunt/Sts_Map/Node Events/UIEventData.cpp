// Fill out your copyright notice in the Description page of Project Settings.


#include "UIEventData.h"
#include "Blueprint/UserWidget.h"

void UUIEventData::OnEnter_Implementation(APlayerController* PC)
{
	Super::OnEnter_Implementation(PC);

	Widget = CreateWidget<UUserWidget>(GetWorld()->GetFirstPlayerController(), EventWidget);
	if (Widget)
		Widget->AddToViewport();
}

void UUIEventData::OnComplete_Implementation(APlayerController* PC)
{
	Super::OnComplete_Implementation(PC);

	if (Widget)
		Widget->RemoveFromParent();
}
