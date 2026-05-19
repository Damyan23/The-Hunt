// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/WeaponDescription.h"

void UWeaponDescription::SetDescription(UItemDefinition* ItemDefinition)
{
    if (!ItemDefinition) return;

    // Set common fields available on all item types
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

    // Runes
    TArray<TObjectPtr<UImage>> RuneImages = { Rune1, Rune2, Rune3 };
    TArray<TObjectPtr<UTextBlock>> RuneDescs = { Rune1Description, Rune2Description, Rune3Description };

    for (int32 i = 0; i < 3; i++)
    {
        if (WeaponData.Runes.IsValidIndex(i) && WeaponData.Runes[i])
        {
            UE_LOG(LogTemp, Warning, TEXT("ok goes in here so wtf??"))
            URuneBase* Rune = WeaponData.Runes[i];
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
            if (RuneDescs[i])
                RuneDescs[i]->SetText(Rune->RuneDescription);
        }
        else
        {
            // Swap to empty rune container
            if (RuneImages[i])
                RuneImages[i]->SetVisibility(ESlateVisibility::Hidden);
            if (RuneDescs[i])
                RuneDescs[i]->SetText(FText::FromString("No Sigil Equipped"));
        }
    }
}

void UWeaponDescription::SetConsumableDescription(UItemDefinition* ItemDefinition)
{
    // Hide weapon-specific widgets
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

    // Add consumable-specific data here when ready
    // e.g. ConsumableData.HealthRestore etc.
}

void UWeaponDescription::SetRuneDescription(UItemDefinition* ItemDefinition)
{
    // Hide weapon-specific widgets
    PhysicalAttack->SetVisibility(ESlateVisibility::Hidden);
    MagicAttack->SetVisibility(ESlateVisibility::Hidden);
    StructureDamage->SetVisibility(ESlateVisibility::Hidden);
    GuardDMGNegation->SetVisibility(ESlateVisibility::Hidden);
    AttackType->SetVisibility(ESlateVisibility::Hidden);
    AttackWeight->SetVisibility(ESlateVisibility::Hidden);

    // Show rune icon and description for the rune item itself
    if (Rune1 && ItemDefinition->RuneData.Rune)
    {
        URuneBase* Rune = ItemDefinition->RuneData.Rune;
        if (!Rune->RuneIcon.IsNull())
        {
            UTexture2D* Icon = Rune->RuneIcon.LoadSynchronous();
            if (Icon)
            {
                FSlateBrush Brush;
                Brush.SetResourceObject(Icon);
                Rune1->SetBrush(Brush);
                Rune1->SetVisibility(ESlateVisibility::Visible);
            }
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
