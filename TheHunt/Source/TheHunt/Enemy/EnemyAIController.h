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
    TObjectPtr<APawn> TargetPlayer;

protected:
    virtual void OnPossess(APawn* InPawn) override;

    // Perception
    UPROPERTY(VisibleAnywhere)
    TObjectPtr<UAISenseConfig_Sight> SightConfig;

    UFUNCTION()
    void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

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
};