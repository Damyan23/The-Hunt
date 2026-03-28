// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapon/MeleeWeapon.h"
#include "GameplayAbilitySystem/BaseCharacter.h"
#include "GameplayAbilitySystem/BasicAttackAbility.h"

// Sets default values
AMeleeWeapon::AMeleeWeapon()
{
    PrimaryActorTick.bCanEverTick = true;

    // Explicitly set root first
    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
    SetRootComponent(WeaponMesh);

    Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollider"));
    Capsule->SetupAttachment(WeaponMesh, FName("Cylinder"));  // attach to the bone
    Capsule->SetGenerateOverlapEvents(true);
    Capsule->OnComponentBeginOverlap.AddDynamic(this, &AMeleeWeapon::OnSwordHit);

    DisableHitbox();
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
    UE_LOG(LogTemp, Warning, TEXT("Hitbox enabled"));
    Capsule->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AMeleeWeapon::DisableHitbox() const
{
    UE_LOG(LogTemp, Warning, TEXT("Hitbox disabled"));
    Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}


void AMeleeWeapon::OnSwordHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    const ABaseCharacter* Attacker = Cast<ABaseCharacter>(GetOwner());
    ABaseCharacter* Target = Cast<ABaseCharacter>(OtherActor);

    // Ignore if invalid, same actor, or target is not player controlled
    if (!Target || !Attacker || Target == Attacker) return;

    if (!Target->IsPlayerControlled() && !Attacker->IsPlayerControlled()) return; // only damage the player

    UAbilitySystemComponent* AttackerASC = Attacker->GetAbilitySystemComponent();
    if (!AttackerASC) return;

    UBasicAttackAbility* AttackAbility = nullptr;
    for (const FGameplayAbilitySpec& Spec : AttackerASC->GetActivatableAbilities())
    {
        AttackAbility = Cast<UBasicAttackAbility>(Spec.Ability);
        if (AttackAbility) break;
    }

    if (!AttackAbility || !AttackAbility->DamageEffect) return;
    UAbilitySystemComponent* TargetASC = Target->GetAbilitySystemComponent();
    if (!TargetASC) return;
    FGameplayEffectContextHandle Context = AttackerASC->MakeEffectContext();
    Context.AddSourceObject(Attacker);
    FGameplayEffectSpecHandle SpecDamage = AttackerASC->MakeOutgoingSpec(
        AttackAbility->DamageEffect, 1.f, Context);
    FGameplayEffectSpecHandle SpecStagger = AttackerASC->MakeOutgoingSpec(
        AttackAbility->StaggerEffect, 1.f, Context);
    AttackerASC->ApplyGameplayEffectSpecToTarget(*SpecDamage.Data.Get(), TargetASC);
    AttackerASC->ApplyGameplayEffectSpecToTarget(*SpecStagger.Data.Get(), TargetASC);
    DisableHitbox();
}