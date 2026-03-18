// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordActor.h"

#include "GameplayAbilitySystem/BaseCharacter.h"

// Sets default values
ASwordActor::ASwordActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    HitboxComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Hitbox"));
    SetRootComponent(HitboxComponent);
    HitboxComponent->OnComponentBeginOverlap.AddDynamic(this, &ASwordActor::OnSwordHit);
    DisableHitbox();
}


void ASwordActor::OnSwordHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    ABaseCharacter* Attacker = Cast<ABaseCharacter>(GetOwner());
    ABaseCharacter* Target = Cast<ABaseCharacter>(OtherActor);

    if (!Target || !Attacker || Target == Attacker) return;

    UAbilitySystemComponent* TargetASC = Target->GetAbilitySystemComponent();
    UAbilitySystemComponent* AttackerASC = Attacker->GetAbilitySystemComponent();

    if (TargetASC && AttackerASC && DamageEffect)
    {
        FGameplayEffectContextHandle Context = AttackerASC->MakeEffectContext();
        Context.AddSourceObject(Attacker);

        FGameplayEffectSpecHandle Spec = AttackerASC->MakeOutgoingSpec(
            DamageEffect, 1.f, Context);

        AttackerASC->ApplyGameplayEffectSpecToTarget(*Spec.Data.Get(), TargetASC);
    }

    DisableHitbox(); // only hit once per swing
}

void ASwordActor::EnableHitbox()
{
    HitboxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void ASwordActor::DisableHitbox()
{
    HitboxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

