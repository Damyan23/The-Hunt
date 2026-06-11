// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NodeTypeData.h"
#include "Sts_Map/Node Events/MapEventData.h"
#include "UObject/Class.h"
#include "MapNode.generated.h"

UCLASS()
class AMapNode : public AActor
{
    GENERATED_BODY()

    virtual void OnConstruction(const FTransform& Transform) override;
    AMapNode();

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

