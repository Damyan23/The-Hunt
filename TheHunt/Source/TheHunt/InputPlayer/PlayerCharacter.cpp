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
#include "GameplayAbilitySystem/Abilities/BasicBlockingAbility.h"

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

	Perks.SetNum(15);
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

	UTheHuntGameInstance* GI = GetGameInstance<UTheHuntGameInstance>();
	if (GI && GI->bHasSaved)
	{
		ApplyProgression(GI->GetProgression());
	}
	else
	{
		AttachWeapon();
	}


	if (PC)
	{
		PC->ConsoleCommand("AbilitySystem.DebugAttribute health");
		PC->ConsoleCommand("AbilitySystem.DebugAttribute stamina");
		PC->ConsoleCommand("AbilitySystem.DebugAttribute stagger");
		PC->ConsoleCommand("AbilitySystem.DebugAbilityTags");
	}

	if (HitVignetteMaterial)
	{
		HitVignetteMID = UMaterialInstanceDynamic::Create(HitVignetteMaterial, this);
		PostProcessComponent->AddOrUpdateBlendable(HitVignetteMID);
	}
}

FPlayerProgressionData APlayerCharacter::GatherProgression()
{
	FPlayerProgressionData Data;
	Data.HotbarSlots = HotbarSlots;
	Data.Perks = Perks;
	Data.EquippedWeaponDef = Weapon ? Weapon->ItemDefinition : nullptr;

	// Inventory from the subsystem
	if (UInventorySubsystem* Inv = GetGameInstance()->GetSubsystem<UInventorySubsystem>())
	{
		Data.InventorySlots = Inv->GetInventory(this)->Slots;
	}

	if (Weapon)
	{
		Data.EquippedWeaponDef = Weapon->ItemDefinition;
	}
		

	// Attributes
	if (UAbilitySystemComponent* ASC = GetAbilitySystemComponent())
	{
		TArray<FGameplayAttribute> Attrs;
		ASC->GetAllAttributes(Attrs);
		for (const FGameplayAttribute& A : Attrs)
			Data.Attributes.Add(FName(*A.GetName()), ASC->GetNumericAttribute(A));
	}


	return Data;
}

void APlayerCharacter::ApplyProgression(const FPlayerProgressionData& Data)
{
	// Hotbar & perks
	HotbarSlots = Data.HotbarSlots;
	Perks = Data.Perks;

	// Inventory
	if (UInventorySubsystem* Sub = GetGameInstance()->GetSubsystem<UInventorySubsystem>())
	{
		if (UInventoryComponent* Inv = Sub->GetInventory(this))
		{
			Inv->LoadInventory(Data.InventorySlots);
		}
	}

	// Equipped weapon — rebuild from the saved definition
	if (Data.EquippedWeaponDef)
	{
		TSubclassOf<AMeleeWeapon> SavedClass = Data.EquippedWeaponDef->GetWeaponClass();
		if (SavedClass)
			EquipWeapon(SavedClass);
	}

	// Attributes
	if (AbilitySystemComponent)
	{
		TArray<FGameplayAttribute> Attributes;
		AbilitySystemComponent->GetAllAttributes(Attributes);

		// Pass 1: Max attributes first (so current values clamp correctly)
		for (const FGameplayAttribute& Attr : Attributes)
		{
			const FName AttrName = Attr.GetUProperty()->GetFName();
			if (AttrName.ToString().Contains(TEXT("Max")))
				if (const float* Saved = Data.Attributes.Find(AttrName))
					AbilitySystemComponent->SetNumericAttributeBase(Attr, *Saved);
		}

		// Pass 2: current values
		for (const FGameplayAttribute& Attr : Attributes)
		{
			const FName AttrName = Attr.GetUProperty()->GetFName();
			if (!AttrName.ToString().Contains(TEXT("Max")))
				if (const float* Saved = Data.Attributes.Find(AttrName))
					AbilitySystemComponent->SetNumericAttributeBase(Attr, *Saved);
		}
	}
}

