// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemSoundData.h"

TArray<USoundBase*> UItemSoundData::GetPickupSounds(UItemDefinition* ItemDef)
{
    if (!ItemDef) return {};

    if (ItemDef->ItemType == EItemType::Weapon)
    {
        EWeaponType WeaponType = ItemDef->WeaponData.WeaponType;
        if (FGenericItemSoundSet* Override = WeaponSounds.WeaponTypeOverrides.Find(WeaponType))
            if (!Override->PickupSounds.IsEmpty())
                return Override->PickupSounds;

        UE_LOG(LogTemp, Warning, TEXT("ok so it gets the generic one"));
        return WeaponSounds.GenericItemSounds.PickupSounds;
    }

    if (FGenericItemSoundSet* SoundSet = ItemSounds.Find(ItemDef->ItemType))
        return SoundSet->PickupSounds;

    return {};
}

TArray<USoundBase*> UItemSoundData::GetEquipSounds(UItemDefinition* ItemDef)
{
    if (!ItemDef) return {};

    if (ItemDef->ItemType == EItemType::Weapon)
    {
        EWeaponType WeaponType = ItemDef->WeaponData.WeaponType;
        if (FGenericItemSoundSet* Override = WeaponSounds.WeaponTypeOverrides.Find(WeaponType))
            if (!Override->EquipSounds.IsEmpty())
                return Override->EquipSounds;
        return WeaponSounds.GenericItemSounds.EquipSounds;
    }

    if (FGenericItemSoundSet* SoundSet = ItemSounds.Find(ItemDef->ItemType))
        return SoundSet->EquipSounds;

    return {};
}

TArray<USoundBase*> UItemSoundData::GetDropSounds(UItemDefinition* ItemDef)
{
    if (!ItemDef) return {};

    if (ItemDef->ItemType == EItemType::Weapon)
    {
        EWeaponType WeaponType = ItemDef->WeaponData.WeaponType;
        if (FGenericItemSoundSet* Override = WeaponSounds.WeaponTypeOverrides.Find(WeaponType))
            if (!Override->DropSounds.IsEmpty())
                return Override->DropSounds;
        return WeaponSounds.GenericItemSounds.DropSounds;
    }

    if (FGenericItemSoundSet* SoundSet = ItemSounds.Find(ItemDef->ItemType))
        return SoundSet->DropSounds;

    return {};
}

void UItemSoundData::PlayRandomSoundAtLocation(const TArray<USoundBase*>& Sounds, UWorld* World, FVector Location)
{
    if (Sounds.IsEmpty()) return;
    int32 Index = FMath::RandRange(0, Sounds.Num() - 1);
    if (Sounds[Index])
        UGameplayStatics::PlaySoundAtLocation(World, Sounds[Index], Location);
}

void UItemSoundData::PlayRandomSound2D(const TArray<USoundBase*>& Sounds, UObject* WorldContext, float StartTime)
{
    if (Sounds.IsEmpty()) return;
    int32 Index = FMath::RandRange(0, Sounds.Num() - 1);
    if (Sounds[Index])
        UGameplayStatics::PlaySound2D(WorldContext, Sounds[Index], 1, 1, StartTime);
}
