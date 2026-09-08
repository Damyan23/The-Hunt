// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatEventMapData.h"
#include "Kismet/GameplayStatics.h"
#include "Sts_Map/CombatEnterWidget.h"
#include "Sts_Map/MapGameInstance.h"
#include "Sts_Map/Character/MapCharacter.h"

void UCombatMapData::OnEnter_Implementation(APlayerController* PC)
{
    Super::OnEnter_Implementation(PC);

    if (UMapGameInstance* GI = Cast<UMapGameInstance>(PC->GetGameInstance()))
    {
        GI->PendingReturnLevel = TSoftObjectPtr<UWorld>(PC->GetWorld());
        GI->PendingReturnNodeIndex = NodeIndex;

        AMapCharacter* MapCharacter = Cast<AMapCharacter>(
            UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
        if (MapCharacter) MapCharacter->SaveData();
    }

    // Create the widget and add it to the viewport
    if (CombatWidgetClass && PC)
    {
        UCombatEnterWidget* EventWidget = CreateWidget<UCombatEnterWidget>(PC, CombatWidgetClass);
        if (EventWidget)
        {
            EventWidget->AddToViewport();

            EventWidget->CombatLevel = this->CombatLevel;
            // So the player can click it, show the cursor and allow UI input
            PC->bShowMouseCursor = true;
            FInputModeGameAndUI InputMode;
            InputMode.SetWidgetToFocus(EventWidget->TakeWidget());
            PC->SetInputMode(InputMode);
        }
    }
}

void UCombatMapData::OnComplete_Implementation(APlayerController* PC)
{
	Super::OnComplete_Implementation(PC);

    if (UMapGameInstance* GI = Cast<UMapGameInstance>(PC->GetGameInstance()))
    {
        UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), GI->PendingReturnLevel);
    }
}
