// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/WeaponDescription.h"

void UWeaponDescription::SetDescription(UItemDefinition* ItemDefinition)
{
    if (!ItemDefinition) return;

    Rune1->SetVisibility(ESlateVisibility::Hidden);
    Rune2->SetVisibility(ESlateVisibility::Hidden);
    Rune3->SetVisibility(ESlateVisibility::Hidden);
    Rune1Description->SetVisibility(ESlateVisibility::Hidden);
    Rune2Description->SetVisibility(ESlateVisibility::Hidden);
    Rune3Description->SetVisibility(ESlateVisibility::Hidden);

    // Set common fields
    ItemName->SetText(FText::FromName(ItemDefinition->ItemName));
    ItemDescription->SetText(ItemDefinition->ItemDescription);
    ItemIcon->SetBrushFromTexture(ItemDefinition->ItemIcon);

    switch (ItemDefinition->ItemType)
    {
    case EItemType::Weapon:
        SetWeaponDescription(ItemDefinition);
        break;
    case EItemType::Consumable:
        SetConsumableDescription(ItemDefinition);
        break;
    case EItemType::Rune:
        SetRuneDescription(ItemDefinition);
        break;
    default:
        break;
    }
}

void UWeaponDescription::SetWeaponDescription(UItemDefinition* ItemDefinition)
{
    const FWeaponData& WeaponData = ItemDefinition->WeaponData;

    // Show weapon-specific widgets
    PhysicalAttack->SetVisibility(ESlateVisibility::Visible);
    MagicAttack->SetVisibility(ESlateVisibility::Visible);
    StructureDamage->SetVisibility(ESlateVisibility::Visible);
    GuardDMGNegation->SetVisibility(ESlateVisibility::Visible);
    AttackType->SetVisibility(ESlateVisibility::Visible);
    AttackWeight->SetVisibility(ESlateVisibility::Visible);

    PhysicalAttack->SetText(FText::AsNumber(WeaponData.PhysicalAttack));
    MagicAttack->SetText(FText::AsNumber(WeaponData.MagicalAttack));
    StructureDamage->SetText(FText::AsNumber(WeaponData.StructureDamage));
    GuardDMGNegation->SetText(FText::AsNumber(WeaponData.GuardDamageNegation));

    switch (WeaponData.AttackType)
    {
    case EAttackType::Slash:
        AttackType->SetText(FText::FromString("Slash"));
        break;
    case EAttackType::Stab:
        AttackType->SetText(FText::FromString("Stab"));
        break;
    }

    switch (WeaponData.Weight)
    {
    case EWeigh::Nimble:
        AttackWeight->SetText(FText::FromString("Nimble"));
        break;
    case EWeigh::Heavy:
        AttackWeight->SetText(FText::FromString("Heavy"));
        break;
    }

    UE_LOG(LogTemp, Warning, TEXT("=== SetWeaponDescription ==="));
    UE_LOG(LogTemp, Warning, TEXT("  Runes in WeaponData: %d"), ItemDefinition->WeaponData.Runes.Num());

    // Runes — read from weapon actor if available
    TArray<TObjectPtr<UImage>> RuneImages = { Rune1, Rune2, Rune3 };
    TArray<TObjectPtr<UTextBlock>> RuneDescs = { Rune1Description, Rune2Description, Rune3Description };

    for (int32 i = 0; i < 3; i++)
    {
        UE_LOG(LogTemp, Warning, TEXT("  Rune[%d]: %s"), i,
            ItemDefinition->WeaponData.Runes[i] ? *ItemDefinition->WeaponData.Runes[i]->GetName() : TEXT("NULL"));
        if (WeaponData.Runes.IsValidIndex(i) && WeaponData.Runes[i])
        {
            URuneBase* Rune = WeaponData.Runes[i];
            RuneImages[i]->SetVisibility(ESlateVisibility::Visible);
            RuneDescs[i]->SetVisibility(ESlateVisibility::Visible);

            if (Rune->RuneIcon)
            {
                FSlateBrush Brush;
                Brush.SetResourceObject(Rune->RuneIcon);
                RuneImages[i]->SetBrush(Brush);
            }
            RuneDescs[i]->SetText(Rune->RuneDescription);
        }
    }
}

