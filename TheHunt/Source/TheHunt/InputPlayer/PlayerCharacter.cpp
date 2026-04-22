#include "PlayerCharacter.h"
#include "PlayerCharacter.h"
#include <string>
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Inventory/InventorySubsystem.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "AbilitySystemComponent.h"
#include "Enemy/EnemyCharacter.h"
#include "Engine/OverlapResult.h"
#include "Items/Weapon/MeleeWeapon.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AISense_Sight.h"
#include "Components/CapsuleComponent.h"

void APlayerCharacter::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	Super::OnHealthChanged(Data);

	ShowHitVignette();
}

void APlayerCharacter::ShowHitVignette()
{
	if (!HitVignetteMID) return;

	// Set intensity to full
	HitVignetteMID->SetScalarParameterValue(FName("HitIntensity"), 1.0f);

	// Fade it out over time
	GetWorldTimerManager().SetTimer(HitVignetteTimer, [this]()
		{
			float CurrentIntensity;
			HitVignetteMID->GetScalarParameterValue(FName("HitIntensity"), CurrentIntensity);

			if (CurrentIntensity > 0.f)
			{
				HitVignetteMID->SetScalarParameterValue(
					FName("HitIntensity"), CurrentIntensity - 0.05f);
			}
			else
			{
				GetWorldTimerManager().ClearTimer(HitVignetteTimer);
			}
		}, 0.016f, true); // runs every frame roughly
}

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	StimuliSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("StimuliSource"));
	StimuliSource->RegisterForSense(TSubclassOf<UAISense_Sight>());
	StimuliSource->RegisterForSense(TSubclassOf<UAISense_Hearing>());

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(RootComponent);
	Camera->bUsePawnControlRotation = true;

	PostProcessComponent = CreateDefaultSubobject<UPostProcessComponent>(TEXT("PostProcess"));
	PostProcessComponent->SetupAttachment(RootComponent);

	HotbarSlots.SetNum(4);	
}


// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// ... rest of your BeginPlay code
	if (InventoryWidgetClass)
	{
		InventoryWidget = CreateWidget<UInventoryWidget>(GetWorld(), InventoryWidgetClass);
		InventoryWidget->InventoryComponent = FindComponentByClass<UInventoryComponent>();
		InventoryWidget->SetupUI();
		InventoryWidget->AddToViewport();
		InventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	PC = GetWorld()->GetFirstPlayerController();
	AttachWeapon();

	if (HitVignetteMaterial)
	{
		HitVignetteMID = UMaterialInstanceDynamic::Create(HitVignetteMaterial, this);
		PostProcessComponent->AddOrUpdateBlendable(HitVignetteMID);
	}
}

void APlayerCharacter::AttachWeapon()
{
	if (Weapon) return;
	if (!WeaponClass) return;

	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	Weapon = GetWorld()->SpawnActor<AMeleeWeapon>(WeaponClass, FVector::ZeroVector, FRotator::ZeroRotator, Params);
	if (!Weapon) return;

	Weapon->AttachToComponent(
	RootComponent,FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	if (USceneComponent* Root = Weapon->GetRootComponent())
	{
		Root->SetRelativeLocation(Weapon->AttachOffset.GetLocation());
		Root->SetRelativeRotation(Weapon->AttachOffset.GetRotation());
		// Scale is preserved from the Blueprint CDO — don't override it
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateLockOn(DeltaTime);

	if (AbilitySystemComponent->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag("State.Poisoned")))
	{
		UE_LOG(LogTemp,Warning,TEXT("kurrec"))
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Add input mapping context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>
			(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMapping, 0);
		}
	}

	if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Input->BindAction(TestAction, ETriggerEvent::Completed, this, &APlayerCharacter::TestInput);
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		Input->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Jump);
		Input->BindAction(InteractAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Interact);
		Input->BindAction(InventoryAction, ETriggerEvent::Started, this, &APlayerCharacter::ToggleInventory);
		Input->BindAction(AttackAction, ETriggerEvent::Started, this, &APlayerCharacter::Attack);

		Input->BindAction(BlockAction, ETriggerEvent::Started, this, &APlayerCharacter::StartBlock);
		Input->BindAction(BlockAction, ETriggerEvent::Completed, this, &APlayerCharacter::StopBlock);

		Input->BindAction(DashAction, ETriggerEvent::Started, this, &APlayerCharacter::Dash);

		Input->BindAction(LockOnAction, ETriggerEvent::Started, this, &APlayerCharacter::ToggleLockOn);

		TArray<FKey> HotbarKeys = { EKeys::One, EKeys::Two, EKeys::Three, EKeys::Four };
		for (int32 i = 0; i < HotbarKeys.Num(); i++)
		{
			FInputKeyBinding Binding(HotbarKeys[i], IE_Pressed);
			Binding.KeyDelegate.GetDelegateForManualSet().BindLambda([this, i]()
				{
					UseHotbarSlot(i);
				});
			Input->KeyBindings.Add(Binding);
		}
	}
}

