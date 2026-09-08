// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyAIController.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameplayAbilitySystem/BasicAttackAbility.h"
#include "GameplayAbilitySystem/Abilities/BasicBlockingAbility.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AEnemyAIController::AEnemyAIController()
{
    UAIPerceptionComponent* AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"));
    SetPerceptionComponent(*AIPerception);
    PerceptionComponent = AIPerception;

    // Create the sight config (this line was missing)
    SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight"));
    SightConfig->SightRadius = 800.f;
    SightConfig->LoseSightRadius = 1000.f;
    SightConfig->PeripheralVisionAngleDegrees = 70.f;   // forward cone
    SightConfig->SetMaxAge(MemoryDuration);
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
    APawn* AsPawn = Cast<APawn>(Actor);
    if (!AsPawn) return;

    if (Stimulus.WasSuccessfullySensed())
    {
        ForcedTarget = AsPawn;
        LastSeenTime = GetWorld()->GetTimeSeconds();
    }
}

void AEnemyAIController::OnAbilityEnded(const FAbilityEndedData& AbilityEndedData)
{
    
}

void AEnemyAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    APawn* MyPawn = GetPawn();
    if (!MyPawn) return;

    if (APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
    {
        float Dist = FVector::Dist(MyPawn->GetActorLocation(), Player->GetActorLocation());
        if (Dist <= ProximityRadius)
        {
            ForcedTarget = Player;
            LastSeenTime = GetWorld()->GetTimeSeconds();   // refresh memory
        }
    }

    if (ForcedTarget && LastSeenTime >= 0.f)
    {
        if (GetWorld()->GetTimeSeconds() - LastSeenTime > MemoryDuration)
        {
            ForcedTarget = nullptr;
            UE_LOG(LogTemp, Warning, TEXT("ig this sets it to null"));
            LastSeenTime = -1.f;
        }
    }
}

void AEnemyAIController::ForceSeeActor(AActor* Actor)
{
    ForcedTarget = Cast<APawn>(Actor);
    LastSeenTime = GetWorld()->GetTimeSeconds();
    ForcedTargetUntil = GetWorld()->GetTimeSeconds() + MemoryDuration;
}
