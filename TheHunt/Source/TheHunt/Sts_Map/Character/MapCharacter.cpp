// Fill out your copyright notice in the Description page of Project Settings.


#include "MapCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Inventory/InventoryComponent.h"
#include "Inventory/InventorySubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Sts_Map/MapManager.h"

// Sets default values
AMapCharacter::AMapCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	BaseAttributes = CreateDefaultSubobject<UBaseAttributeSet>(TEXT("BaseAttributesSet"));

}

UAbilitySystemComponent* AMapCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AMapCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetupMovement();

	if (!LoadSaveData())
		return;

	FindMapManager();
	PlaceOnCurrentNode();
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

void AMapCharacter::SetupMovement()
{
	GetCharacterMovement()->GravityScale = 0.f;
	GetCharacterMovement()->SetMovementMode(MOVE_None);
	GetCharacterMovement()->bOrientRotationToMovement = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	SetActorRotation(FRotator(0.f, -90.f, 0.f));
}

void AMapCharacter::FindMapManager()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMapManager::StaticClass(), FoundActors);
	PC = Cast<APlayerController>(GetController());
	if (FoundActors.Num() > 0)
		Map = Cast<AMapManager>(FoundActors[0]);
}

bool AMapCharacter::LoadSaveData()
{
	GI = Cast<UTheHuntGameInstance>(GetGameInstance());
	if (!GI)
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance is null!"));
		return false;
	}

	if (GI->bHasSaved)
	{
		const FPlayerProgressionData& Data = GI->GetProgression();

		if (UInventorySubsystem* Sub = GetGameInstance()->GetSubsystem<UInventorySubsystem>())
		{
			if (UInventoryComponent* Inv = Sub->GetInventory(this))
			{
				Inv->LoadInventory(GI->SavedProgression.InventorySlots);
			}
		}

		// --- Restore GAS attributes ---
		if (AbilitySystemComponent)
		{
			TArray<FGameplayAttribute> Attributes;
			AbilitySystemComponent->GetAllAttributes(Attributes);

			// Pass 1: set Max attributes first (so current values clamp correctly)
			for (const FGameplayAttribute& Attr : Attributes)
			{
				const FName AttrName = Attr.GetUProperty()->GetFName();
				if (AttrName.ToString().Contains(TEXT("Max")))
				{
					if (const float* Saved = Data.Attributes.Find(AttrName))
						AbilitySystemComponent->SetNumericAttributeBase(Attr, *Saved);
				}
			}

			// Pass 2: set the rest (current values)
			for (const FGameplayAttribute& Attr : Attributes)
			{
				const FName AttrName = Attr.GetUProperty()->GetFName();
				if (!AttrName.ToString().Contains(TEXT("Max")))
				{
					if (const float* Saved = Data.Attributes.Find(AttrName))
						AbilitySystemComponent->SetNumericAttributeBase(Attr, *Saved);
				}
			}
		}
	}

	return true;
}

void AMapCharacter::PlaceOnCurrentNode()
{
	if (!Map) return;

	if (GI->CurrentNodeIndex >= 0)
	{
		CurrentNode = nullptr;
		for (AMapNode* Node : Map->SpawnedNodes)
		{
			if (Node && Node->PointIndex == GI->CurrentNodeIndex)
			{
				CurrentNode = Node;
				break;
			}
		}
	}
	else
	{
		CurrentNode = Map->StartNode;
	}

	if (!CurrentNode) return;

	SetActorLocation(CurrentNode->GetActorLocation());
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
	if (CurrentNode && !CurrentNode->NextNodes.Contains(TargetNode))
	{
		UE_LOG(LogTemp, Warning, TEXT("  EARLY RETURN: TargetNode not in CurrentNode->NextNodes"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("  OK, travelling to %s"), *TargetNode->GetName());

	bIsMoving = true;
	TravelAlpha = 0.f;
	TravelStart = GetActorLocation();
	TravelEnd = TargetNode->GetActorLocation();
	PendingNode = TargetNode;
	GI->CurrentNodeIndex = TargetNode->PointIndex;
}



