#include "PlayerCharacter.h"
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
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AISense_Sight.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameplayAbilitySystem/BasicAttackAbility.h"

void APlayerCharacter::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	Super::OnHealthChanged(Data);

	UE_LOG(LogTemp, Warning, TEXT("Health went from %f to %f"), Data.OldValue, Data.NewValue);

	if (Data.NewValue < Data.OldValue)
	{
		ShowHitVignette();
		// Get attacker from effect context
		if (AbilitySystemComponent)
		{
			const FGameplayEffectModCallbackData* ModData = Data.GEModData;
			if (ModData)
			{
				AActor* Attacker = ModData->EffectSpec.GetContext().GetInstigator();
				PlayHitReaction(Attacker);
			}
		}
	}
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

	// 3rd person — only yaw rotates the character, pitch stays on camera only
	bUseControllerRotationYaw = false; // let the spring arm handle this
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; // character faces movement direction

	// Spring arm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = true; // camera rotates with controller

	// Camera attaches to spring arm, not the mesh
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false; // spring arm handles it

	PostProcessComponent = CreateDefaultSubobject<UPostProcessComponent>(TEXT("PostProcess"));
	PostProcessComponent->SetupAttachment(RootComponent);

	HotbarSlots.SetNum(4);
}

void APlayerCharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	SpringArm->TargetArmLength = SpringArmDistance;
	SpringArm->SetRelativeLocation(SpringArmOffset);
	SpringArm->SetRelativeRotation(SpringArmRotation);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	PC = GetWorld()->GetFirstPlayerController();
	AttachWeapon();

	if (HitVignetteMaterial)
	{
		HitVignetteMID = UMaterialInstanceDynamic::Create(HitVignetteMaterial, this);
		PostProcessComponent->AddOrUpdateBlendable(HitVignetteMID);
	}

	GetWorldTimerManager().SetTimer(
		FootstepTimerHandle,
		this,
		&APlayerCharacter::TryPlayFootsteps,
		FootstepInterval,
		false // not repeating
	);
}


void APlayerCharacter::ToggleCombat()
{
}

void APlayerCharacter::ApplyPerk(UPerkData* Perk)
{
	if (!Perk || !Perk->Effect) return;

	FGameplayEffectContextHandle Context = AbilitySystemComponent->MakeEffectContext();
	FGameplayEffectSpecHandle Spec = AbilitySystemComponent->MakeOutgoingSpec(Perk->Effect, 1.0f, Context);
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*Spec.Data.Get());

	ActivePerks.Add(Perk);
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
		GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "Weapon_R");

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(Weapon->ItemDefinition->WeaponData.EnterCombat);
	CombatType = Weapon->ItemDefinition->WeaponData.CombatType;

	OnWeaponEquipped.Broadcast(CombatType);
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

		Input->BindAction(AttackAction, ETriggerEvent::Started, this, &APlayerCharacter::Attack);

		Input->BindAction(BlockAction, ETriggerEvent::Started, this, &APlayerCharacter::StartBlock);
		Input->BindAction(BlockAction, ETriggerEvent::Completed, this, &APlayerCharacter::StopBlock);

		Input->BindAction(DashAction, ETriggerEvent::Started, this, &APlayerCharacter::Dash);

		Input->BindAction(LockOnAction, ETriggerEvent::Started, this, &APlayerCharacter::ToggleLockOn);

		Input->BindAction(ToggleCombatAction, ETriggerEvent::Started, this, &APlayerCharacter::ToggleCombat);

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