void UWeaponDescription::SetConsumableDescription(UItemDefinition* ItemDefinition)
{
    PhysicalAttack->SetVisibility(ESlateVisibility::Hidden);
    MagicAttack->SetVisibility(ESlateVisibility::Hidden);
    StructureDamage->SetVisibility(ESlateVisibility::Hidden);
    GuardDMGNegation->SetVisibility(ESlateVisibility::Hidden);
    AttackType->SetVisibility(ESlateVisibility::Hidden);
    AttackWeight->SetVisibility(ESlateVisibility::Hidden);
    Rune1->SetVisibility(ESlateVisibility::Hidden);
    Rune2->SetVisibility(ESlateVisibility::Hidden);
    Rune3->SetVisibility(ESlateVisibility::Hidden);
    Rune1Description->SetVisibility(ESlateVisibility::Hidden);
    Rune2Description->SetVisibility(ESlateVisibility::Hidden);
    Rune3Description->SetVisibility(ESlateVisibility::Hidden);
}

void UWeaponDescription::SetRuneDescription(UItemDefinition* ItemDefinition)
{
    PhysicalAttack->SetVisibility(ESlateVisibility::Hidden);
    MagicAttack->SetVisibility(ESlateVisibility::Hidden);
    StructureDamage->SetVisibility(ESlateVisibility::Hidden);
    GuardDMGNegation->SetVisibility(ESlateVisibility::Hidden);
    AttackType->SetVisibility(ESlateVisibility::Hidden);
    AttackWeight->SetVisibility(ESlateVisibility::Hidden);

    if (Rune1 && ItemDefinition->RuneData.Rune)
    {
        URuneBase* Rune = ItemDefinition->RuneData.Rune;
        if (Rune->RuneIcon)
        {
            FSlateBrush Brush;
            Brush.SetResourceObject(Rune->RuneIcon);
            Rune1->SetBrush(Brush);
            Rune1->SetVisibility(ESlateVisibility::Visible);
            
        }
        if (Rune1Description)
        {
            Rune1Description->SetText(Rune->RuneDescription);
            Rune1Description->SetVisibility(ESlateVisibility::Visible);
        }
    }

    Rune2->SetVisibility(ESlateVisibility::Hidden);
    Rune3->SetVisibility(ESlateVisibility::Hidden);
    Rune2Description->SetVisibility(ESlateVisibility::Hidden);
    Rune3Description->SetVisibility(ESlateVisibility::Hidden);
}

void UWeaponDescription::SetSingleRuneDescription(URuneBase* Rune)
{
    // Hide all weapon stats
    PhysicalAttack->SetVisibility(ESlateVisibility::Hidden);
    MagicAttack->SetVisibility(ESlateVisibility::Hidden);
    StructureDamage->SetVisibility(ESlateVisibility::Hidden);
    GuardDMGNegation->SetVisibility(ESlateVisibility::Hidden);
    AttackType->SetVisibility(ESlateVisibility::Hidden);
    AttackWeight->SetVisibility(ESlateVisibility::Hidden);

    // Hide all rune slots by default
    Rune1->SetVisibility(ESlateVisibility::Hidden);
    Rune2->SetVisibility(ESlateVisibility::Hidden);
    Rune3->SetVisibility(ESlateVisibility::Hidden);
    Rune1Description->SetVisibility(ESlateVisibility::Hidden);
    Rune2Description->SetVisibility(ESlateVisibility::Hidden);
    Rune3Description->SetVisibility(ESlateVisibility::Hidden);

    if (!Rune) return;

    if (Rune->RuneIcon)
    {
        FSlateBrush Brush;
        Brush.SetResourceObject(Rune->RuneIcon);
        Rune1->SetBrush(Brush);
        Rune1->SetVisibility(ESlateVisibility::Visible);
    }

    if (Rune1Description)
    {
        Rune1Description->SetText(Rune->RuneDescription);
        Rune1Description->SetVisibility(ESlateVisibility::Visible);
    }
}