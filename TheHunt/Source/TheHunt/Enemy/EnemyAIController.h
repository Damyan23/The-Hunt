// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyCharacter.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Sight.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class THEHUNT_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	AEnemyAIController();

	UPROPERTY()
	TObjectPtr<APawn> TargetPlayer;

	UPROPERTY()
	TObjectPtr<AEnemyCharacter> Enemy;
	int CurrentPatrolIndex;
	TObjectPtr<AActor> CurrentTarget;

protected:

// ============================================================
// Overrides
// ============================================================
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaSeconds) override;

// ============================================================
// AI Settings
// ============================================================
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float StoppingRange = 200.f;
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float AttackRange = 50.f;
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float StrafeMoveSpeed = 20.;
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float StrafeRange = 150.f;
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float StrafeDirectionCheckInterval = 1.f;
	FVector CurrentStrafeDirection;
	bool bStrafeDirectionSet;
	float StrafeDirectionTimer = 0.0f;
	float DefaultMoveSpeed;
	float DecisionTimer = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float MinDecisionTime = 0.5f;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float MaxDecisionTime = 2.0f;
// ============================================================
// Animation Settings
// ============================================================
	UPROPERTY()
	TObjectPtr<UAnimInstance> AnimInstance;
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	TObjectPtr<UAnimMontage> AttackMontage;
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	TObjectPtr<UAnimMontage> BlockMontage;

// ============================================================
// State Update
// ============================================================
	UFUNCTION()
	void UpdateCurrentState();
	UFUNCTION()
	void UpdateChaseState();
	UFUNCTION()
	void UpdateAlertState();
	UFUNCTION()
	void UpdatePatrolState();

// ============================================================
// Combat
// ============================================================
	UFUNCTION()
	void UpdateAttackState();
	UFUNCTION()
	void MakeCombatDecision();
	UFUNCTION()
	void Strafe();
	FVector GetStrafeDirection(const FVector& ToEnemy) const;
	UFUNCTION()
	void Attack();
	bool bIsAttacking;
	UFUNCTION()
	void Block();
	bool bBlock;
	bool bBlockExiting;
	EEnemyCombatState PendingCombatState;
	UFUNCTION()
	void StartBlock();
	UFUNCTION()
	void StopBlock();

// ============================================================
// Perception
// ============================================================

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAISenseConfig_Sight> SightConfig;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAISenseConfig_Hearing> HearingConfig;

	UFUNCTION()
	void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
	UFUNCTION()
	void OnAlertTimerExpired();
	FTimerHandle AlertTimerHandle;

// ============================================================
// ASC
// ============================================================
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> ASC;
	UFUNCTION()
	void OnAbilityEnded(const FAbilityEndedData& AbilityEndedData);
};


