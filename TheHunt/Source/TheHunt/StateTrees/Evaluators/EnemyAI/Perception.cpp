// Fill out your copyright notice in the Description page of Project Settings.


#include "StateTrees/Evaluators/EnemyAI/Perception.h"

#include "Perception/AIPerceptionComponent.h"

void UPerception::TreeStart(FStateTreeExecutionContext& Context)
{
	Super::TreeStart(Context);

	if (AIController.IsValid())
	{
		AIController->GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &UPerception::OnStimulusUpdated);
	}
}

void UPerception::TreeStop(FStateTreeExecutionContext& Context)
{
	Super::TreeStop(Context);
}

void UPerception::Tick(FStateTreeExecutionContext& Context, const float DeltaTime)
{
	Super::Tick(Context, DeltaTime);

	if (AIController->ForcedTarget &&
		GetWorld()->GetTimeSeconds() < AIController->ForcedTargetUntil)
	{
		CurrentTarget = AIController->ForcedTarget;
	}
}

void UPerception::OnStimulusUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (Actor->IsA<AEnemyCharacter>()) return;

	if (Stimulus.WasSuccessfullySensed())
	{
		CurrentTarget = Actor;
		OnSightStimulus(Actor, Stimulus);
	}
}
