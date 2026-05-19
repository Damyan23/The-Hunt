// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/ItemDefinitionDescription.h"
#include "Items/ItemDefinition.h"
#include "WeaponDescription.generated.h"

/**
 * 
 */
UCLASS()
class THEHUNT_API UWeaponDescription : public UItemDefinitionDescription
{
	GENERATED_BODY()

public:
	void SetDescription(UItemDefinition* ItemDefinition);
private:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> PhysicalAttack;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> MagicAttack;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> StructureDamage;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> GuardDMGNegation;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> AttackType;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> AttackWeight;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UImage> Rune1;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UImage> Rune2;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UImage> Rune3;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> Rune1Description;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> Rune2Description;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> Rune3Description;

};
