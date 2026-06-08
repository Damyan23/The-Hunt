// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySystem/BaseCharacter.h" 
#include "EnemyCharacter.generated.h"

UCLASS()
class THEHUNT_API AEnemyCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
    AEnemyCharacter();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;
    virtual void OnDeath() override;

    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    TObjectPtr<UAnimMontage> StaggerMontage;

    UPROPERTY(EditDefaultsOnly, Category = "Stagger")
    float StunDuration = 1.5f;
    virtual void OnGuardBroken() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Dying")
    float FreezeAfterDeathDuration = 10.0f;


public:
    UPROPERTY(EditInstanceOnly, Category = "AI")
    TArray<TObjectPtr<AActor>> PatrolPoints;

    void OpenParryWindow();
    void CloseParryWindow();
    bool SetStagger();

private:
    FTimerHandle ParryWindowTimer;
};