void APlayerCharacter::OnGuardBroken()
{
	Super::OnGuardBroken();
	UE_LOG(LogTemp, Warning, TEXT("it should be playing the anim?"));

	if (Weapon)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (!AnimInstance) return;

		UAnimMontage* BlockBrokenMontage = Weapon->ItemDefinition->WeaponData.BlockBroken;
		if (!BlockBrokenMontage) return;

		float Duration = AnimInstance->Montage_Play(BlockBrokenMontage);
		if (Duration > 0.f)
		{
			FOnMontageEnded EndDelegate;
			EndDelegate.BindUObject(this, &APlayerCharacter::OnBlockBrokenMontageEnded);
			AnimInstance->Montage_SetEndDelegate(EndDelegate, BlockBrokenMontage);
		}
	}
}

void APlayerCharacter::OnDeath()
{
	Super::OnDeath();

	UE_LOG(LogTemp, Warning, TEXT("OnDeath: DeathMontage=%s, AnimInstance=%s"),
		DeathMontage ? *DeathMontage->GetName() : TEXT("NULL"),
		GetMesh()->GetAnimInstance() ? TEXT("valid") : TEXT("NULL"));

	if (PC)
	{
		PC->SetIgnoreMoveInput(true);
		PC->SetIgnoreLookInput(true);
	}
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->CancelAllAbilities();
	}
	if (UCapsuleComponent* Capsule = GetCapsuleComponent())
	{
		Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	GetCharacterMovement()->DisableMovement();

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && DeathMontage)
	{
		AnimInstance->Montage_Play(DeathMontage);
	}

	// Show the death screen after 0.2 seconds regardless of montage length
	FTimerHandle DeathScreenTimer;
	GetWorldTimerManager().SetTimer(DeathScreenTimer, this,
		&APlayerCharacter::ShowDeathScreen, 0.2f, false);
}

void APlayerCharacter::OnDeathMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	ShowDeathScreen();
}

void APlayerCharacter::ShowDeathScreen()
{
	if (DeathScreenWidgetClass && PC)
	{
		DeathScreenWidget = CreateWidget<UUserWidget>(PC, DeathScreenWidgetClass);
		if (DeathScreenWidget)
		{
			DeathScreenWidget->AddToViewport();
		}
	}

	// Respawn after a delay (gives the widget animation time to play)
	FTimerHandle RespawnTimer;
	GetWorldTimerManager().SetTimer(RespawnTimer, this,
		&APlayerCharacter::Respawn, DeathScreenDuration, false);
}

void APlayerCharacter::Respawn()
{
	// Remove the death screen
	if (DeathScreenWidget)
	{
		DeathScreenWidget->RemoveFromParent();
		DeathScreenWidget = nullptr;
	}

	// Full run reset
	if (UTheHuntGameInstance* GI = GetGameInstance<UTheHuntGameInstance>())
		GI->ResetRun();

	// Go back to the map level — it will regenerate fresh and place the player on the start node
	UGameplayStatics::OpenLevel(this, FName("Lvl_Map"));
}

void APlayerCharacter::OnBlockBrokenMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (!AbilitySystemComponent || !StaggerResetEffect) return;

	AbilitySystemComponent->ApplyGameplayEffectToSelf(
		StaggerResetEffect.GetDefaultObject(), 1.f,
		AbilitySystemComponent->MakeEffectContext());
}

void APlayerCharacter::ApplyPerk(UPerkData* Perk)
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
	
	DeathMontage = Weapon->ItemDefinition->WeaponData.Death;
	Weapon->DisableAttackHitbox();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateLockOn(DeltaTime);
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

		Input->BindAction(HealAction, ETriggerEvent::Started, this, &APlayerCharacter::Heal);

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

