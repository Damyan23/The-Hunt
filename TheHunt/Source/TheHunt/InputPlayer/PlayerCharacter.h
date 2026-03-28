#pragma once
#include "CoreMinimal.h"
#include "GameplayAbilitySystem/BaseCharacter.h"
#include "InputActionValue.h"
#include "Components/PostProcessComponent.h"
#include "Inventory/UI/InventoryWidget.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class THEHUNT_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

	UPROPERTY(Visibleanywhere, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;	

	APlayerController* PC;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> ArmsMesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAIPerceptionStimuliSourceComponent> StimuliSource;

protected:
	virtual void AttachWeapon() override;

	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput", meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput", meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput", meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput", meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput", meta = (AllowPrivateAccess = "true"))
	class UInputAction* InteractAction;
	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput", meta = (AllowPrivateAccess = "true"))
	class UInputAction* AttackAction;

	UPROPERTY(EditAnywhere, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	float InteractionSphereRadius = 50.f;

	UPROPERTY(EditAnywhere, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	float InteractionDistance = 500.f;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UInventoryWidget> InventoryWidgetClass;
	UPROPERTY()
	TObjectPtr<UInventoryWidget> InventoryWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	class UInputAction* InventoryAction;

	UPROPERTY(VisibleAnywhere)
	UPostProcessComponent* PostProcessComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UMaterialInterface* HitVignetteMaterial;

	UPROPERTY()
	UMaterialInstanceDynamic* HitVignetteMID;

	virtual void OnHealthChanged(const FOnAttributeChangeData& Data) override;
	void ShowHitVignette();

	UPROPERTY(EditDefaultsOnly, Category="Effects")
	FTimerHandle HitVignetteTimer;

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Jump();
	void Attack();
	void Interact();
	void ToggleInventory();
};