void APlayerCharacter::UseWeapon(TSubclassOf<AMeleeWeapon> NewWeaponClass)
{
	if (Weapon)
	{
		Weapon->Destroy();
		Weapon = nullptr;
	}

	WeaponClass = NewWeaponClass;
	AttachWeapon();
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D InputVector = Value.Get<FVector2D>();

	if (IsValid(Controller))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(ForwardDirection, InputVector.Y);
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(RightDirection, InputVector.X);
	}
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D InputVector = Value.Get<FVector2D>();

	if (IsValid(Controller))
	{
		AddControllerYawInput(InputVector.X);
		AddControllerPitchInput(InputVector.Y);
	}
}

void APlayerCharacter::Jump()
{
	ACharacter::Jump();
}

void APlayerCharacter::Attack()
{
	if (AbilitySystemComponent->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag("State.Attacking")))
		return; // already attacking

	FGameplayTagContainer TagContainer;
	TagContainer.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Attack.Slash")));
	AbilitySystemComponent->TryActivateAbilitiesByTag(TagContainer);
}

void APlayerCharacter::StartBlock()
{
	FGameplayTagContainer TagContainer;
	TagContainer.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Block")));
	AbilitySystemComponent->TryActivateAbilitiesByTag(TagContainer);

	if (LockOnTarget)
	{
		AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(LockOnTarget);
		if (Enemy && Enemy->GetAbilitySystemComponent()->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag("State.Parryable")))
		{
			Enemy->GetAbilitySystemComponent()->AddLooseGameplayTag(
				FGameplayTag::RequestGameplayTag("State.Staggered"));
		}
	}
}

void APlayerCharacter::StopBlock()
{
	UE_LOG(LogTemp, Warning, TEXT("StopBlock called"));
	if (!AbilitySystemComponent) return;

	FGameplayTagContainer TagContainer;
	TagContainer.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Block")));
	AbilitySystemComponent->CancelAbilities(&TagContainer);
}

void APlayerCharacter::Interact()
{
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	//const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	FCollisionShape Sphere = FCollisionShape::MakeSphere(InteractionSphereRadius);

	TArray<FHitResult> HitResults;
	GetWorld()->SweepMultiByChannel(
		HitResults,
		GetActorLocation(),
		GetActorLocation() + ForwardDirection * InteractionDistance,
		FQuat::Identity,
		ECC_GameTraceChannel1,  // your custom trace channel
		Sphere
	);

	DrawDebugLine(
		GetWorld(),
		GetActorLocation(),
		GetActorLocation() + ForwardDirection * InteractionDistance,
		HitResults.Num() > 0 ? FColor::Green : FColor::Red,  // green if hit, red if not
		false,  // persistent
		1.0f,   // duration in seconds
		0,
		2.0f    // thickness
	);

	if (HitResults.Num() > 0)
	{
		for (const FHitResult& Hit : HitResults)
		{
			if (IsValid(Hit.GetActor()) && Hit.GetActor() != this)
			{
				if (AMeleeWeapon* Pickup = Cast<AMeleeWeapon>(Hit.GetActor()))
				{
					if (UItemDefinition* ItemDef = Pickup->ItemDefinition)
					{
						GetWorld()->GetGameInstance()->GetSubsystem<UInventorySubsystem>()->AddItemToActor(this, ItemDef);
						Pickup->Destroy();
					}
				}
			}
		}
	}
}