float APlayerCharacter::UnequipWeapon()
{
	if (!Weapon) return 0;

	// Store reference BEFORE nulling out Weapon
	AMeleeWeapon* WeaponToDestroy = Weapon;

	// Play the exit-combat montage from the weapon being removed
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	float MontageDuration = 1.f; // default fallback
	if (AnimInstance && WeaponToDestroy->ItemDefinition->WeaponData.ExitCombat)
		MontageDuration = AnimInstance->Montage_Play(
			WeaponToDestroy->ItemDefinition->WeaponData.ExitCombat) / 2;

	// Clear weapon state now so the rest of the game knows we're unarmed
	Weapon = nullptr;
	WeaponClass = nullptr;
	CombatType = ECombatType::Unarmed;
	OnWeaponEquipped.Broadcast(CombatType);

	// Destroy the weapon actor after the unequip animation plays
	FTimerHandle UnequipTimer;
	GetWorldTimerManager().SetTimer(UnequipTimer, [WeaponToDestroy]()
		{
			if (IsValid(WeaponToDestroy))
				WeaponToDestroy->Destroy();
		}, MontageDuration, false);

	return MontageDuration;
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
		FGameplayTag::RequestGameplayTag("State.Healing"))) return;

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
	if (!Weapon) return;

	if (AbilitySystemComponent->HasMatchingGameplayTag
		(FGameplayTag::RequestGameplayTag("State.Healing"))) return;

	if (AbilitySystemComponent->HasMatchingGameplayTag
		(FGameplayTag::RequestGameplayTag("State.Attacking"))) return;

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
	if (!AbilitySystemComponent) return;

	for (FGameplayAbilitySpec& Spec : AbilitySystemComponent->GetActivatableAbilities())
	{
		for (UGameplayAbility* Instance : Spec.GetAbilityInstances())
		{
			if (UBasicBlockingAbility* Block = Cast<UBasicBlockingAbility>(Instance))
			{
				if (Block->IsActive())
				{
					Block->RequestBlockExit();
					return;
				}
			}
		}
	}
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
				UE_LOG(LogTemp,Warning, TEXT("hmm why does it go here and not down"))
				if (AInteractable* Interactable = Cast<AInteractable>(Hit.GetActor()))
				{
					UE_LOG(LogTemp, Warning, TEXT("should interact"));
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
	if (AbilitySystemComponent->HasMatchingGameplayTag(
		FGameplayTag::RequestGameplayTag("State.Healing"))) return;

	FGameplayTag LockOnTag = FGameplayTag::RequestGameplayTag(FName("State.LockedOn"));
	FGameplayTagContainer TagContainer;

	if (AbilitySystemComponent->HasMatchingGameplayTag(LockOnTag))
		TagContainer.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Movement.LockOn.Dash")));
	else
		TagContainer.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Movement.Normal.Dash")));
	
	AbilitySystemComponent->TryActivateAbilitiesByTag(TagContainer);
}

void APlayerCharacter::Heal()
{
	FGameplayTagContainer TagContainer;
	TagContainer.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Heal")));

	AbilitySystemComponent->TryActivateAbilitiesByTag(TagContainer);
}

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

