// Fill out your copyright notice in the Description page of Project Settings.


#include "Sts_Map/CombatEnterWidget.h"

#include "TheHuntGameInstance.h"
#include "Engine/LevelScriptActor.h"
#include "Kismet/GameplayStatics.h"

void UCombatEnterWidget::TriggerLevel() const
{
    if (UTheHuntGameInstance* GI = GetGameInstance<UTheHuntGameInstance>())
        GI->TransitionToLevel(CombatLevel);
}

FReply UCombatEnterWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    UE_LOG(LogTemp, Warning, TEXT("[Trigger] Mouse down: %s"),
        *InMouseEvent.GetEffectingButton().ToString());
    if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
    {
        TriggerLevel();
        return FReply::Handled();
    }
    return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}