void APlayerCharacter::ToggleInventory()
{
	if (!InventoryWidget) return;

	if (InventoryWidget->IsVisible())
	{
		InventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
		PC->SetShowMouseCursor(false);
		PC->SetInputMode(FInputModeGameOnly());
	}
	else
	{
		InventoryWidget->SetVisibility(ESlateVisibility::Visible);
		PC->SetShowMouseCursor(true);
		PC->SetInputMode(FInputModeGameAndUI());
	}
}

void APlayerCharacter::Dash()
{
	FGameplayTag LockOnTag = FGameplayTag::RequestGameplayTag(FName("State.LockedOn"));
	FGameplayTagContainer TagContainer;

	if (AbilitySystemComponent->HasMatchingGameplayTag(LockOnTag))
		TagContainer.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Movement.LockOn.Dash")));
	else
		TagContainer.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Movement.Normal.Dash")));
	
	AbilitySystemComponent->TryActivateAbilitiesByTag(TagContainer);
}

void APlayerCharacter::BindItemToSlot(UItemDefinition* ItemDefinition, int32 HotbarSlotIndex)
{
	if (HotbarSlotIndex < 1 || HotbarSlotIndex > 4) return;
	// if another hotbar contains that item remove it from the other one and 
	for (int i = 0; i < HotbarSlots.Num(); ++i)
	{
		// skip the selected hotbar slot as we are going to overwrite what it has anyway so there is no need to remove what it contains
		if (i == HotbarSlotIndex) continue; 

		if (HotbarSlots[i] == ItemDefinition)
			HotbarSlots[i] = nullptr;
		
	}
	HotbarSlots[HotbarSlotIndex - 1] = ItemDefinition;
}

void APlayerCharacter::ToggleLockOn()
{

	FGameplayTag LockOnTag = FGameplayTag::RequestGameplayTag(FName("State.LockedOn"));

	if (AbilitySystemComponent->HasMatchingGameplayTag(LockOnTag))
	{
		AbilitySystemComponent->RemoveLooseGameplayTag(LockOnTag);
		LockOnTarget = nullptr;
	}
	else
	{
		AbilitySystemComponent->AddLooseGameplayTag(LockOnTag);
		LockOnTarget = FindBestTarget(Camera->GetForwardVector());
	}
}

TArray<TObjectPtr<AActor>> APlayerCharacter::GetPossibleLockOnTargetsWithinRange()
{
	TArray<TObjectPtr<AActor>> FinalTargets;
	TArray<FOverlapResult> Overlaps;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(LockOnDetectionRadius);
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	GetWorld()->OverlapMultiByChannel(Overlaps, this->GetActorLocation(), FQuat::Identity, ECC_Pawn, Sphere, Params);

	for (FOverlapResult& Overlap : Overlaps)
	{
		AEnemyCharacter* Target = Cast<AEnemyCharacter>(Overlap.GetActor());
		if (!Target) continue;

		FHitResult Hit;
		FCollisionQueryParams LineParams;
		LineParams.AddIgnoredActor(this);
		LineParams.AddIgnoredActor(Target);

		bool bBlocked = GetWorld()->LineTraceSingleByChannel(Hit, this->GetActorLocation(), Target->GetActorLocation(), ECC_Visibility, LineParams);
		if (!bBlocked) FinalTargets.Add(Target);
	}

	return FinalTargets;
}

