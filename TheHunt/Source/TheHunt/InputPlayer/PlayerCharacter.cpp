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
#include "Items/Weapon/MeleeWeapon.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AISense_Sight.h"

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
		RootComponent,
		FAttachmentTransformRules::SnapToTargetNotIncludingScale);

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
	}
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

