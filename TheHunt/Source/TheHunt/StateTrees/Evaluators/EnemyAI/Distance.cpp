// Fill out your copyright notice in the Description page of Project Settings.


#include "StateTrees/Evaluators/EnemyAI/Distance.h"

void UDistance::TreeStart(FStateTreeExecutionContext& Context)
{
	Super::TreeStart(Context);

	if (Character && CurrentTarget) DisntanceToPlayer = Character->GetDistanceTo(CurrentTarget);
}