TObjectPtr<AActor> APlayerCharacter::FindBestTarget(FVector Direction)
{
	TArray<TObjectPtr<AActor>> Targets = GetPossibleLockOnTargetsWithinRange();
	TObjectPtr<AActor> BestTarget = nullptr;
	float BestScore = FLT_MAX;
	FVector NormalizedDirection = Direction.GetSafeNormal();

	if (!LockOnTarget)
	{
		for (TObjectPtr<AActor> Candidate : Targets)
		{
			FVector CameraToTarget = (Candidate->GetActorLocation() - Camera->GetComponentLocation());
			FVector NormalizedCameraToTarget = CameraToTarget.GetSafeNormal();

			// Angular distance 0-1, regardless of how far the enemy is
			float AngularDistance = FVector::CrossProduct(NormalizedDirection, NormalizedCameraToTarget).Size();

			// Only consider enemies within a cone in front of camera
			float Dot = FVector::DotProduct(NormalizedDirection, NormalizedCameraToTarget);
			if (Dot < 0.f) continue; // behind camera

			// Combine angular distance with actual distance, prioritize centered targets
			float ActualDistance = CameraToTarget.Size();
			float Score = AngularDistance * 1000.f + ActualDistance;

			if (Score < BestScore)
			{
				BestScore = Score;
				BestTarget = Candidate;
			}
		}
	}
	else
	{
		FVector CameraLocation = Camera->GetComponentLocation();

		for (TObjectPtr<AActor> Candidate : Targets)
		{
			if (Candidate == LockOnTarget) continue;

			FVector CameraToTarget = (Candidate->GetActorLocation() - CameraLocation);
			FVector NormalizedCameraToTarget = CameraToTarget.GetSafeNormal();

			float Dot = FVector::DotProduct(NormalizedDirection, NormalizedCameraToTarget);
			if (Dot < 0.3f) continue; // require target to be somewhat in stick direction

			float Distance = CameraToTarget.Size();
			float Score = Distance * (1.f - Dot); // prioritize direction first, then distance

			if (Score < BestScore)
			{
				BestScore = Score;
				BestTarget = Candidate;
			}
		}
	}

	return BestTarget;
}

void APlayerCharacter::UpdateLockOn(float DeltaTime)
{
	FGameplayTag LockOnTag = FGameplayTag::RequestGameplayTag(FName("State.LockedOn"));
	if (!AbilitySystemComponent->HasMatchingGameplayTag(LockOnTag) || !LockOnTarget) return;

	// Check if target went out of range
	if (FVector::Dist(GetActorLocation(), LockOnTarget->GetActorLocation()) > LockOnDetectionRadius)
	{
		AbilitySystemComponent->RemoveLooseGameplayTag(LockOnTag);
		LockOnTarget = nullptr;
		return;
	}

	// Track cooldown so it doesn't spam switch
	TargetSwitchCooldownTimer -= DeltaTime;

	// Get mouse delta this frame
	float MouseX, MouseY;
	PC->GetInputMouseDelta(MouseX, MouseY);
	FVector2D MouseDelta(MouseX, MouseY);

	if (MouseDelta.Size() > TargetSwitchThreshold && TargetSwitchCooldownTimer <= 0.f)
	{
		// Convert 2D mouse direction to 3D world direction
		FVector SwitchDirection = (Camera->GetRightVector() * MouseDelta.X) +
			(Camera->GetUpVector() * -MouseDelta.Y);

		TObjectPtr<AActor> NextTarget = FindBestTarget(SwitchDirection);
		if (NextTarget)
		{
			LockOnTarget = NextTarget;
			TargetSwitchCooldownTimer = TargetSwitchCooldown;
		}
	}

	// Rotate camera toward current target
	FVector DirectionToTarget = LockOnTarget->GetActorLocation() - GetActorLocation();
	FRotator TargetRotation = DirectionToTarget.Rotation();
	FRotator NewRotation = FMath::RInterpTo(GetControlRotation(), TargetRotation, DeltaTime, 20.f);
	NewRotation.Roll = 0;
	NewRotation.Pitch += LockOnOffsetZ;
	GetController()->SetControlRotation(NewRotation);
}

void APlayerCharacter::UseHotbarSlot(int32 Index)
{
	if (!HotbarSlots[Index]) return;

	WeaponClass = HotbarSlots[Index]->WeaponData.WeaponClass;
	AttachWeapon();
}

