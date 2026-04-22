// Fill out your copyright notice in the Description page of Project Settings.

#include "StateTrees/Tasks/Enemy/Patrol.h"
#include "StateTreeExecutionContext.h"

EStateTreeRunStatus FPatrolTask::EnterState(FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition) const
{
	return EStateTreeRunStatus::Running;
}

EStateTreeRunStatus FPatrolTask::Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const
{
	FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

	if (!InstanceData.Character || !InstanceData.AIController) return EStateTreeRunStatus::Failed;
	if (InstanceData.Character->PatrolPoints.IsEmpty()) return EStateTreeRunStatus::Running;

	GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Green,
		FString::Printf(TEXT("Patrol - Index: %d"), InstanceData.CurrentPatrolIndex));

	AActor* Target = InstanceData.Character->PatrolPoints[InstanceData.CurrentPatrolIndex];
	InstanceData.CurrentTarget = Target;

	float Distance = InstanceData.Character->GetDistanceTo(Target);
	if (Distance < InstanceData.StoppingDistance + 40.f)
	{
		InstanceData.CurrentPatrolIndex = (InstanceData.CurrentPatrolIndex + 1) % InstanceData.Character->PatrolPoints.Num();
	}

	InstanceData.AIController->MoveToActor(Target, 10.0f);

	return EStateTreeRunStatus::Running;
}




