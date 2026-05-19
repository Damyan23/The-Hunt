// Fill out your copyright notice in the Description page of Project Settings.


#include "StateTrees/Tasks/Enemy/MoveTo.h"
#include "StateTreeExecutionContext.h"
#include "Navigation/PathFollowingComponent.h"

EStateTreeRunStatus FMoveToTarget::EnterState(FStateTreeExecutionContext& Context,
    const FStateTreeTransitionResult& Transition) const
{
    FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

    if (!InstanceData.AIController || !InstanceData.TargetActor)
    {
        UE_LOG(LogTemp, Error, TEXT("MoveToTarget FAILED on enter - Controller: %s | Target: %s"),
            InstanceData.AIController ? TEXT("valid") : TEXT("NULL"),
            InstanceData.TargetActor ? TEXT("valid") : TEXT("NULL"));
        return EStateTreeRunStatus::Failed;
    }

    InstanceData.bMoveCompleted = false;
    InstanceData.bMoveFailed = false;

    UE_LOG(LogTemp, Warning, TEXT("MoveToTarget - Moving to: %s | AcceptanceRadius: %.1f"),
        *InstanceData.TargetActor->GetName(), InstanceData.AcceptanceRadius);

    EPathFollowingRequestResult::Type Result = InstanceData.AIController->MoveToActor(
        InstanceData.TargetActor,
        InstanceData.AcceptanceRadius,
        true, true, false, nullptr, false
    );

    if (Result == EPathFollowingRequestResult::Failed)
    {
        UE_LOG(LogTemp, Error, TEXT("MoveToTarget - MoveToActor request FAILED"));
        return EStateTreeRunStatus::Failed;
    }

    if (Result == EPathFollowingRequestResult::AlreadyAtGoal)
    {
        UE_LOG(LogTemp, Warning, TEXT("MoveToTarget - Already at goal, SUCCEEDED immediately"));
        return EStateTreeRunStatus::Succeeded;
    }

    UE_LOG(LogTemp, Warning, TEXT("MoveToTarget - Move request accepted, Running"));
    return EStateTreeRunStatus::Running;
}

EStateTreeRunStatus FMoveToTarget::Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const
{
    FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

    if (!InstanceData.AIController || !InstanceData.TargetActor)
    {
        UE_LOG(LogTemp, Error, TEXT("MoveToTarget Tick - Controller or Target became NULL"));
        return EStateTreeRunStatus::Failed;
    }

    UPathFollowingComponent* PFC = InstanceData.AIController->GetPathFollowingComponent();
    if (!PFC)
    {
        UE_LOG(LogTemp, Error, TEXT("MoveToTarget Tick - No PathFollowingComponent"));
        return EStateTreeRunStatus::Failed;
    }

    EPathFollowingStatus::Type Status = PFC->GetStatus();

    if (Status == EPathFollowingStatus::Idle)
    {
        float Distance = InstanceData.AIController->GetPawn()
            ->GetDistanceTo(InstanceData.TargetActor);

        if (Distance <= InstanceData.AcceptanceRadius + 50)
        {
            UE_LOG(LogTemp, Warning, TEXT("MoveToTarget SUCCEEDED - Distance: %.1f | Radius: %.1f"),
                Distance, InstanceData.AcceptanceRadius);
            return EStateTreeRunStatus::Succeeded;
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("MoveToTarget FAILED - Stopped but too far. Distance: %.1f | Radius: %.1f"),
                Distance, InstanceData.AcceptanceRadius);
            return EStateTreeRunStatus::Failed;
        }
    }

    if (Status == EPathFollowingStatus::Waiting)
    {
        UE_LOG(LogTemp, Error, TEXT("MoveToTarget FAILED - PathFollowing stuck in Waiting"));
        return EStateTreeRunStatus::Failed;
    }

    return EStateTreeRunStatus::Running;
}

void FMoveToTarget::ExitState(FStateTreeExecutionContext& Context,
    const FStateTreeTransitionResult& Transition) const
{
    FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

    if (InstanceData.AIController)
        InstanceData.AIController->StopMovement();
}