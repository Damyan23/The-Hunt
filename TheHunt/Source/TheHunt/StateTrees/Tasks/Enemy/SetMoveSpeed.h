// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateTreeTaskBase.h"
#include "Enemy/EnemyCharacter.h"
#include "SetMoveSpeed.generated.h"

USTRUCT()
struct FSetMoveSpeedInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Context)
	TObjectPtr<AEnemyCharacter> Character;

	UPROPERTY(EditAnywhere, Category = Parameters)
	float MoveSpeed = 300.f;
};

USTRUCT(meta = (DisplayName = "Set Move Speed", Category = "Enemy"))
struct THEHUNT_API FSetMoveSpeedTask : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	using FInstanceDataType = FSetMoveSpeedInstanceData;
	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
};