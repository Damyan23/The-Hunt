// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AttributeSet.h"
#include "BaseAttributeSet.h"
#include "Abilities/GameplayAbility.h"
#include "Items/Weapon/MeleeWeapon.h"
#include "BaseCharacter.generated.h"

/**
 * 
 */
UCLASS()
class THEHUNT_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:
	virtual void PostInitializeComponents() override;
	void InitializeAttributes();
	void GrantDefaultAbilities();

	UFUNCTION()
	virtual void AttachWeapon();

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<AMeleeWeapon> WeaponClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon");
	TObjectPtr<AMeleeWeapon> Weapon;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AbilitySystem")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<UBaseAttributeSet> BaseAttributes;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;
	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TSubclassOf<UGameplayEffect> StaminaRegen;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	TObjectPtr<UAnimMontage> GettingHitMontage;
	UPROPERTY(EditDefaultsOnly, Category="Animation")
	TObjectPtr<UAnimMontage> StaggerMontage;
	UPROPERTY(EditDefaultsOnly, Category="Stagger")
	float StunDuration = 1.5f;
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<UGameplayEffect> StaggerResetEffect;

	virtual void Die();

protected:
	virtual void OnHealthChanged(const FOnAttributeChangeData& Data);
	virtual void OnStaggerChanged(const FOnAttributeChangeData& Data);

	virtual void OnGuardBroken();
};
