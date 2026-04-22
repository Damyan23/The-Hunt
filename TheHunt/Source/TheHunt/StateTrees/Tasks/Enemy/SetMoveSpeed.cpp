// Fill out your copyright notice in the Description page of Project Settings.

#include "StateTrees/Tasks/Enemy/SetMoveSpeed.h"
#include "StateTreeExecutionContext.h"
#include "GameFramework/CharacterMovementComponent.h"

EStateTreeRunStatus FSetMoveSpeedTask::EnterState(FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition) const
{
	FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

	if (InstanceData.Character)
	{
		InstanceData.Character->GetCharacterMovement()->MaxWalkSpeed = InstanceData.MoveSpeed;
	}

	return EStateTreeRunStatus::Succeeded;
}