// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapon/MeleeWeapon.h"
#include "GameplayAbilitySystem/BaseCharacter.h"

// Sets default values
AMeleeWeapon::AMeleeWeapon()
{
    PrimaryActorTick.bCanEverTick = true;

    // Explicitly set root first
    WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
    SetRootComponent(WeaponMesh);
    WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    WeaponMesh->OnComponentBeginOverlap.AddDynamic(this, &AMeleeWeapon::OnSwordHit);
}

// Called when the game starts or when spawned
void AMeleeWeapon::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMeleeWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMeleeWeapon::EnableHitbox() const
{
    WeaponMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AMeleeWeapon::DisableHitbox() const
{
    WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AMeleeWeapon::OnSwordHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    const ABaseCharacter* Attacker = Cast<ABaseCharacter>(GetOwner());
    const ABaseCharacter* Target = Cast<ABaseCharacter>(OtherActor);
    if (!Target || !Attacker || Target == Attacker) return;

    if (!ItemDefinition || !ItemDefinition->DamageEffect) return;

    UAbilitySystemComponent* TargetASC = Target->GetAbilitySystemComponent();
    UAbilitySystemComponent* AttackerASC = Attacker->GetAbilitySystemComponent();

    if (TargetASC && AttackerASC)
    {
        FGameplayEffectContextHandle Context = AttackerASC->MakeEffectContext();
        Context.AddSourceObject(Attacker);
        FGameplayEffectSpecHandle Spec = AttackerASC->MakeOutgoingSpec(
            ItemDefinition->DamageEffect, 1.f, Context);
        AttackerASC->ApplyGameplayEffectSpecToTarget(*Spec.Data.Get(), TargetASC);
    }

    DisableHitbox();
}