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
		bStrafeDirectionSet = false;
	}

	switch (Enemy->CombatState)
	{
		case EEnemyCombatState::None: break;
		case EEnemyCombatState::Strafe: Strafe(); break;
		case EEnemyCombatState::Attacking: Attack(); break;
		case EEnemyCombatState::Blocking: 
			bStrafeDirectionSet = false;
			break;
		default: break;
	}
}

void AEnemyAIController::Strafe()
{
	if (!Enemy || !TargetPlayer) return;

	FVector ToEnemy = Enemy->GetActorLocation() - TargetPlayer->GetActorLocation();

	if (!bStrafeDirectionSet)
	{
		CurrentStrafeDirection = GetStrafeDirection(ToEnemy);
		CurrentStrafeDirection.Z = 0.f; // flatten to horizontal plane
		CurrentStrafeDirection = CurrentStrafeDirection.GetSafeNormal();
		UE_LOG(LogTemp, Warning, TEXT("Strafe direction set to: %s"), *CurrentStrafeDirection.ToString());
		bStrafeDirectionSet = true;
	}

	StrafeDirectionTimer += GetWorld()->DeltaTimeSeconds;
	if (StrafeDirectionTimer >= StrafeDirectionCheckInterval)
	{
		StrafeDirectionTimer = 0.0f;
		CurrentStrafeDirection = GetStrafeDirection(ToEnemy); // recheck for walls
	}

	if (CurrentStrafeDirection.Equals(FVector::Zero()))
	{
		Enemy->CombatState = EEnemyCombatState::None;
		return;
	}

	float Distance = ToEnemy.Size();
	FVector MoveDirection = CurrentStrafeDirection;

	if (Distance < StrafeRange)
		MoveDirection += ToEnemy.GetSafeNormal();
	else if (Distance > StrafeRange)
		MoveDirection -= ToEnemy.GetSafeNormal();

	
	UE_LOG(LogTemp, Warning, TEXT("Move direction: %s, Distance: %f, AttackRange: %f"),
		*MoveDirection.ToString(), Distance, AttackRange);

	Enemy->AddMovementInput(MoveDirection.GetSafeNormal(), StrafeMoveSpeed * GetWorld()->DeltaTimeSeconds);
}


FVector AEnemyAIController::GetStrafeDirection(const FVector &ToEnemy) const
{
	FVector ForwardDirection = ToEnemy.GetSafeNormal();
	FVector LeftDirection = FVector::CrossProduct(ForwardDirection, FVector::UpVector).GetSafeNormal();
	FVector RightDirection = -LeftDirection;

	FHitResult HitResultLeft;
	FHitResult HitResultRight;

	FVector Start = Enemy->GetActorLocation();
	FVector EndLeft = Start + LeftDirection * 100;
	FVector EndRight = Start + RightDirection * 100;

	bool bHitLeft = GetWorld()->LineTraceSingleByChannel(
		HitResultLeft,
		Start,
		EndLeft,
		ECC_Visibility
	);

	bool bHitRight = GetWorld()->LineTraceSingleByChannel(
		HitResultRight,
		Start,
		EndRight,
		ECC_Visibility
	);


	int32 Random = FMath::RandRange(0, 1);

	if (bHitLeft && !bHitRight)
	{
		return RightDirection;
	}
	else if (!bHitLeft && bHitRight)
	{
		return LeftDirection;
	}
	else if (bHitLeft && bHitRight)
	{
		return FVector::Zero();
	}

	if (Random == 0) return LeftDirection;
	else if (Random == 1) return RightDirection;

	return FVector::Zero();
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