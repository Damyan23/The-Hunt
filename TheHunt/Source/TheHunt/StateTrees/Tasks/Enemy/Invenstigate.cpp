// Fill out your copyright notice in the Description page of Project Settings.

#include "StateTrees/Tasks/Enemy/Invenstigate.h"
#include "StateTreeExecutionContext.h"

EStateTreeRunStatus FInvestigate::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const
{
    FInstanceDataType& InstanceData = Context.GetInstanceData(*this);
    InstanceData.TimeInState = 0.f;

    if (InstanceData.AIController)
        InstanceData.AIController->StopMovement();

    return EStateTreeRunStatus::Running;
}

EStateTreeRunStatus FInvestigate::Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const
{
    FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

    if (!InstanceData.CurrentTarget)
    {
        return EStateTreeRunStatus::Failed;
    }


    // rotate toward target
    if (InstanceData.Character && InstanceData.CurrentTarget)
    {
        FVector Direction = (InstanceData.CurrentTarget->GetActorLocation() - InstanceData.Character->GetActorLocation()).GetSafeNormal();
        FRotator TargetRotation = Direction.Rotation();
        FRotator NewRotation = FMath::RInterpTo(InstanceData.Character->GetActorRotation(), TargetRotation, DeltaTime, 5.0f);
        InstanceData.Character->SetActorRotation(NewRotation);
    }

    InstanceData.TimeInState += DeltaTime;
    if (InstanceData.TimeInState >= InstanceData.ConfirmTime)
    {
        return EStateTreeRunStatus::Succeeded;
    }   
    return EStateTreeRunStatus::Running;
}
