// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeEvaluatorBlueprintBase.h"
#include "Enemy/EnemyCharacter.h"
#include "GameplayAbilitySystem/BaseAttributeSet.h"
#include "CombatStats.generated.h"

/**
 * 
 */
UCLASS()
class THEHUNT_API UCombatStats : public UStateTreeEvaluatorBlueprintBase
{
	GENERATED_BODY()
	
protected:
	virtual void TreeStart(FStateTreeExecutionContext& Context) override;
	virtual void Tick(FStateTreeExecutionContext& Context, const float DeltaTime) override;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Context)
	TObjectPtr<AEnemyCharacter> Character;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Output)
	float HealthPercentage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Output)
	float StaminaPercentage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Output)
	float StaggerPercentage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Output)
	float Stamina;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Output)
	FGameplayTagContainer TagContainer;

	void OnHealthChanged(const FOnAttributeChangeData& Data);
	void OnStaminaChanged(const FOnAttributeChangeData& Data);
	void OnStaggerChanged(const FOnAttributeChangeData& Data);

	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> AttackStaminaCostEffect;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Output)
	float AttackStaminaCost = 0.f;

};