void APlayerCharacter::PlayHitReaction(AActor* Attacker)
{
	if (AbilitySystemComponent->HasMatchingGameplayTag(
		FGameplayTag::RequestGameplayTag("State.Dead"))) return;

	if (!Attacker) return;   // only need an attacker now, not a weapon

	FVector ToAttacker = Attacker->GetActorLocation() - GetActorLocation();
	ToAttacker.Z = 0;
	ToAttacker.Normalize();

	float DotForward = FVector::DotProduct(GetActorForwardVector(), ToAttacker);
	float DotRight = FVector::DotProduct(GetActorRightVector(), ToAttacker);

	UE_LOG(LogTemp, Warning, TEXT("DotForward: %.2f | DotRight: %.2f"), DotForward, DotRight);

	// Pick the montage set: weapon's if armed, defaults if not
	UAnimMontage* MontageF;
	UAnimMontage* MontageB;
	UAnimMontage* MontageL;
	UAnimMontage* MontageR;

	if (Weapon)
	{
		const FWeaponData& WeaponData = Weapon->ItemDefinition->WeaponData;
		MontageF = WeaponData.HitF;
		MontageB = WeaponData.HitB;
		MontageL = WeaponData.HitL;
		MontageR = WeaponData.HitR;
	}
	else
	{
		MontageF = DefaultHitF;
		MontageB = DefaultHitB;
		MontageL = DefaultHitL;
		MontageR = DefaultHitR;
	}

	// Pick direction
	UAnimMontage* HitMontage = nullptr;

	if (DotForward > 0.5f)
	{
		HitMontage = MontageF;
		UE_LOG(LogTemp, Warning, TEXT("Hit direction: FRONT"));
	}
	else if (DotForward < -0.5f)
	{
		HitMontage = MontageB;
		UE_LOG(LogTemp, Warning, TEXT("Hit direction: BACK"));
	}
	else if (DotRight < 0.f)
	{
		HitMontage = MontageL;
		UE_LOG(LogTemp, Warning, TEXT("Hit direction: RIGHT"));
	}
	else
	{
		HitMontage = MontageR;
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

void APlayerCharacter::EnableHitbox() const
{
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
}

void APlayerCharacter::DisableHitbox() const
{
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
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

	FVector DirectionToTarget = LockOnTarget->GetActorLocation() - GetActorLocation();
	FRotator TargetRotation = DirectionToTarget.Rotation();
	FRotator NewRotation = FMath::RInterpTo(GetControlRotation(), TargetRotation, DeltaTime, 20.f);
	NewRotation.Roll = 0;
	NewRotation.Pitch += LockOnOffsetZ;
	GetController()->SetControlRotation(NewRotation);


	bool bDodging = AbilitySystemComponent->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag("State.Dodging"));

	if (bDodging)
	{
		if (bDodgeDirectionLocked) return;
		bDodgeDirectionLocked = true;

		FVector Input = GetCharacterMovement()->GetLastInputVector();
		FVector ToTarget = DirectionToTarget; ToTarget.Z = 0.f; ToTarget.Normalize();
		FVector RightOfTarget = FVector::CrossProduct(FVector::UpVector, ToTarget);

		FVector DodgeDir;
		if (Input.IsNearlyZero())
		{
			DodgeDir = -ToTarget;
			UE_LOG(LogTemp, Warning, TEXT("DODGE: no input -> backstep"));
		}
		else
		{
			Input.Z = 0.f; Input.Normalize();
			float fwd = FVector::DotProduct(Input, ToTarget);
			float right = FVector::DotProduct(Input, RightOfTarget);
			UE_LOG(LogTemp, Warning, TEXT("DODGE: Input=%s fwd=%.2f right=%.2f"),
				*Input.ToString(), fwd, right);

			if (FMath::Abs(right) > FMath::Abs(fwd))
			{
				// Lateral dodge, but biased toward the enemy so it arcs inward (diagonal)
				FVector LateralDir = (right > 0.f) ? RightOfTarget : -RightOfTarget;
				// Blend in some "toward target" — tune InwardBias 0..1
				float InwardBias = 0.6f; // 0 = pure sideways, 1 = straight at enemy
				DodgeDir = (LateralDir * (1.f - InwardBias) + ToTarget * InwardBias).GetSafeNormal();
			}
			else
			{
				DodgeDir = (fwd > 0.f) ? ToTarget : -ToTarget;
			}
		}
		UE_LOG(LogTemp, Warning, TEXT("DODGE: chosen DodgeDir=%s"), *DodgeDir.ToString());

		FRotator DodgeRot = DodgeDir.Rotation();
		DodgeRot.Pitch = 0.f; DodgeRot.Roll = 0.f;
		SetActorRotation(DodgeRot);
		return;
	}
	else
		bDodgeDirectionLocked = false;

	// Normal locked-on body rotation toward target
	FRotator NewCharacterRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, DeltaTime, 10.f);
	NewCharacterRotation.Pitch = 0.f;
	NewCharacterRotation.Roll = 0.f;
	SetActorRotation(NewCharacterRotation);
}

void APlayerCharacter::UseHotbarSlot(int32 Index)
{
	if (!HotbarSlots.IsValidIndex(Index) || !HotbarSlots[Index]) return;
	if (HotbarSlots[Index]->ItemType != EItemType::Weapon) return;

	TSubclassOf<AMeleeWeapon> NewWeaponClass = HotbarSlots[Index]->GetWeaponClass();
	if (!NewWeaponClass) return;

	// Pressing the slot of the already-equipped weapon → unequip
	if (Weapon && Weapon->ItemDefinition == HotbarSlots[Index])
	{
		UnequipWeapon();
		return;
	}

	EquipWeapon(NewWeaponClass);
}

void APlayerCharacter::EquipHealingItem(UItemDefinition* ItemDef, int SlotIndex)
{
	if (!ItemDef) return;
	if (ItemDef->ItemType != EItemType::Consumable) return;   // only consumables

	HealingItem = ItemDef;
	HealingItemSlotIndex = SlotIndex;
}

void APlayerCharacter::UnequipHealingItem()
{
	HealingItem = nullptr;
}

void APlayerCharacter::ConsumeHealItem()
{
	if (!HealingItem || !AbilitySystemComponent) return;

	GetGameInstance()->GetSubsystem<UInventorySubsystem>()->GetInventory(this)->RemoveFromItemQuantity(HealingItemSlotIndex, 1);
}