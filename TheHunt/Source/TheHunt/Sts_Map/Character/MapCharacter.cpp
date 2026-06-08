// Fill out your copyright notice in the Description page of Project Settings.


#include "MapCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sts_Map/MapManager.h"

// Sets default values
AMapCharacter::AMapCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMapCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->GravityScale = 0.f;
	GetCharacterMovement()->SetMovementMode(MOVE_None);

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMapManager::StaticClass(), FoundActors);

	PC = Cast<APlayerController>(GetController());

	if (FoundActors.Num() > 0)
	{
		Map = Cast<AMapManager>(FoundActors[0]);

	}

	if (Map)
	{
		CurrentNode = Map->StartNode;

		SetActorLocation(CurrentNode->GetActorLocation());
		UE_LOG(LogTemp, Warning, TEXT("goes into here"));
	}
}

// Called every frame
void AMapCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsMoving) return;

	TravelAlpha += DeltaTime / TravelSpeed;
	TravelAlpha = FMath::Clamp(TravelAlpha, 0.f, 1.f);

	// Smooth lerp using ease in/out
	float EasedAlpha = FMath::InterpEaseInOut(0.f, 1.f, TravelAlpha, 2.f);
	FVector NewPos = FMath::Lerp(TravelStart, TravelEnd, EasedAlpha);
	SetActorLocation(NewPos);

	if (TravelAlpha >= 1.f)
	{
		bIsMoving = false;
		CurrentNode = PendingNode;
		PendingNode = nullptr;
		CurrentNode->OnEnter(PC);
	}

}

// Called to bind functionality to input
void AMapCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMapCharacter::TravelToNode(AMapNode* TargetNode)
{
	UE_LOG(LogTemp, Warning, TEXT("TravelToNode called. TargetNode=%s, bIsMoving=%s"),
		TargetNode ? *TargetNode->GetName() : TEXT("NULL"),
		bIsMoving ? TEXT("TRUE") : TEXT("FALSE"));

	if (!TargetNode || bIsMoving)
	{
		UE_LOG(LogTemp, Warning, TEXT("  EARLY RETURN: %s"),
			!TargetNode ? TEXT("TargetNode is NULL") : TEXT("bIsMoving is TRUE"));
		return;
	}

	// Only allow travelling to connected nodes
	if (CurrentNode && !CurrentNode->NextNodes.Contains(TargetNode->GraphNode))
	{
		UE_LOG(LogTemp, Warning, TEXT("  EARLY RETURN: TargetNode not in CurrentNode->NextNodes"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("  OK, travelling to %s"), *TargetNode->GetName());

	bIsMoving = true;
	TravelAlpha = 0.f;
	TravelStart = GetActorLocation();
	TravelEnd = TargetNode->GraphNode->GetActorLocation();
	PendingNode = TargetNode;
}



