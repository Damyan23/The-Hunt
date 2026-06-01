// UIEventData.h
#pragma once
#include "CoreMinimal.h"
#include "MapEventData.h"
#include "Items/ItemType.h"
#include "RewardEntry.h"
#include "UIEventData.generated.h"

class UBaseEventWidget;

UENUM(BlueprintType)
enum class EUIEventType : uint8
{
    ToolUsage       UMETA(DisplayName = "Tool Usage"),
    StrangerTrade   UMETA(DisplayName = "Stranger Trade"),
    PushYourLuck    UMETA(DisplayName = "Push Your Luck")
};

USTRUCT(BlueprintType)
struct FDungeonRoom
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Room")
    FText RoomName;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Room")
    float FailChance = 0.2f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Room")
    int32 RewardCount = 1;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Room")
    float DamageOnFail = 20.0f;
};

UCLASS()
class THEHUNT_API UUIEventData : public UMapEventData
{
    GENERATED_BODY()

    virtual void OnEnter_Implementation(APlayerController* PC) override;
    virtual void OnComplete_Implementation(APlayerController* PC) override;

public:

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    EUIEventType EventType;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TSubclassOf<UBaseEventWidget> EventWidget;

    UPROPERTY()
    TObjectPtr<UBaseEventWidget> Widget;

    // Tool Usage specific
    UPROPERTY(EditDefaultsOnly, Category = "UI|Tool Usage", meta = (EditCondition = "EventType == EUIEventType::ToolUsage"))
    EItemType RequiredItemType;

    UPROPERTY(EditDefaultsOnly, Category = "UI|Tool Usage", meta = (EditCondition = "EventType == EUIEventType::ToolUsage"))
    float ItemBreakChance = 0.2f;

    UPROPERTY(EditDefaultsOnly, Category = "UI|Tool Usage", meta = (EditCondition = "EventType == EUIEventType::ToolUsage"))
    TArray<FRewardEntry> ToolUsageRewardPool;

    // Stranger Trade specific
    UPROPERTY(EditDefaultsOnly, Category = "UI|Stranger Trade", meta = (EditCondition = "EventType == EUIEventType::StrangerTrade"))
    TArray<FString> GoodItemIDs;

    UPROPERTY(EditDefaultsOnly, Category = "UI|Stranger Trade", meta = (EditCondition = "EventType == EUIEventType::StrangerTrade"))
    TArray<FRewardEntry> NegativeOutcomes;

    UPROPERTY(EditDefaultsOnly, Category = "UI|Stranger Trade", meta = (EditCondition = "EventType == EUIEventType::StrangerTrade"))
    TArray<FRewardEntry> StrangerTradeRewardPool;

    // Push Your Luck specific
    UPROPERTY(EditDefaultsOnly, Category = "UI|Push Your Luck", meta = (EditCondition = "EventType == EUIEventType::PushYourLuck"))
    TArray<FRewardEntry> PushYourLuckRewardPool;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI|Push Your Luck", meta = (EditCondition = "EventType == EUIEventType::PushYourLuck"))
    TArray<FDungeonRoom> Rooms;
        
    // Shared helpers
    UFUNCTION(BlueprintCallable, Category = "UI Event")
    FRewardEntry PickReward();

    UFUNCTION(BlueprintCallable, Category = "UI Event")
    bool RollItemBreak();

    // Push Your Luck helpers
    UFUNCTION(BlueprintCallable, Category = "UI Event|Push Your Luck")
    bool RollRoomFail(int32 RoomIndex);

    UFUNCTION(BlueprintCallable, Category = "UI Event|Push Your Luck")
    TArray<FRewardEntry> PickRoomRewards(int32 RoomIndex);

    UFUNCTION(BlueprintCallable, Category = "UI Event|Push Your Luck")
    float GetRoomFailChance(int32 RoomIndex) const;

    UFUNCTION(BlueprintCallable, Category = "UI Event|Push Your Luck")
    float GetRoomDamage(int32 RoomIndex) const;

    UFUNCTION(BlueprintCallable, Category = "UI Event|Push Your Luck")
    int32 GetRoomCount() const;
};