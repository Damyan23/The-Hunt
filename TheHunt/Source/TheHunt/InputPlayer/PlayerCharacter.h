#pragma once
#include "CoreMinimal.h"
#include "GameplayAbilitySystem/BaseCharacter.h"
#include "InputActionValue.h"
#include "Components/PostProcessComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Inventory/UI/InventoryWidget.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perks/PerkData.h"
#include "Perks/PerkSlot.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class THEHUNT_API APlayerCharacter : public ABaseCharacter
{
    GENERATED_BODY()

    // ============================================================
    // CORE COMPONENTS
    // ============================================================
    UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
    class UCameraComponent* Camera;

    UPROPERTY(VisibleAnywhere)
    TObjectPtr<USpringArmComponent> SpringArm;

    UPROPERTY(VisibleAnywhere)
    TObjectPtr<UAIPerceptionStimuliSourceComponent> StimuliSource;

    UPROPERTY(VisibleAnywhere)
    UPostProcessComponent* PostProcessComponent;

    APlayerController* PC;

    // ============================================================
    // CAMERA
    // ============================================================
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
    float SpringArmDistance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
    FVector SpringArmOffset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
    FRotator SpringArmRotation;

    UPROPERTY(EditAnywhere, Category = "Camera")
    float NormalCameraLag = 0.1f;

    UPROPERTY(EditAnywhere, Category = "Camera")
    float LockOnCameraLag = 0.3f;

    // ============================================================
    // INPUT
    // ============================================================
    UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
    class UInputMappingContext* InputMapping;

    UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
    class UInputAction* MoveAction;

    UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
    class UInputAction* LookAction;

    UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
    class UInputAction* JumpAction;

    UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
    class UInputAction* InteractAction;

    UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
    class UInputAction* AttackAction;

    UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
    class UInputAction* BlockAction;

    UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
    class UInputAction* DashAction;

    UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
    class UInputAction* LockOnAction;

    UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
    class UInputAction* InventoryAction;

    UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
    class UInputAction* ToggleCombatAction;

    UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
    class UInputAction* HealAction;

    // ============================================================
    // LOCK-ON
    // ============================================================
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Lock-On")
    float LockOnDetectionRadius = 500.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Lock-On")
    float LockOnRange;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Lock-On")
    float LockOnOffsetZ = 20.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Lock-On")
    float TargetingHeightOffset = 20.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Lock-On")
    float TargetSwitchThreshold = 1.5f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Lock-On")
    float TargetSwitchCooldown = 0.2f;

    UPROPERTY()
    TObjectPtr<AActor> LockOnTarget;

    float TargetSwitchCooldownTimer = 0.f;
    FVector2D LastMouseDelta;
    // ============================================================
    // Combat
    // ============================================================
private:
    ECombatType CombatType = ECombatType::Unarmed;

    FVector DodgeDirection = FVector::ZeroVector;
    bool bDodgeDirectionLocked = false;
    
    UPROPERTY(EditAnywhere, Category = "Animation|Hit Reactions")
    UAnimMontage* DefaultHitF;

    UPROPERTY(EditAnywhere, Category = "Animation|Hit Reactions")
    UAnimMontage* DefaultHitB;

    UPROPERTY(EditAnywhere, Category = "Animation|Hit Reactions")
    UAnimMontage* DefaultHitL;

    UPROPERTY(EditAnywhere, Category = "Animation|Hit Reactions")
    UAnimMontage* DefaultHitR;
protected:
    // ============================================================
    // INVENTORY & HOTBAR
    // ============================================================
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UInventoryWidget> InventoryWidgetClass;

    UPROPERTY()
    TObjectPtr<UInventoryWidget> InventoryWidget;

    UPROPERTY()
    TArray<TObjectPtr<UItemDefinition>> HotbarSlots;

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponEquippedFromSlot, int, SlotIndex);
    UPROPERTY(BlueprintAssignable)
    FOnWeaponEquippedFromSlot OnWeaponEquippedFromSlotEvent;

    UPROPERTY()
    int EquippedWeaponSlotIndex;

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPotionEquippedFromSlot, int, SlotIndex);
    UPROPERTY(BlueprintAssignable)
    FOnPotionEquippedFromSlot OnPotionEquippedFromSlotEvent;
public:
    // ============================================================
    // PERKS
    // ============================================================
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TArray<FPerkSlot> Perks;

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPerkApplied, FPerkSlot, PerkSlot);

    UPROPERTY(BlueprintAssignable, Category = "Perks")
    FOnPerkApplied OnPerkApplied;
