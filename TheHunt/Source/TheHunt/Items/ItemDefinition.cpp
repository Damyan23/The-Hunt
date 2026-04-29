// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemDefinition.h"

UItemDefinition::UItemDefinition()
{
	
}

TSubclassOf<AMeleeWeapon> UItemDefinition::GetWeaponClass() const
{
	if (!ItemClass) return nullptr;

	if (ItemClass->IsChildOf(AMeleeWeapon::StaticClass()))
	{
		return TSubclassOf<AMeleeWeapon>(ItemClass);
	}

	return nullptr;
}