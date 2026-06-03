// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "InputPlayer/PlayerCharacter.h"

UBaseAttributeSet::UBaseAttributeSet()
{
	Health = 100.0f;
	MaxHealth = 100.0f;
	Stamina = 100.0f;
	MaxStamina = 100.0f;
	Stagger = 0.0f;
	MaxStagger = 30.0f;
}

void UBaseAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

    if (Data.EvaluatedData.Attribute == GetHealthAttribute())
    {
        // Clamp Health between 0 and MaxHealth
        float CurrentMaxHealth = GetMaxHealth();
        SetHealth(FMath::Clamp(GetHealth(), 0.0f, CurrentMaxHealth));
    }

    if (Data.EvaluatedData.Attribute == GetMaxHealthAttribute())
    {
        // If MaxHealth was reduced, clamp Health down to new MaxHealth
        float CurrentHealth = GetHealth();
        float NewMaxHealth = GetMaxHealth();
        SetHealth(FMath::Clamp(CurrentHealth, 0.0f, NewMaxHealth));
    }

    if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
    {
        // Clamp stamina to max
        float NewStamina = FMath::Clamp(GetStamina(), 0.f, GetMaxStamina());
        SetStamina(NewStamina);
    }
}

bool UBaseAttributeSet::PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data)
{
    if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
    {
        if (GetStamina() >= GetMaxStamina() && Data.EvaluatedData.Magnitude > 0.f)
            return false;

        // Block regen if delay is active
        APlayerCharacter* Player = Cast<APlayerCharacter>(GetOwningActor());
        if (Player && !Player->bStaminaRegenAllowed && Data.EvaluatedData.Magnitude > 0.f)
            return false;
    }
    return true;
}

