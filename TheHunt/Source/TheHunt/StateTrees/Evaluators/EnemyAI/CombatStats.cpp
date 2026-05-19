// Fill out your copyright notice in the Description page of Project Settings.


#include "StateTrees/Evaluators/EnemyAI/CombatStats.h"

void UCombatStats::TreeStart(FStateTreeExecutionContext& Context)
{
	Super::TreeStart(Context);

    if (Character) ASC = Character->AbilitySystemComponent;

    ASC->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetHealthAttribute())
        .AddUObject(this, &UCombatStats::OnHealthChanged);
    ASC->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetStaminaAttribute())
        .AddUObject(this, &UCombatStats::OnStaminaChanged);
    ASC->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetStaggerAttribute())
        .AddUObject(this, &UCombatStats::OnStaggerChanged);

    MaxStagger = ASC->GetNumericAttribute(UBaseAttributeSet::GetMaxStaggerAttribute());

    // Read the cost once at start since GE values don't change at runtime
    if (AttackStaminaCostEffect)
    {
        const UGameplayEffect* GE = AttackStaminaCostEffect->GetDefaultObject<UGameplayEffect>();
        for (const FGameplayModifierInfo& Modifier : GE->Modifiers)
        {
            if (Modifier.Attribute == UBaseAttributeSet::GetStaminaAttribute())
            {
                float Cost = 0.f;
                Modifier.ModifierMagnitude.GetStaticMagnitudeIfPossible(1.f, Cost);
                AttackStaminaCost = FMath::Abs(Cost);
            }
        }
    }
}

void UCombatStats::Tick(FStateTreeExecutionContext& Context, const float DeltaTime)
{
	Super::Tick(Context, DeltaTime);
    TagContainer = ASC->GetOwnedGameplayTags();
}

void UCombatStats::OnHealthChanged(const FOnAttributeChangeData& Data)
{
    Health = Data.NewValue;
}

void UCombatStats::OnStaminaChanged(const FOnAttributeChangeData& Data)
{
    Stamina = Data.NewValue;
}

void UCombatStats::OnStaggerChanged(const FOnAttributeChangeData& Data)
{
    Stagger = Data.NewValue;
}
