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

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		UBaseAttributeSet::GetHealthAttribute())
		.AddUObject(this, &AMapCharacter::OnHealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetStaminaAttribute()).AddUObject(this, &AMapCharacter::OnStaminaChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetStaggerAttribute()).AddUObject(this, &AMapCharacter::OnStaggerChanged);
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
				Inv->LoadInventory(Data.InventorySlots);
			}
		}

		if (Data.EquippedWeaponDef)
			ItemDefinition = Data.EquippedWeaponDef;

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

	UE_LOG(LogTemp, Warning, TEXT("PlaceOnNode: CurrentNodeIndex=%d, StartNode=%s"),
		GI->CurrentNodeIndex,
		Map->StartNode ? *Map->StartNode->GetName() : TEXT("NULL"));

	if (GI->CurrentNodeIndex >= 0)
	{
		// ... finds by index
		UE_LOG(LogTemp, Warning, TEXT("  Using SAVED index path"));
	}
	else
	{
		CurrentNode = Map->StartNode;
		UE_LOG(LogTemp, Warning, TEXT("  Using START node path"));
	}

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

bool AMapCharacter::SaveData()
{
	if (!GI)
		return false;

	FPlayerProgressionData SaveData = GI->GetProgression();
	SaveData.InventorySlots = InventoryComponent->Slots;
	SaveData.Perks = Perks;

	// Gather GAS attributes
	if (AbilitySystemComponent)
	{
		TArray<FGameplayAttribute> Attributes;
		AbilitySystemComponent->GetAllAttributes(Attributes);
		for (const FGameplayAttribute& Attr : Attributes)
		{
			const FName AttrName = Attr.GetUProperty()->GetFName();
			SaveData.Attributes.Add(AttrName, AbilitySystemComponent->GetNumericAttribute(Attr));
		}
	}

	// Actually store it on the game instance
	GI->StoreProgression(SaveData);

	return true;
}

// Called to bind functionality to input
void AMapCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMapCharacter::TravelToNode(AMapNode* TargetNode)
{
	if (!TargetNode) return;

	// If the clicked node is a visualization actor, redirect to its graph node
	if (TargetNode->GraphNode)
		TargetNode = TargetNode->GraphNode;

	if (bIsMoving) return;

	if (CurrentNode && !CurrentNode->NextNodes.Contains(TargetNode))
		return;

	
	bIsMoving = true;
	TravelAlpha = 0.f;
	TravelStart = GetActorLocation();
	TravelEnd = TargetNode->GetActorLocation();
	PendingNode = TargetNode;
	GI->CurrentNodeIndex = TargetNode->PointIndex;
}

void AMapCharacter::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	float Delta = FMath::Abs(Data.NewValue - Data.OldValue);
	if (Delta > 0.5f)
		OnHealthChangedEvent.Broadcast(Data.NewValue / AbilitySystemComponent->GetNumericAttribute(
			UBaseAttributeSet::GetMaxHealthAttribute()));
}

void AMapCharacter::OnStaminaChanged(const FOnAttributeChangeData& Data)
{
	float Delta = FMath::Abs(Data.NewValue - Data.OldValue);
	if (Delta > 0.5f)
		OnStaminaChangedEvent.Broadcast(Data.NewValue / AbilitySystemComponent->GetNumericAttribute(
			UBaseAttributeSet::GetMaxStaminaAttribute()));
}

void AMapCharacter::OnStaggerChanged(const FOnAttributeChangeData& Data)
{
	OnStaggerChangedEvent.Broadcast(Data.NewValue / AbilitySystemComponent->GetNumericAttribute(
		UBaseAttributeSet::GetMaxStaggerAttribute()));
}

void AMapCharacter::ApplyPerk(UPerkData* Perk)
{
	if (!Perk || !Perk->Effect) return;

	FGameplayEffectContextHandle Context = AbilitySystemComponent->MakeEffectContext();
	FGameplayEffectSpecHandle Spec = AbilitySystemComponent->MakeOutgoingSpec(Perk->Effect, 1.f, Context);
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*Spec.Data.Get());

	for (int i = 0; i < Perks.Num() - 1; i++)
	{
		FPerkSlot& Slot = Perks[i];

		if (!Slot.bIsOccupied)
		{
			Slot.PerkData = Perk;
			Slot.bIsOccupied = true;
			Slot.SlotIndex = i;

			OnPerkApplied.Broadcast(Slot);
			break;
		}
	}
}



