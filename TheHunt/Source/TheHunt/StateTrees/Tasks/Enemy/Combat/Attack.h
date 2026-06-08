// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "StateTreeTaskBase.h"
#include "UObject/Class.h"
#include "Attack.generated.h"

USTRUCT()
struct FAttackInstanceData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = Context)
    TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

    // The actor to face (bind Parameters.CurrentTarget in the StateTree)
    UPROPERTY(EditAnywhere, Category = Context)
    TObjectPtr<AActor> TargetActor = nullptr;

    // Owning enemy, so we can rotate it
    UPROPERTY(EditAnywhere, Category = Context)
    TObjectPtr<AActor> Character = nullptr;

    UPROPERTY(EditAnywhere, Category = Parameters)
    float RotationSpeed = 12.0f;

    // How long after entering to keep rotating toward target (wind-up window)
    UPROPERTY(EditAnywhere, Category = Parameters)
    float RotateTrackDuration = 0.3f;

    UPROPERTY()
    float TimeInState = 0.f;

    UPROPERTY()
    bool bAbilityEnded = false;

    FDelegateHandle AbilityEndedHandle;
};

USTRUCT(meta = (DisplayName = "Attack", Category = "Enemy|Combat"))
struct THEHUNT_API FAttack : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()
	
	using FInstanceDataType = FAttackInstanceData;
	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;

	virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;

	virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
};
