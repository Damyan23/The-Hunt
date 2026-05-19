// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/WeaponDescription.h"

void UWeaponDescription::SetDescription(UItemDefinition* ItemDefinition)
{
    if (!ItemDefinition) return;

    const FWeaponData& WeaponData = ItemDefinition->WeaponData;

    ItemName->SetText(FText::FromName(ItemDefinition->ItemName));
    ItemDescription->SetText(ItemDefinition->ItemDescription);

    ItemIcon->SetBrushFromTexture(ItemDefinition->ItemIcon);

    // Stats
    PhysicalAttack->SetText(FText::AsNumber(WeaponData.PhysicalAttack));
    MagicAttack->SetText(FText::AsNumber(WeaponData.MagicalAttack));
    StructureDamage->SetText(FText::AsNumber(WeaponData.StructureDamage));
    GuardDMGNegation->SetText(FText::AsNumber(WeaponData.GuardDamageNegation));

    // Attack type
    switch (WeaponData.AttackType)
    {
    case EAttackType::Slash:
        AttackType->SetText(FText::FromString("Slash"));
        break;
    case EAttackType::Stab:
        AttackType->SetText(FText::FromString("Stab"));
        break;
    }

    // Weight
    switch (WeaponData.Weight)
    {
    case EWeigh::Nimble:
        AttackWeight->SetText(FText::FromString("Nimble"));
        break;
    case EWeigh::Heavy:
        AttackWeight->SetText(FText::FromString("Heavy"));
        break;
    }

    // Runes
    TArray<TObjectPtr<UImage>> RuneImages = { Rune1, Rune2, Rune3 };
    TArray<TObjectPtr<UTextBlock>> RuneDescriptions = { Rune1Description, Rune2Description, Rune3Description };

    for (int32 i = 0; i < 3; i++)
    {
        if (WeaponData.Runes.IsValidIndex(i) && WeaponData.Runes[i])
        {
            URuneBase* Rune = WeaponData.Runes[i];

            // Set rune icon
            if (RuneImages[i] && !Rune->RuneIcon.IsNull())
            {
                UTexture2D* Icon = Rune->RuneIcon.LoadSynchronous();
                if (Icon)
                {
                    FSlateBrush Brush;
                    Brush.SetResourceObject(Icon);
                    RuneImages[i]->SetBrush(Brush);
                }
            }

            // Set rune description
            if (RuneDescriptions[i])
                RuneDescriptions[i]->SetText(Rune->RuneDescription);
        }
        else
        {
            // Hide empty rune slots
            if (RuneImages[i])
                RuneImages[i]->SetVisibility(ESlateVisibility::Hidden);
            if (RuneDescriptions[i])
                RuneDescriptions[i]->SetVisibility(ESlateVisibility::Hidden);
        }
    }
}
