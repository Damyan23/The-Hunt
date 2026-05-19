// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeEvaluatorBlueprintBase.h"
#include "Enemy/EnemyCharacter.h"
#include "StrafeRaycasts.generated.h"

/**
 * 
 */
UCLASS()
class THEHUNT_API UStrafeRaycasts : public UStateTreeEvaluatorBlueprintBase
{
	GENERATED_BODY()

protected:
	virtual void Tick(FStateTreeExecutionContext& Context, const float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Output)
	bool bHitRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Output)
	bool bHitLeft;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Context)
	TObjectPtr<AEnemyCharacter> Character;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float TraceDistance = 150.0f;
private:
	TArray<FHitResult> Hits;
};
