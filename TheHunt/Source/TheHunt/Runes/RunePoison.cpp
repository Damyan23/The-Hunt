// Fill out your copyright notice in the Description page of Project Settings.


#include "Runes/RunePoison.h"

void URunePoison::OnHit(ABaseCharacter* Attacker, ABaseCharacter* Target, int8 HitCount)
{
	Super::OnHit(Attacker, Target, HitCount);

    // Apply poison GE to target using attacker's ASC
    UAbilitySystemComponent* AttackerASC = Attacker->GetAbilitySystemComponent();
    UAbilitySystemComponent* TargetASC = Target->GetAbilitySystemComponent();
    if (!AttackerASC || !TargetASC) return;

    UE_LOG (LogTemp, Warning, TEXT("Kurr"));

    FGameplayEffectSpecHandle Spec = AttackerASC->MakeOutgoingSpec(
        PoisonEffect, 1.f, AttackerASC->MakeEffectContext());
    AttackerASC->ApplyGameplayEffectSpecToTarget(*Spec.Data.Get(), TargetASC);
}
