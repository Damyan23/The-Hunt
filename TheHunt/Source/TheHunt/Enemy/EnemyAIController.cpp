// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyAIController.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameplayAbilitySystem/BasicAttackAbility.h"
#include "GameplayAbilitySystem/Abilities/BasicBlockingAbility.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AEnemyAIController::AEnemyAIController()
{
    UAIPerceptionComponent* AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"));
    SetPerceptionComponent(*AIPerception);
    PerceptionComponent = AIPerception;

    SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight"));
    SightConfig->SightRadius = 500.f;
    SightConfig->LoseSightRadius = 700.f;
    SightConfig->DetectionByAffiliation.bDetectEnemies = true;
    SightConfig->DetectionByAffiliation.bDetectNeutrals = false;
    SightConfig->DetectionByAffiliation.bDetectFriendlies = false;

    PerceptionComponent->ConfigureSense(*SightConfig);
    PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnPerceptionUpdated);

    StateTreeComponent = CreateDefaultSubobject<UStateTreeComponent>(TEXT("StateTree"));
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    PerceptionComponent->RequestStimuliListenerUpdate();
    StateTreeComponent->StartLogic();
}

void AEnemyAIController::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{   
    if (Stimulus.WasSuccessfullySensed())
        TargetPlayer = Cast<APawn>(Actor);
    else
        TargetPlayer = nullptr;
}

void AEnemyAIController::OnAbilityEnded(const FAbilityEndedData& AbilityEndedData)
{
    
}