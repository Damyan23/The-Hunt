// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateTreeTaskBase.h"
#include "Enemy/EnemyCharacter.h"
#include "UObject/Class.h"
#include "Stagger.generated.h"

USTRUCT()
struct FStaggerInstandeData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Parameter")
	TObjectPtr<UAnimMontage> StaggerMontage;

	UPROPERTY(EditAnywhere, Category = Context)
	TObjectPtr<AEnemyCharacter> Character;
	UPROPERTY(EditAnywhere, Category = Context)
	TWeakObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditAnywhere, Category = "Parameter")
	float StaggerDuration = 1.f;

	UPROPERTY()
	float ElapsedTime = 0.f;

	UPROPERTY()
	bool bPlayingExit = false;

	float ExitElapsedTime = 0.f;

	UPROPERTY(EditAnywhere, Category = "Stagger")
	TObjectPtr<UAnimMontage> BlockReactionMontage;
	bool bBlockReactionDone = false;

	UPROPERTY(EditAnywhere, Category = "Stagger")
	float PostStaggerDelay = 0.5f;

	bool bWaitingPostDelay = false;
	float PostDelayElapsed = 0.f;

	UPROPERTY(EditAnywhere, Category = "Stagger")
	TObjectPtr<UAnimMontage> StaggerExitMontage;

	float StaggerExitDuration = 0;
};

USTRUCT(meta = (DisplayName = "Stagger", Category = "Enemy"))
struct THEHUNT_API FStagger : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()
	
	using FInstanceDataType = FStaggerInstandeData;
	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); };

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
	virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;
};
