// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AITypes.h"
#include "StateTreeTaskBase.h"
#include "UObject/Class.h"
#include "MoveTo.generated.h"

/**
 * 
 */
 // MoveToTarget.h
// MoveToTarget.h
USTRUCT()
struct FMoveToTargetInstanceData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere)
    TObjectPtr<AAIController> AIController = nullptr;

    UPROPERTY(EditAnywhere)
    TObjectPtr<AActor> TargetActor = nullptr;

    UPROPERTY(EditAnywhere)
    float AcceptanceRadius = 150.f;

    UPROPERTY()
    bool bMoveCompleted = false;

    UPROPERTY()
    bool bMoveFailed = false;
};

USTRUCT(meta = (DisplayName = "Move To Target", Category = "Enemy|Movement"))
struct THEHUNT_API FMoveToTarget : public FStateTreeTaskCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FMoveToTargetInstanceData;
    virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }
    virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
    virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;
    virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
};