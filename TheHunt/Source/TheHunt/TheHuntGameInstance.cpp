// Fill out your copyright notice in the Description page of Project Settings.

#include "TheHuntGameInstance.h"

#include "InputPlayer/PlayerCharacter.h"
#include "Inventory/InventoryComponent.h" 
#include "MainMenu/TransitionWidget.h"
#include "Sts_Map/Character/MapCharacter.h"

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

    // Save the map character's progression BEFORE transitioning
    if (World)
    {
        if (APlayerController* PC = World->GetFirstPlayerController())
        {
            if (AMapCharacter* MapChar = Cast<AMapCharacter>(PC->GetPawn()))
            {
                MapChar->SaveData();
            }
            else if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(PC->GetPawn()))
            {
                this->StoreProgression(PlayerCharacter->GatherProgression());
            }
        }
    }

    if (!World || !TransitionWidgetClass)
    {
        UGameplayStatics::OpenLevelBySoftObjectPtr(this, Level);
        return;
    }

    APlayerController* PC = World->GetFirstPlayerController();
    ActiveTransitionWidget = CreateWidget<UTransitionWidget>(
        PC ? Cast<APlayerController>(PC) : nullptr, TransitionWidgetClass);
    if (!ActiveTransitionWidget)
    {
        UGameplayStatics::OpenLevelBySoftObjectPtr(this, Level);
        return;
    }

    ActiveTransitionWidget->AddToViewport(1);
    ActiveTransitionWidget->PlayDissolve(0.f, 1.5f, TransitionDuration);

    FTimerHandle Timer;
    World->GetTimerManager().SetTimer(Timer, [this]()
        {
            UGameplayStatics::OpenLevelBySoftObjectPtr(this, PendingLevel);
        }, TransitionDuration, false);
}

void UTheHuntGameInstance::TransitionToLevel(FName LevelName)
{
    PendingLevelName = LevelName;
    UWorld* World = GetWorld();

    // Save the map character's progression BEFORE transitioning
    if (World)
    {
        if (APlayerController* PC = World->GetFirstPlayerController())
        {
            if (AMapCharacter* MapChar = Cast<AMapCharacter>(PC->GetPawn()))
            {
                MapChar->SaveData();
            }
            else if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(PC->GetPawn()))
            {
                this->StoreProgression(PlayerCharacter->GatherProgression());
            }
        }
    }

    if (!World || !TransitionWidgetClass)
    {
        UGameplayStatics::OpenLevel(this, LevelName);
        return;
    }

    APlayerController* PC = World->GetFirstPlayerController();
    ActiveTransitionWidget = CreateWidget<UTransitionWidget>(
        PC ? Cast<APlayerController>(PC) : nullptr, TransitionWidgetClass);
    if (!ActiveTransitionWidget)
    {
        UGameplayStatics::OpenLevel(this, LevelName);
        return;
    }

    ActiveTransitionWidget->AddToViewport(1);
    ActiveTransitionWidget->PlayDissolve(0.f, 1.5f, TransitionDuration);

    FTimerHandle Timer;
    World->GetTimerManager().SetTimer(Timer, [this]()
        {
            UGameplayStatics::OpenLevel(this, PendingLevelName);
        }, TransitionDuration, false);
}