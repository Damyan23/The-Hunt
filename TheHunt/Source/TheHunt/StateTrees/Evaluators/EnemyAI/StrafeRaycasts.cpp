// Fill out your copyright notice in the Description page of Project Settings.


#include "StateTrees/Evaluators/EnemyAI/StrafeRaycasts.h"

void UStrafeRaycasts::Tick(FStateTreeExecutionContext& Context, const float DeltaTime)
{
	Super::Tick(Context, DeltaTime);

	FVector Right = Character->GetActorLocation() + Character->GetActorRightVector() * TraceDistance;
	FVector Left = Character->GetActorLocation() + (-Character->GetActorRightVector()) * TraceDistance;

	bHitRight = GetWorld()->LineTraceMultiByChannel(Hits, Character->GetActorLocation(), Right, ECC_Visibility);
	bHitLeft = GetWorld()->LineTraceMultiByChannel(Hits, Character->GetActorLocation(), Left, ECC_Visibility);
}