protected:

    // ============================================================
    // INTERACTION
    // ============================================================
    UPROPERTY(EditAnywhere, Category = "Interaction")
    float InteractionSphereRadius = 50.f;

    UPROPERTY(EditAnywhere, Category = "Interaction")
    float InteractionDistance = 500.f;

    // ============================================================
    // EFFECTS
    // ============================================================
    UPROPERTY(EditDefaultsOnly, Category = "Effects")
    UMaterialInterface* HitVignetteMaterial;

    UPROPERTY()
    UMaterialInstanceDynamic* HitVignetteMID;

    UPROPERTY(EditDefaultsOnly, Category = "Effects")
    FTimerHandle HitVignetteTimer;

    // ============================================================
    // FOOTSTEPS
    // ============================================================
    UPROPERTY(EditAnywhere, Category = "Footsteps")
    float FootstepInterval = 0.4f;

    FTimerHandle FootstepTimerHandle;

    // ============================================================
    // HEALING
    // ============================================================

public:
    UPROPERTY()
    TObjectPtr<UItemDefinition> HealingItem;

    UPROPERTY()
    int HealingItemSlotIndex;

    // ============================================================
    // COMBAT
    // ============================================================
public:
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponEquipped, ECombatType, NewCombatType);

    UPROPERTY(BlueprintAssignable, Category = "Combat")
    FOnWeaponEquipped OnWeaponEquipped;

    void OnBlockBrokenMontageEnded(UAnimMontage* Montage, bool bInterrupted);

    // ============================================================
    // PERKS   
    // ============================================================
    UFUNCTION(BlueprintCallable)
    void ApplyPerk(UPerkData* Perk);
protected:
    // ============================================================
    // OVERRIDES
    // ============================================================
    virtual void AttachWeapon() override;
    virtual void OnHealthChanged(const FOnAttributeChangeData& Data) override;
    virtual void BeginPlay() override;
    virtual void OnConstruction(const FTransform& Transform) override;
    virtual void OnGuardBroken() override;
    virtual void OnDeath() override;

    // ============================================================
    // INPUT HANDLERS
    // ============================================================
    void Move(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);
    void Jump();
    void Attack();
    void StartBlock();
    void StopBlock();
    void Interact();
    void ToggleInventory();
    void Dash();
    void Heal();

    // ============================================================
    // LOCK-ON LOGIC
    // ============================================================
    void ToggleLockOn();
    void UpdateLockOn(float DeltaTime);
    TArray<TObjectPtr<AActor>> GetPossibleLockOnTargetsWithinRange();
    TObjectPtr<AActor> FindBestTarget(FVector Direction = FVector::ZeroVector);

    // ============================================================
    // MISC
    // ============================================================
    void ShowHitVignette();
    void PlayHitReaction(AActor* Attacker);

private:
    void UseHotbarSlot(int32 Index);

    // ============================================================
    // DEATH STATE
    // ============================================================
    UPROPERTY(EditDefaultsOnly, Category = "Death")
    TSubclassOf<UUserWidget> DeathScreenWidgetClass;

    UPROPERTY()
    TObjectPtr<UUserWidget> DeathScreenWidget;

    UPROPERTY(EditDefaultsOnly, Category = "Death")
    float DeathScreenDuration = 3.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Death")
    TSubclassOf<UGameplayEffect> ReviveEffect;

    UFUNCTION()
    void OnDeathMontageEnded(UAnimMontage* Montage, bool bInterrupted);

    void ShowDeathScreen();
    void Respawn();



public:
    UPROPERTY(BlueprintReadWrite, Category = "Death")
    FVector LastSpawnPoint = FVector::ZeroVector;
    // ============================================================
    // SAVE DATA
    // ============================================================
    FPlayerProgressionData GatherProgression();
    void ApplyProgression(const FPlayerProgressionData& Data);

    // ============================================================
    // HEALING
    // ============================================================
    UFUNCTION(BlueprintCallable)
    void EquipHealingItem(UItemDefinition* ItemDef, int SlotIndex);

    UFUNCTION(BlueprintCallable)
    void UnequipHealingItem();

    UFUNCTION(BlueprintCallable)
    void ConsumeHealItem();

    // ============================================================
    // PUBLIC API
    // ============================================================
    APlayerCharacter();

    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UFUNCTION(BlueprintCallable)
    void EquipWeapon(TSubclassOf<AMeleeWeapon> NewWeaponClass, int SlotIndex, UItemDefinition* SourceItemDef);

    UPROPERTY()
    UItemDefinition* PendingWeaponItemDef;

    UFUNCTION(BlueprintCallable)
    float UnequipWeapon();

    void BindItemToSlot(UItemDefinition* ItemDefinition, int32 HotbarSlotIndex);
    void EquipRuneToWeapon(UItemDefinition* RuneDef);

    void EnableHitbox() const;
    void DisableHitbox() const;

    bool IsLockedOn() const {
        return AbilitySystemComponent->HasMatchingGameplayTag(
            FGameplayTag::RequestGameplayTag("State.LockedOn"));
    }

    AActor* GetLockOnTarget() const { return LockOnTarget; }

};