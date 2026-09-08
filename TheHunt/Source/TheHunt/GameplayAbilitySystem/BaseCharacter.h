// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AttributeSet.h"
#include "GameplayEffectTypes.h"
#include "GameplayEffect.h"
#include "BaseAttributeSet.h"
#include "Abilities/GameplayAbility.h"
#include "NiagaraSystem.h"
#include "BaseCharacter.generated.h"

class AMeleeWeapon;

UCLASS()
class THEHUNT_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ABaseCharacter();

	virtual void Tick(float DeltaTime) override;

	//~ Ability System
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	//============================================================
	//  Ability System
	//============================================================
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<UBaseAttributeSet> BaseAttributes;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TSubclassOf<UGameplayEffect> StaminaRegen;

	//============================================================
	//  Weapon
	//============================================================
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<AMeleeWeapon> WeaponClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	TObjectPtr<AMeleeWeapon> Weapon;

	//============================================================
	//  Combat
	//============================================================
public:
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<UGameplayEffect> StaggerResetEffect;

	virtual void Die();

	//============================================================
	//  Attribute Change Delegates (Blueprint-assignable)
	//============================================================
public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, HealthPercent);
	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnHealthChanged OnHealthChangedEvent;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStaminaChanged, float, StaminaPercent);
	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnStaminaChanged OnStaminaChangedEvent;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStaggerChanged, float, StaggerPercent);
	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnStaggerChanged OnStaggerChangedEvent;

	//============================================================
	//  Animation
	//============================================================
public:
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	TObjectPtr<UAnimMontage> GettingHitMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	TObjectPtr<UAnimMontage> DeathMontage;

	//============================================================
	//  VFX
	//============================================================
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* HitVFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* BlockVFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* ParryVFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* PoisonVFX;

	//============================================================
	//  Sound — General
	//============================================================
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound FX")
	TObjectPtr<USoundBase> GettingHitSound;

	//============================================================
	//  Sound — Footsteps
	//============================================================
protected:
	UPROPERTY(EditAnywhere, Category = "Footsteps")
	TArray<USoundBase*> BootSounds;

	UPROPERTY(EditAnywhere, Category = "Footsteps")
	TArray<USoundBase*> SurfaceSounds;

	UPROPERTY(EditAnywhere, Category = "Footsteps")
	TArray<USoundBase*> WeatherLayerSounds;

	//============================================================
	//  Stamina Regen
	//============================================================
public:
	void StartStaminaRegenDelay();
	void AllowStaminaRegen();

	FTimerHandle StaminaRegenDelayTimer;
	bool bStaminaRegenAllowed = true;

	//============================================================
	//  Lifecycle / Setup
	//============================================================
protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

	void InitializeAttributes();
	void GrantDefaultAbilities();

	UFUNCTION(BlueprintCallable)
	virtual void AttachWeapon();

	//============================================================
	//  Attribute Change Handlers
	//============================================================
protected:
	virtual void OnHealthChanged(const FOnAttributeChangeData& Data);
	virtual void OnStaminaChanged(const FOnAttributeChangeData& Data);
	virtual void OnStaggerChanged(const FOnAttributeChangeData& Data);
	virtual void OnGuardBroken();

	virtual void OnDeath();

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void OnHealthUpdated(float CurrentHealth, float MaxHealth);

	//============================================================
	//  Sound / Footstep Helpers
	//============================================================
protected:
	UFUNCTION(BlueprintCallable)
	void PlayFootstepSounds();

	void PlayRandomSoundAtLocation(const TArray<USoundBase*>& Sounds, FVector Location);
};