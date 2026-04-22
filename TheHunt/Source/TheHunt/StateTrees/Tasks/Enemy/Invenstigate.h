// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateTreeTaskBase.h"
#include "Enemy/EnemyAIController.h"
#include "Enemy/EnemyCharacter.h"
#include "Invenstigate.generated.h"

USTRUCT()
struct FInvestigateInstanceData
{
    GENERATED_BODY()
    
    UPROPERTY(VisibleAnywhere, Category = Context)
    TObjectPtr<AEnemyCharacter> Character;
    UPROPERTY(VisibleAnywhere, Category = Context)
    TObjectPtr<AEnemyAIController> AIController;
    UPROPERTY(VisibleAnywhere, Category = Context)
    TObjectPtr<AActor> CurrentTarget;

    UPROPERTY(EditAnywhere, Category = Parameters)
    float ConfirmTime = 1.0f;

    float TimeInState = 0.f;

    UPROPERTY()
    TObjectPtr<AActor> CachedTarget;
};

USTRUCT(meta = (DisplayName = "Investigate", Category = "Enemy"))
struct THEHUNT_API FInvestigate : public FStateTreeTaskCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FInvestigateInstanceData;
    virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }

    virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;

    virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;
};
