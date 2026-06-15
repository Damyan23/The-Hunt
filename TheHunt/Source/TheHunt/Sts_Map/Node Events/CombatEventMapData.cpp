// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatEventMapData.h"
#include "Kismet/GameplayStatics.h"
#include "Sts_Map/MapGameInstance.h"
#include "Sts_Map/Character/MapCharacter.h"

void UCombatMapData::OnEnter_Implementation(APlayerController* PC)
{
	Super::OnEnter_Implementation(PC);

    // Save info to game instance so we can return to map after combat
    if (UMapGameInstance* GI = Cast<UMapGameInstance>(PC->GetGameInstance()))
    {
        GI->PendingReturnLevel = TSoftObjectPtr<UWorld>(PC->GetWorld());
        GI->PendingReturnNodeIndex = NodeIndex;
        // save any other state you need here
        AMapCharacter* MapCharacter = Cast<AMapCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

        if (MapCharacter) MapCharacter->SaveData();
    }

    UGameplayStatics::OpenLevelBySoftObjectPtr(PC->GetWorld(), CombatLevel);
}

void UCombatMapData::OnComplete_Implementation(APlayerController* PC)
{
	Super::OnComplete_Implementation(PC);

    if (UMapGameInstance* GI = Cast<UMapGameInstance>(PC->GetGameInstance()))
    {
        UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), GI->PendingReturnLevel);
    }
}
