// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateTreeTaskBase.h"
#include "Enemy/EnemyAIController.h"
#include "Enemy/EnemyCharacter.h"
#include "Patrol.generated.h"

USTRUCT()
struct FPatrolInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Context)
	TObjectPtr<AEnemyCharacter> Character;

	UPROPERTY(EditAnywhere, Category = Context)
	TObjectPtr<AEnemyAIController> AIController;

	UPROPERTY(EditAnywhere, Category = Parameters)
	float StoppingDistance = 200.f;

	UPROPERTY()
	int32 CurrentPatrolIndex = 0;

	UPROPERTY()
	TObjectPtr<AActor> CurrentTarget;
};

USTRUCT(meta = (DisplayName = "Patrol", Category = "Enemy"))
struct THEHUNT_API FPatrolTask : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	using FInstanceDataType = FPatrolInstanceData;
	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;

	virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;
};