void APlayerCharacter::EquipWeapon(TSubclassOf<AMeleeWeapon> NewWeaponClass)
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
	if (CombatType == ECombatType::Unarmed) return;

	if (AbilitySystemComponent->HasMatchingGameplayTag(
		FGameplayTag::RequestGameplayTag("State.Attacking")))
	{
		// Just queue, don't activate
		for (FGameplayAbilitySpec& Spec : AbilitySystemComponent->GetActivatableAbilities())
		{
			for (UGameplayAbility* Instance : Spec.GetAbilityInstances())
			{
				UBasicAttackAbility* Attack = Cast<UBasicAttackAbility>(Instance);
				if (Attack && Attack->IsActive())
				{
					Attack->QueueNextAttack();
					return; // return here, don't fall through to TryActivate
				}
			}
		}
		return; // even if we didn't find the instance, don't re-activate
	}

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
			if (IsValid(Hit.GetActor()) && Hit.GetActor() != this && Hit.GetActor() != Weapon)
			{
				if (AInteractable* Interactable = Cast<AInteractable>(Hit.GetActor()))
				{
					Interactable->OnInteract(this);
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

		PC->bShowMouseCursor = false;

		FInputModeGameOnly InputMode;
		PC->SetInputMode(InputMode);

		PC->SetIgnoreLookInput(false);
		PC->SetIgnoreMoveInput(false);
	}
	else
	{
		InventoryWidget->SetVisibility(ESlateVisibility::Visible);

		PC->bShowMouseCursor = true;

		FInputModeGameAndUI InputMode;
		InputMode.SetWidgetToFocus(InventoryWidget->TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

		PC->SetInputMode(InputMode);
		PC->SetIgnoreLookInput(true);
		InventoryWidget->SetKeyboardFocus();
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

void APlayerCharacter::TryPlayFootsteps()
{
	float Speed = GetVelocity().Size();

	if (Speed < 10.f || GetCharacterMovement()->IsFalling())
	{
		// Reschedule even when not playing, so it picks up again when moving
		GetWorldTimerManager().SetTimer(FootstepTimerHandle, this, &APlayerCharacter::TryPlayFootsteps, FootstepInterval, false);
		return;
	}

	float Interval = FMath::GetMappedRangeValueClamped(
		FVector2D(0.f, 600.f),
		FVector2D(0.5f, 0.25f),
		Speed
	);

	GetWorldTimerManager().SetTimer(FootstepTimerHandle, this, &APlayerCharacter::TryPlayFootsteps, Interval, false);
	PlayFootstepSounds();
}

void APlayerCharacter::PlayHitReaction(AActor* Attacker)
{
	if (!Attacker || !Weapon) return;

	FVector ToAttacker = Attacker->GetActorLocation() - GetActorLocation();
	ToAttacker.Z = 0;
	ToAttacker.Normalize();

	float DotForward = FVector::DotProduct(GetActorForwardVector(), ToAttacker);
	float DotRight = FVector::DotProduct(GetActorRightVector(), ToAttacker);

	UE_LOG(LogTemp, Warning, TEXT("DotForward: %.2f | DotRight: %.2f"), DotForward, DotRight);

	UAnimMontage* HitMontage = nullptr;
	FWeaponData WeaponData = Weapon->ItemDefinition->WeaponData;

	if (DotForward > 0.5f)
	{
		HitMontage = WeaponData.HitF;
		UE_LOG(LogTemp, Warning, TEXT("Hit direction: FRONT"));
	}
	else if (DotForward < -0.5f)
	{
		HitMontage = WeaponData.HitB;
		UE_LOG(LogTemp, Warning, TEXT("Hit direction: BACK"));
	}
	else if (DotRight < 0.f)
	{
		HitMontage = WeaponData.HitL;
		UE_LOG(LogTemp, Warning, TEXT("Hit direction: RIGHT"));
	}
	else
	{
		HitMontage = WeaponData.HitR;
		UE_LOG(LogTemp, Warning, TEXT("Hit direction: LEFT"));
	}

	if (HitMontage)
	{
		UE_LOG(LogTemp, Warning, TEXT("Playing montage: %s"), *HitMontage->GetName());
		if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
			AnimInstance->Montage_Play(HitMontage);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("HitMontage is NULL for this direction"));
	}
}

void APlayerCharacter::BindItemToSlot(UItemDefinition* ItemDefinition, int32 HotbarSlotIndex)
{
	if (HotbarSlotIndex < 1 || HotbarSlotIndex > 4) return;

	for (int i = 0; i < HotbarSlots.Num(); ++i)
	{
		if (i == HotbarSlotIndex) continue; 

		if (HotbarSlots[i] == ItemDefinition)
			HotbarSlots[i] = nullptr;
	}
	HotbarSlots[HotbarSlotIndex - 1] = ItemDefinition;
}

void APlayerCharacter::EquipRuneToWeapon(UItemDefinition* RuneDef)
{
	if (!Weapon || !RuneDef) return;

	URuneBase* Rune = RuneDef->GetRune();
	if (!Rune)
	{
		UE_LOG(LogTemp, Warning, TEXT("No rune found on item definition"));
		return;
	}

	Weapon->EquipRune(Rune);
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
	float Offset;
	FVector ModifiedOffset = FVector(0, Offset, 0);
	if (!AbilitySystemComponent->HasMatchingGameplayTag(LockOnTag) || !LockOnTarget)
		return;

	// Check if target went out of range
	if (FVector::Dist(GetActorLocation(), LockOnTarget->GetActorLocation()) > LockOnDetectionRadius)
	{
		AbilitySystemComponent->RemoveLooseGameplayTag(LockOnTag);
		LockOnTarget = nullptr;	
		return;
	}

	FVector Velocity = GetVelocity().GetSafeNormal();
	float RightDot = FVector::DotProduct(Velocity, GetActorRightVector());

	FVector TargetOffset = SpringArmOffset; // default center

	if (RightDot > 0.1f)
	{
		// Moving right — shift camera left so enemy stays visible
		TargetOffset = SpringArmOffset + FVector(0.f, -60.f, 0.f);
	}
	else if (RightDot < -0.1f)
	{
		// Moving left — shift camera right
		TargetOffset = SpringArmOffset + FVector(0.f, 60.f, 0.f);
	}

	// Smoothly interpolate to target offset
	SpringArm->SetRelativeLocation(
		FMath::VInterpTo(SpringArm->GetRelativeLocation(), TargetOffset, DeltaTime, 5.f)
	);

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

	FRotator CurrentRotation = GetActorRotation();
	FRotator NewCharacterRotation = FMath::RInterpTo(
		CurrentRotation,
		TargetRotation,
		DeltaTime,
		10.f // rotation speed, tweak this
	);
	NewCharacterRotation.Pitch = 0.f;
	NewCharacterRotation.Roll = 0.f;

	SetActorRotation(NewCharacterRotation);
	GetController()->SetControlRotation(NewRotation);
	
}

void APlayerCharacter::UseHotbarSlot(int32 Index)
{
	if (!HotbarSlots.IsValidIndex(Index) || !HotbarSlots[Index]) return;
	if (HotbarSlots[Index]->ItemType != EItemType::Weapon) return;

	TSubclassOf<AMeleeWeapon> NewWeaponClass = HotbarSlots[Index]->GetWeaponClass();
	if (!NewWeaponClass) return;

	if (Weapon && Weapon->ItemDefinition == HotbarSlots[Index])
	{
		// Store reference BEFORE nulling out Weapon
		AMeleeWeapon* WeaponToDestroy = Weapon;

		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		float MontageDuration = 1.f; // default fallback
		if (AnimInstance && WeaponToDestroy->ItemDefinition->WeaponData.ExitCombat)
			MontageDuration = AnimInstance->Montage_Play(WeaponToDestroy->ItemDefinition->WeaponData.ExitCombat) / 2;

		// Now safe to null out
		Weapon = nullptr;
		WeaponClass = nullptr;
		CombatType = ECombatType::Unarmed;
		OnWeaponEquipped.Broadcast(CombatType);

		FTimerHandle UnequipTimer;
		GetWorldTimerManager().SetTimer(UnequipTimer, [WeaponToDestroy]()
			{
				if (IsValid(WeaponToDestroy))
					WeaponToDestroy->Destroy();
			}, MontageDuration, false);

		return;
	}

	EquipWeapon(NewWeaponClass);
}

