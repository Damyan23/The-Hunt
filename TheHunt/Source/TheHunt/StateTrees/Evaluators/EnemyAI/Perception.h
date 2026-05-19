// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeEvaluatorBlueprintBase.h"
#include "Enemy/EnemyAIController.h"
#include "Enemy/EnemyCharacter.h"
#include "Perception.generated.h"

/**
 * 
 */
UCLASS()
class THEHUNT_API UPerception : public UStateTreeEvaluatorBlueprintBase
{
	GENERATED_BODY()
	
protected:
	virtual void TreeStart(FStateTreeExecutionContext& Context) override;
	virtual void TreeStop(FStateTreeExecutionContext& Context) override;

#if WITH_EDITOR
	virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting) const
	{
		return NSLOCTEXT("STE_Percpetion", "PerceptionDisc", "Monitors the Context Actor's perceptions");
	};
#endif

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Context)
	TObjectPtr<AEnemyCharacter> Character;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Context)
	TWeakObjectPtr<AEnemyAIController> AIController;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Output)
	TObjectPtr<AActor> CurrentTarget = nullptr;

	UFUNCTION()
	void OnStimulusUpdated(AActor* Actor, FAIStimulus Stimulus);
	UFUNCTION(BlueprintImplementableEvent, Category = "Perception")
	void OnSightStimulus(AActor* Actor, const FAIStimulus Stimulus);
	UFUNCTION(BlueprintImplementableEvent, Category = "Perception")
	void OnSightStimulusForgotten(AActor* Actor, const FAIStimulus Stimulus);
};
