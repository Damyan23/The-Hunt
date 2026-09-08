// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NodeTypeData.h"
#include "Components/PointLightComponent.h"
#include "Sts_Map/Node Events/MapEventData.h"
#include "UObject/Class.h"
#include "MapNode.generated.h"

UCLASS()
class AMapNode : public AActor
{
    GENERATED_BODY()

    virtual void OnConstruction(const FTransform& Transform) override;
    AMapNode();

protected:
    virtual void NotifyActorOnClicked(FKey ButtonPressed = EKeys::LeftMouseButton) override;
    virtual void NotifyActorBeginCursorOver() override;
    virtual void NotifyActorEndCursorOver() override;
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

private:
    bool bIsHovered = false;
    float HoverInterpSpeed = 8.f;     // how fast it lerps

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TObjectPtr<UPointLightComponent> HoverLight;

    float HoverLightIntensity = 7000.f;

    UPROPERTY(EditDefaultsOnly)
    TObjectPtr<USoundBase> HoverSoundFX;



public:
    UPROPERTY(BlueprintReadOnly)
    int32 PointIndex = -1;

    ENodeType NodeType;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    TObjectPtr<UTexture2D> Icon;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TArray<AMapNode*> NextNodes;

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void OnEnter(APlayerController* PC);

    UPROPERTY()
    TObjectPtr<UMapEventData> Event;

    UFUNCTION()
    void AssignEvent(UMapEventData* AssignedEvent);

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TObjectPtr<UStaticMeshComponent> MeshComponent;

    UPROPERTY()
    TObjectPtr<AMapNode> GraphNode;

    UMapEventData* GetAssignedEvent() { return Event; }
};

