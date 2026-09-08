#pragma once
#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyCharacter.h"
#include "Components/StateTreeComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "EnemyAIController.generated.h"

UCLASS()
class THEHUNT_API AEnemyAIController : public AAIController
{
    GENERATED_BODY()

    AEnemyAIController();

public:
    UPROPERTY()
    TObjectPtr<APawn> ForcedTarget;

    float ForcedTargetUntil = -1.f;

protected:
    virtual void OnPossess(APawn* InPawn) override;
    virtual FGenericTeamId GetGenericTeamId() const override { return FGenericTeamId(1); }   // team 1 = enemies

    // Perception
    UPROPERTY(VisibleAnywhere)
    TObjectPtr<UAISenseConfig_Sight> SightConfig;

    UFUNCTION()
    void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

    float LastSeenTime = -1.f;

    UPROPERTY(EditAnywhere, Category = "AI")
    float MemoryDuration = 5.f;

public:
    void ForceSeeActor(AActor* Actor);

    // Animation
    UPROPERTY()
    TObjectPtr<UAnimInstance> AnimInstance;
    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    TObjectPtr<UAnimMontage> BlockMontage;

    // ASC
    UPROPERTY()
    TObjectPtr<UAbilitySystemComponent> ASC;
    UFUNCTION()
    void OnAbilityEnded(const FAbilityEndedData& AbilityEndedData);

    // Block state — kept for OnAbilityEnded cleanup
    bool bBlock = false;

    float DefaultMoveSpeed;

    UPROPERTY(VisibleAnywhere, Category = "AI")
    TObjectPtr<UStateTreeComponent> StateTreeComponent;

    virtual void Tick(float DeltaSeconds) override;
    UPROPERTY(EditAnywhere, Category = "AI") float ProximityRadius = 250.f;
};