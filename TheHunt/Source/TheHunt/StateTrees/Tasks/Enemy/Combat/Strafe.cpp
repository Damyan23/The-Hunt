// Strafe.cpp
#include "StateTrees/Tasks/Enemy/Combat/Strafe.h"

#include "AIController.h"
#include "StateTreeExecutionContext.h"
#include "GameFramework/CharacterMovementComponent.h"

EStateTreeRunStatus FStrafe::EnterState(FStateTreeExecutionContext& Context,
    const FStateTreeTransitionResult& Transition) const
{
    FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

    if (!InstanceData.Character || !InstanceData.CurrentTarget || !InstanceData.AIController.IsValid())
        return EStateTreeRunStatus::Failed;

    InstanceData.bStrafeDirectionSet = false;
    InstanceData.CurrentStrafeDirection = FVector::ZeroVector;
    InstanceData.StrafeDirectionTimer = 0.f;
    InstanceData.TimeInState = 0.f;
    InstanceData.TargetDuration = FMath::FRandRange(InstanceData.MinDuration, InstanceData.MaxDuration);

    // Face the target while strafing
    InstanceData.AIController->SetFocus(InstanceData.CurrentTarget);

    return EStateTreeRunStatus::Running;
}

EStateTreeRunStatus FStrafe::Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const
{
    FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

    if (!InstanceData.Character || !InstanceData.CurrentTarget)
        return EStateTreeRunStatus::Failed;

    InstanceData.TimeInState += DeltaTime;

    if (InstanceData.TimeInState >= InstanceData.TargetDuration)
        return EStateTreeRunStatus::Succeeded;

    Strafe(InstanceData, DeltaTime);
    return EStateTreeRunStatus::Running;
}

void FStrafe::ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const
{
    FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

    // Clear focus when leaving strafe
    if (InstanceData.AIController.IsValid())
        InstanceData.AIController->ClearFocus(EAIFocusPriority::Gameplay);
}

FVector FStrafe::GetStrafeDirection(FInstanceDataType& InstanceData, const FVector& ToEnemy) const
{
    FVector Right = FVector::CrossProduct(ToEnemy.GetSafeNormal(), FVector::UpVector);

    if (InstanceData.bHitRight)
        return -Right;
    if (InstanceData.bHitLeft)
        return Right;

    return Right;
}

void FStrafe::Strafe(FInstanceDataType& InstanceData, const float DeltaTime) const
{
    if (!InstanceData.Character || !InstanceData.CurrentTarget) return;

    FVector ToEnemy = InstanceData.Character->GetActorLocation()
        - InstanceData.CurrentTarget->GetActorLocation();

    if (!InstanceData.bStrafeDirectionSet)
    {
        InstanceData.CurrentStrafeDirection = GetStrafeDirection(InstanceData, ToEnemy);
        InstanceData.CurrentStrafeDirection.Z = 0.f;
        InstanceData.CurrentStrafeDirection = InstanceData.CurrentStrafeDirection.GetSafeNormal();
        InstanceData.bStrafeDirectionSet = true;
    }

    InstanceData.StrafeDirectionTimer += DeltaTime;
    if (InstanceData.StrafeDirectionTimer >= InstanceData.StrafeDirectionCheckInterval)
    {
        InstanceData.StrafeDirectionTimer = 0.f;
        InstanceData.CurrentStrafeDirection = GetStrafeDirection(InstanceData, ToEnemy);
    }

    if (InstanceData.CurrentStrafeDirection.IsZero())
        return;

    float Distance = ToEnemy.Size();
    FVector MoveDirection = InstanceData.CurrentStrafeDirection;

    if (Distance < InstanceData.StrafeRange)
        MoveDirection += ToEnemy.GetSafeNormal();
    else if (Distance > InstanceData.StrafeRange)
        MoveDirection -= ToEnemy.GetSafeNormal();

    InstanceData.Character->GetCharacterMovement()->MaxWalkSpeed = InstanceData.StrafeMoveSpeed;
    InstanceData.Character->AddMovementInput(MoveDirection.GetSafeNormal(),
        InstanceData.StrafeMoveSpeed * DeltaTime);
}