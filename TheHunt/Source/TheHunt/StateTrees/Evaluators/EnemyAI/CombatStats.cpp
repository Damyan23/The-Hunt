// Fill out your copyright notice in the Description page of Project Settings.


#include "StateTrees/Evaluators/EnemyAI/CombatStats.h"

void UCombatStats::TreeStart(FStateTreeExecutionContext& Context)
{
	Super::TreeStart(Context);

    if (Character) AbilitySystemComponent = Character->AbilitySystemComponent;

    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetHealthAttribute())
        .AddUObject(this, &UCombatStats::OnHealthChanged);
    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetStaminaAttribute())
        .AddUObject(this, &UCombatStats::OnStaminaChanged);
    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetStaggerAttribute())
        .AddUObject(this, &UCombatStats::OnStaggerChanged);

    const float MaxHealth = AbilitySystemComponent->GetNumericAttribute(UBaseAttributeSet::GetMaxHealthAttribute());
    const float MaxStamina = AbilitySystemComponent->GetNumericAttribute(UBaseAttributeSet::GetMaxStaminaAttribute());
    const float MaxStagger = AbilitySystemComponent->GetNumericAttribute(UBaseAttributeSet::GetMaxStaggerAttribute());

    HealthPercentage = MaxHealth > 0.f ? AbilitySystemComponent->GetNumericAttribute(UBaseAttributeSet::GetHealthAttribute()) / MaxHealth : 0.f;
    StaminaPercentage = MaxStamina > 0.f ? AbilitySystemComponent->GetNumericAttribute(UBaseAttributeSet::GetStaminaAttribute()) / MaxStamina : 0.f;
    StaggerPercentage = MaxStagger > 0.f ? AbilitySystemComponent->GetNumericAttribute(UBaseAttributeSet::GetStaggerAttribute()) / MaxStagger : 0.f;
    Stamina = AbilitySystemComponent->GetNumericAttribute(UBaseAttributeSet::GetStaminaAttribute());

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
    TagContainer = AbilitySystemComponent->GetOwnedGameplayTags();
}

void UCombatStats::OnHealthChanged(const FOnAttributeChangeData& Data)
{
    HealthPercentage = Data.NewValue / AbilitySystemComponent->GetNumericAttribute(UBaseAttributeSet::GetMaxHealthAttribute());
}

void UCombatStats::OnStaminaChanged(const FOnAttributeChangeData& Data)
{
    Stamina = Data.NewValue;
    StaminaPercentage = Data.NewValue / AbilitySystemComponent->GetNumericAttribute(UBaseAttributeSet::GetMaxStaminaAttribute());
}

void UCombatStats::OnStaggerChanged(const FOnAttributeChangeData& Data)
{
    StaggerPercentage = Data.NewValue / AbilitySystemComponent->GetNumericAttribute(UBaseAttributeSet::GetMaxStaggerAttribute());
}
