// Fill out your copyright notice in the Description page of Project Settings.

#include "TheHuntGameInstance.h"
#include "Inventory/InventoryComponent.h" 

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
