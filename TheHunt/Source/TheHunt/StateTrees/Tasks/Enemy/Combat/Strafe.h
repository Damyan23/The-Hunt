// Strafe.h
#pragma once
#include "CoreMinimal.h"
#include "StateTreeTaskBase.h"
#include "Enemy/EnemyAIController.h"
#include "Enemy/EnemyCharacter.h"
#include "InputPlayer/PlayerCharacter.h"
#include "Strafe.generated.h"

USTRUCT()
struct FStrafeInstanceData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = Context)
    TObjectPtr<AEnemyCharacter> Character = nullptr;

    UPROPERTY(EditAnywhere, Category = Input)
    TObjectPtr<AActor> CurrentTarget = nullptr;

    UPROPERTY(EditAnywhere, Category = Context)
    TWeakObjectPtr<AEnemyAIController> AIController;

    UPROPERTY(EditAnywhere)
    float StrafeRange = 300.f;

    UPROPERTY(EditAnywhere)
    float StrafeMoveSpeed = 300.f;

    UPROPERTY(EditAnywhere)
    float StrafeDirectionCheckInterval = 2.f;

    UPROPERTY(EditAnywhere, Category = Input)
    bool bHitRight = false;

    UPROPERTY(EditAnywhere, Category = Input)
    bool bHitLeft = false;

    UPROPERTY()
    bool bStrafeDirectionSet = false;

    UPROPERTY()
    FVector CurrentStrafeDirection = FVector::ZeroVector;

    UPROPERTY()
    float StrafeDirectionTimer = 0.f;

    UPROPERTY(EditAnywhere)
    float MinDuration = 1.5f;

    UPROPERTY(EditAnywhere)
    float MaxDuration = 3.5f;

    UPROPERTY()
    float TargetDuration = 0.f;

    UPROPERTY()
    float TimeInState = 0.f;
};

USTRUCT(meta = (DisplayName = "Strafe", Category = "Enemy|Combat"))
struct THEHUNT_API FStrafe : public FStateTreeTaskCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FStrafeInstanceData;
    virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }

    virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;

    virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;

    virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;

private:
    FVector GetStrafeDirection(FInstanceDataType& InstanceData, const FVector& ToEnemy) const;
    void Strafe(FInstanceDataType& InstanceData, const float DeltaTime) const;
};