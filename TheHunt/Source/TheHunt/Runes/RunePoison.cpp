// Fill out your copyright notice in the Description page of Project Settings.


#include "Runes/RunePoison.h"

void URunePoison::OnHit(ABaseCharacter* Attacker, ABaseCharacter* Target, int8 HitCount)
{
	Super::OnHit(Attacker, Target, HitCount);
    UE_LOG(LogTemp, Warning, TEXT("RunePoison OnHit: Attacker=%s Target=%s"),
        Attacker ? *Attacker->GetName() : TEXT("NULL"),
        Target ? *Target->GetName() : TEXT("NULL"));

    if (!Target)
    {
        UE_LOG(LogTemp, Warning, TEXT("  Target NULL — bailing"));
        return;
    }

    UAbilitySystemComponent* TargetASC = Target->GetAbilitySystemComponent();
    if (!TargetASC) { UE_LOG(LogTemp, Warning, TEXT("  No TargetASC")); return; }

    if (!PoisonEffect) { UE_LOG(LogTemp, Warning, TEXT("  PoisonEffect is NULL!")); return; }

    FGameplayEffectContextHandle Ctx = TargetASC->MakeEffectContext();
    FGameplayEffectSpecHandle Spec = TargetASC->MakeOutgoingSpec(PoisonEffect, 1.f, Ctx);
    if (Spec.IsValid())
    {
        TargetASC->ApplyGameplayEffectSpecToSelf(*Spec.Data.Get());
        UE_LOG(LogTemp, Warning, TEXT("  Poison effect applied"));
    }
    else
        UE_LOG(LogTemp, Warning, TEXT("  Spec invalid"));


    // Apply poison GE to target using attacker's ASC
    UAbilitySystemComponent* AttackerASC = Attacker->GetAbilitySystemComponent();

    if (!AttackerASC || !TargetASC) return;

    AttackerASC->ApplyGameplayEffectSpecToTarget(*Spec.Data.Get(), TargetASC);
}
