// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeEvaluatorBlueprintBase.h"
#include "Enemy/EnemyAIController.h"
#include "Distance.generated.h"

/**
 * 
 */
UCLASS()
class THEHUNT_API UDistance : public UStateTreeEvaluatorBlueprintBase
{
	GENERATED_BODY()
	
protected:
	virtual void TreeStart(FStateTreeExecutionContext& Context) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Output)
	float DisntanceToPlayer;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Context)
	TObjectPtr<AEnemyCharacter> Character;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Context)
	TObjectPtr<AActor> CurrentTarget = nullptr;

};
