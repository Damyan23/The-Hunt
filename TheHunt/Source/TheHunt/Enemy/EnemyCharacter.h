// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySystem/BaseCharacter.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EEnemyState : uint8
{
    Idle,
    Patrol,
    Chase,
    Alert,
    Attack,
    Stagger,
    Dead
};

UENUM(BlueprintType)
enum class EEnemyCombatState : uint8
{
    None,
    Strafe,
    Attacking,
    Blocking
};

UCLASS()
class THEHUNT_API AEnemyCharacter : public ABaseCharacter
{
	GENERATED_BODY()

	AEnemyCharacter();

protected:
    virtual void BeginPlay() override;

public:
    UPROPERTY(VisibleAnywhere, Category = "AI")
    EEnemyState CurrentState = EEnemyState::Idle;
    UPROPERTY(VisibleAnywhere, Category = "AI")
    EEnemyCombatState CombatState = EEnemyCombatState::None;

    UPROPERTY(EditInstanceOnly, Category = "AI")
    TArray<TObjectPtr<AActor>> PatrolPoints;
};
