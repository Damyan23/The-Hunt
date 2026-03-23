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



