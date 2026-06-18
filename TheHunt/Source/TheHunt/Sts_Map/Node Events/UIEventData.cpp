// UIEventData.cpp
#include "UIEventData.h"
#include "Sts_Map/Nodes/BaseEventWidget.h"

void UUIEventData::OnEnter_Implementation(APlayerController* PC)
{
    if (!PC || !EventWidget) return;

    Widget = CreateWidget<UBaseEventWidget>(PC, EventWidget);
    if (Widget)
    {
        Widget->EventData = this;
        Widget->AddToViewport();
    }
}

void UUIEventData::OnComplete_Implementation(APlayerController* PC)
{
    if (Widget)
    {
        Widget->RemoveFromParent();
        Widget = nullptr;
    }
}

FRewardEntry UUIEventData::PickReward()
{
    TArray<FRewardEntry>* Pool = nullptr;

    switch (EventType)
    {
    case EUIEventType::ToolUsage:     Pool = &ToolUsageRewardPool;      break;
    case EUIEventType::StrangerTrade: Pool = &StrangerTradeRewardPool;  break;
    case EUIEventType::PushYourLuck:  Pool = &PushYourLuckRewardPool;   break;
    }

    if (!Pool || Pool->IsEmpty()) return FRewardEntry();

    int32 Index = FMath::RandRange(0, Pool->Num() - 1);
    return (*Pool)[Index];
}

bool UUIEventData::RollItemBreak()
{
    return FMath::FRand() < ItemBreakChance;
}

bool UUIEventData::RollRoomFail(int32 RoomIndex)
{
    if (!Rooms.IsValidIndex(RoomIndex)) return false;
    return FMath::FRand() < Rooms[RoomIndex].FailChance;
}

TArray<FRewardEntry> UUIEventData::PickRoomRewards(int32 RoomIndex)
{
    TArray<FRewardEntry> Results;
    if (!Rooms.IsValidIndex(RoomIndex) || PushYourLuckRewardPool.IsEmpty()) return Results;

    int32 Count = Rooms[RoomIndex].RewardCount;
    TArray<FRewardEntry> Available = PushYourLuckRewardPool;

    for (int32 i = 0; i < Count && Available.Num() > 0; i++)
    {
        int32 Index = FMath::RandRange(0, Available.Num() - 1);
        Results.Add(Available[Index]);
        Available.RemoveAt(Index);
    }

    return Results;
}

float UUIEventData::GetRoomFailChance(int32 RoomIndex) const
{
    if (!Rooms.IsValidIndex(RoomIndex)) return 0.0f;
    return Rooms[RoomIndex].FailChance;
}

float UUIEventData::GetRoomDamage(int32 RoomIndex) const
{
    if (!Rooms.IsValidIndex(RoomIndex)) return 0.0f;
    return Rooms[RoomIndex].DamageOnFail;
}

int32 UUIEventData::GetRoomCount() const
{
    return Rooms.Num();
}

UPerkData* UUIEventData::GetRandomPerk()
{
    if (PerksPool.Num() > 0)
    {
        int32 Index = FMath::RandRange(0, PerksPool.Num() - 1);
        return  PerksPool[Index];
    }

    return nullptr;
}

URuneBase* UUIEventData::GetRandomRune()
{
    if (RunesPool.Num() > 0)
    {
        int32 Index = FMath::RandRange(0, RunesPool.Num() - 1);
        return  RunesPool[Index];
    }

    return nullptr;
}
