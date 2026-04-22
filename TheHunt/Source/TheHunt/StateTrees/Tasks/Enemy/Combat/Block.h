// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "StateTreeTaskBase.h"
#include "Enemy/EnemyCharacter.h"
#include "UObject/Class.h"
#include "Block.generated.h"


USTRUCT()
struct FBlockInstanceData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = Context)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;
	UPROPERTY(EditAnywhere, Category = Context)
	TObjectPtr<AEnemyCharacter> Character;

	UPROPERTY(EditAnywhere, Category = Parameters)
	float MinDuration = 1.5f;

	UPROPERTY(EditAnywhere, Category = Parameters)
	float MaxDuration = 4.0f;

	UPROPERTY()
	float TargetDuration = 0.f;

	UPROPERTY()
	float TimeInState = 0.f;

	UPROPERTY()
	bool bAbilityEnded = false;

	UPROPERTY()
	bool bExitRequested = false;

	FDelegateHandle AbilityEndedHandle;
};

USTRUCT(meta = (DisplayName = "Block", Category = "Enemy|Combat"))
struct THEHUNT_API FBlock : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	using FInstanceDataType = FBlockInstanceData;
	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;

	virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;

	virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
};