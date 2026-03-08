// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyAIController.h"

#include "Kismet/GameplayStatics.h"
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
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

	PerceptionComponent->ConfigureSense(*SightConfig);
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnPerceptionUpdated);
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	Enemy = Cast<AEnemyCharacter>(GetPawn());
	PerceptionComponent->RequestStimuliListenerUpdate();
}


void AEnemyAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!TargetPlayer)
	{
		TargetPlayer = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		CurrentTarget = TargetPlayer;
		SetFocus(CurrentTarget, 0);
		return;
	}

	UpdateCurrentState();
}


void AEnemyAIController::UpdateCurrentState()
{
	if (!Enemy) return;

	switch (Enemy->CurrentState)
	{
		case EEnemyState::Patrol: UpdatePatrolState(); break;
		case EEnemyState::Chase:  UpdateChaseState();  break;
		case EEnemyState::Attack: UpdateAttackState(); break;
		case EEnemyState::Alert:  UpdateAlertState();  break;
		default:                  UpdatePatrolState(); break;
	}
}

void AEnemyAIController::UpdateChaseState()
{
	if (!TargetPlayer || !GetPawn()) return;

	float Distance = Enemy->GetDistanceTo(TargetPlayer);
	FVector ToEnemy = Enemy->GetActorLocation() - TargetPlayer->GetActorLocation();
	FVector TargetLocation = TargetPlayer->GetActorLocation() + ToEnemy.GetSafeNormal() * AttackRange;

	if (FMath::IsNearlyEqual(Distance, AttackRange, 40.f))
	{
		Enemy->CurrentState = EEnemyState::Attack;
		Enemy->CombatState = EEnemyCombatState::Strafe;
	}
	else
	{
		CurrentTarget = TargetPlayer;
		MoveToLocation(TargetLocation, -1.f);
	}
}

void AEnemyAIController::UpdateAlertState()
{

}

void AEnemyAIController::UpdatePatrolState()
{
	if (Enemy->PatrolPoints.IsEmpty()) return;

	AActor* Target = Enemy->PatrolPoints[CurrentPatrolIndex];
	CurrentTarget = Target;
	float Distance = Enemy->GetDistanceTo(Target);

	if (Distance < AttackRange + 40.f)
	{
		CurrentPatrolIndex = (CurrentPatrolIndex + 1) % Enemy->PatrolPoints.Num();
	}

	MoveToActor(Target, 10.0f);
}

void AEnemyAIController::UpdateAttackState()
{
	if (!Enemy || !TargetPlayer) return;

	float Distance = Enemy->GetDistanceTo(TargetPlayer);
	CurrentTarget = TargetPlayer;

	if (Distance > AttackRange  + 40.f)
	{
		Enemy->CurrentState = EEnemyState::Chase;
		Enemy->CombatState = EEnemyCombatState::None;
	}

	switch (Enemy->CombatState)
	{
		case EEnemyCombatState::None: break;
		case EEnemyCombatState::Strafe: Strafe(); break;
		case EEnemyCombatState::Attacking: Attack(); break;
		case EEnemyCombatState::Blocking: break;
		default: break;
	}
}

void AEnemyAIController::Strafe()
{
	if (!Enemy || !TargetPlayer) return;

	// Decide correct strafe direction. Raycast behind the player in two directions - forwards direction and minus forward direction.
	// If there is a wall or smth within one of the directions decide to use the other one. Constantly raycast if it finds a wall swap directions.
	// If in both directions there is a wall return and decide to attack or block.

	FVector ToEnemy = Enemy->GetActorLocation() - TargetPlayer->GetActorLocation();

	FVector ForwardDirection = ToEnemy.GetSafeNormal();
	FVector StrafeDirection = FVector::CrossProduct(ForwardDirection, FVector::UpVector).GetSafeNormal();

	float Distance = ToEnemy.Size();

	if (Distance < StrafeRange)
	{
		StrafeDirection += ToEnemy.GetSafeNormal();
	}
	else
	{
		StrafeDirection -= ToEnemy.GetSafeNormal();
	}

	Enemy->AddMovementInput(StrafeDirection, StrafeMoveSpeed * GetWorld()->DeltaTimeSeconds);
}

void AEnemyAIController::Attack()
{

}

void AEnemyAIController::Block()
{
}

void AEnemyAIController::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (!Enemy) return;
	if (Stimulus.WasSuccessfullySensed())
	{
		TargetPlayer = Cast<APawn>(Actor);
		Enemy->CurrentState = EEnemyState::Alert;
		StopMovement();
		CurrentTarget = TargetPlayer;

		// after 1 second check if player is still visible
		GetWorld()->GetTimerManager().SetTimer(
			AlertTimerHandle,
			this,
			&AEnemyAIController::OnAlertTimerExpired,
			1.0f,
			false
		);
	}
	else
	{
		TargetPlayer = nullptr;
		Enemy->CurrentState = EEnemyState::Patrol;
	}
}
void AEnemyAIController::OnAlertTimerExpired()
{
	if (!Enemy || !TargetPlayer) return;
	TArray<AActor*> SensedActors;
	PerceptionComponent->GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), SensedActors);
	// check if player is still in sight
	if (SensedActors.Contains(TargetPlayer))
	{
		Enemy->CurrentState = EEnemyState::Chase;
	}
	else
	{
		TargetPlayer = nullptr;
		Enemy->CurrentState = EEnemyState::Patrol;
	}
}