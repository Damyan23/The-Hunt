// Fill out your copyright notice in the Description page of Project Settings.

#include "TheHuntGameInstance.h"
#include "Inventory/InventoryComponent.h" 
#include "MainMenu/TransitionWidget.h"

void UTheHuntGameInstance::ResetRun()
{
    bHasSaved = false;
    SavedProgression = FPlayerProgressionData();   // empty struct — no inventory, no perks, no weapon, no attributes

    // Clear map state so a brand-new map generates
    bHasMapState = false;
    SavedMap.Empty();
    FoliagePoints.Empty();
    HousePoints.Empty();
    RuinPoints.Empty();

    // Reset node position so the player starts on the StartNode
    CurrentNodeIndex = -1;
}

void UTheHuntGameInstance::TransitionToLevel(TSoftObjectPtr<UWorld> Level)
{
    PendingLevel = Level;

    UWorld* World = GetWorld();
    if (!World || !TransitionWidgetClass)
    {
        // No widget set up — just open immediately as a fallback
        UGameplayStatics::OpenLevelBySoftObjectPtr(this, Level);
        return;
    }

    APlayerController* PC = World->GetFirstPlayerController();

    // Create and show the transition widget
    ActiveTransitionWidget = CreateWidget<UTransitionWidget>(
        PC ? Cast<APlayerController>(PC) : nullptr, TransitionWidgetClass);

    if (!ActiveTransitionWidget)
    {
        UGameplayStatics::OpenLevelBySoftObjectPtr(this, Level);
        return;
    }

    ActiveTransitionWidget->AddToViewport(1);

    ActiveTransitionWidget->PlayDissolve(0.f, 1.5f, TransitionDuration);

    // Open the level once the screen is fully covered
    FTimerHandle Timer;
    World->GetTimerManager().SetTimer(Timer, [this]()
        {
            UGameplayStatics::OpenLevelBySoftObjectPtr(this, PendingLevel);
        }, TransitionDuration, false);
}
