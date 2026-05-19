// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapon/MeleeWeapon.h"
#include "GameplayAbilitySystem/BaseCharacter.h"
#include "GameplayAbilitySystem/BasicAttackAbility.h"
#include "Items/ItemDefinition.h"
#include "Items/RuneBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMeleeWeapon::AMeleeWeapon()
{
    PrimaryActorTick.bCanEverTick = true;

    // Explicitly set root first
    ItemMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
    SetRootComponent(ItemMesh);

    Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollider"));
    Capsule->SetupAttachment(ItemMesh, FName("Cylinder"));
    Capsule->SetGenerateOverlapEvents(true);
    Capsule->SetMobility(EComponentMobility::Movable);
    Capsule->OnComponentBeginOverlap.AddDynamic(this, &AMeleeWeapon::OnSwordHit);

    Runes.SetNum(3);
}

// Called when the game starts or when spawned
void AMeleeWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AMeleeWeapon::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);
}

void AMeleeWeapon::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    if (Runes.IsEmpty())
    {
        // Only fill if blueprint didn't set any
        Runes.Add(NewObject<URuneBase>(this));
        Runes.Add(NewObject<URuneBase>(this));
        Runes.Add(NewObject<URuneBase>(this));
    }
}

// Called every frame
void AMeleeWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (TimeStopEndTime > 0.f &&
        GetWorld()->GetRealTimeSeconds() >= TimeStopEndTime)
    {
        RestoreGlobalTimeDilation();
        TimeStopEndTime = 0.f;
        SetActorTickEnabled(false);
    }
}

void AMeleeWeapon::EnableAttackHitbox() const
{
    UE_LOG(LogTemp, Warning, TEXT("Hitbox enabled"));
    Capsule->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AMeleeWeapon::DisableAttackHitbox() const
{
    UE_LOG(LogTemp, Warning, TEXT("Hitbox disabled"));
    Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AMeleeWeapon::OnSwordHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    if (!OtherActor) return;



    ABaseCharacter* Attacker = Cast<ABaseCharacter>(GetOwner());
    ABaseCharacter* Target = Cast<ABaseCharacter>(OtherActor);

    if (!Target || !Attacker || Target == Attacker) return;
    if (!Target->IsPlayerControlled() && !Attacker->IsPlayerControlled()) return;

    FVector SpawnLocation = OtherComp ? OtherComp->GetComponentLocation() : Target->GetActorLocation();

    // Try to get exact impact point with a trace
    FHitResult TraceHit;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);
    Params.AddIgnoredActor(Attacker);

    bool bHit = GetWorld()->SweepSingleByChannel(
        TraceHit,
        Capsule->GetComponentLocation(),
        OtherComp->GetComponentLocation(),
        Capsule->GetComponentQuat(),
        ECC_Pawn,
        FCollisionShape::MakeCapsule(
            Capsule->GetScaledCapsuleRadius(),
            Capsule->GetScaledCapsuleHalfHeight()
        ),
        Params
    );

    if (bHit)
    {
        SpawnLocation = TraceHit.ImpactPoint;
    }

    UAbilitySystemComponent* AttackerASC = Attacker->GetAbilitySystemComponent();
    UAbilitySystemComponent* TargetASC = Target->GetAbilitySystemComponent();

    if (!AttackerASC || !TargetASC) return;

    // Get attack ability early since we need it in multiple places
    UBasicAttackAbility* AttackAbility = nullptr;
    for (const FGameplayAbilitySpec& Spec : AttackerASC->GetActivatableAbilities())
    {
        AttackAbility = Cast<UBasicAttackAbility>(Spec.Ability);
        if (AttackAbility) break;
    }

    /*
     * ==========================
     * BLOCK / PARRY CHECK
     * ==========================
     */
    if (TargetASC->HasMatchingGameplayTag(
        FGameplayTag::RequestGameplayTag("State.Blocking")))
    {
        FCombatSoundData WeaponSoundData = Target->Weapon->ItemDefinition->WeaponData.SoundData;

        // Perfect parry check
        if (TargetASC->HasMatchingGameplayTag(
            FGameplayTag::RequestGameplayTag("State.Parrying")))
        {
            if (AttackerASC->HasMatchingGameplayTag(
                FGameplayTag::RequestGameplayTag("State.Parryable")))
            {
                UE_LOG(LogTemp, Warning, TEXT("PARRY SUCCESS"));
                AttackerASC->AddLooseGameplayTag(
                    FGameplayTag::RequestGameplayTag("State.Staggered"));


                UGameplayStatics::PlaySoundAtLocation(this, WeaponSoundData.ParrySound, GetActorLocation());

                // Parry VFX
                if (Target->ParryVFX)
                {
                    FGameplayCueParameters CueParams;
                    CueParams.Location = SpawnLocation;
                    CueParams.SourceObject = TWeakObjectPtr<UObject>(Target->ParryVFX);
                    CueParams.RawMagnitude = 20.f;
                    TargetASC->ExecuteGameplayCue(
                        FGameplayTag::RequestGameplayTag("GameplayCue.Hit.Impact"),
                        CueParams
                    );

                    UE_LOG(LogTemp, Warning, TEXT("SweepResult.ImpactPoint: %s"), *SweepResult.ImpactPoint.ToString());
                    UE_LOG(LogTemp, Warning, TEXT("bFromSweep: %s"), bFromSweep ? TEXT("true") : TEXT("false"));
                }

                DisableAttackHitbox();
                return;
            }
        }

        UGameplayStatics::PlaySoundAtLocation(this, WeaponSoundData.BlockSound, GetActorLocation());

        // Apply stagger to blocker even though damage is blocked
        if (AttackAbility && AttackAbility->StaggerEffect)
        {
            FGameplayEffectContextHandle Context = AttackerASC->MakeEffectContext();
            Context.AddSourceObject(Attacker);
            FGameplayEffectSpecHandle SpecStagger = AttackerASC->MakeOutgoingSpec(
                AttackAbility->StaggerEffect, 1.f, Context);
            AttackerASC->ApplyGameplayEffectSpecToTarget(*SpecStagger.Data.Get(), TargetASC);
        }

        // Block VFX
        if (Target->BlockVFX)
        {
            FGameplayCueParameters CueParams;
            CueParams.Location = SpawnLocation;
            CueParams.SourceObject = TWeakObjectPtr<UObject>(Target->BlockVFX);
            CueParams.RawMagnitude = 20.f;
            TargetASC->ExecuteGameplayCue(
                FGameplayTag::RequestGameplayTag("GameplayCue.Hit.Impact"),
                CueParams
            );
        }

        DisableAttackHitbox();
        return;
    }

    /*
     * ==========================
     * RUNES ONHIT
     * ==========================
     */
    if (Runes.Num() > 0)
    {
        for (int i = 0; i < Runes.Num(); i++)
        {
            if (!Runes[i]) continue;
            if (AttackerASC->HasMatchingGameplayTag(
                FGameplayTag::RequestGameplayTag("State.Attacking")))
            {
                Runes[i]->OnHit(Attacker, Target, 0);
            }
        }
    }

    /*
     * ==========================
     * NORMAL DAMAGE
     * ==========================
     */
    if (!AttackAbility || !AttackAbility->DamageEffect) return;

    FGameplayEffectContextHandle Context = AttackerASC->MakeEffectContext();
    Context.AddSourceObject(Attacker);

    FGameplayEffectSpecHandle SpecDamage = AttackerASC->MakeOutgoingSpec(
        AttackAbility->DamageEffect, 1.f, Context);

    FGameplayEffectSpecHandle SpecStagger = AttackerASC->MakeOutgoingSpec(
        AttackAbility->StaggerEffect, 1.f, Context);

    AttackerASC->ApplyGameplayEffectSpecToTarget(*SpecDamage.Data.Get(), TargetASC);
    AttackerASC->ApplyGameplayEffectSpecToTarget(*SpecStagger.Data.Get(), TargetASC);

    // Spawn hit VFX from target
    if (Target->HitVFX)
    {
        FGameplayCueParameters CueParams;
        CueParams.Location = SpawnLocation;
        CueParams.SourceObject = TWeakObjectPtr<UObject>(Target->HitVFX);
        CueParams.RawMagnitude = 20.f;
        TargetASC->ExecuteGameplayCue(
            FGameplayTag::RequestGameplayTag("GameplayCue.Hit.Impact"),
            CueParams
        );
    }
    
    if (Target)
    {
        FVector KnockbackDirection = Target->GetActorLocation() - Attacker->GetActorLocation();
        KnockbackDirection.Z = 0.f;
        KnockbackDirection.Normalize();
        Target->LaunchCharacter(KnockbackDirection * KnockbackForce, true, false);
    }

    DisableAttackHitbox();
}

void AMeleeWeapon::OnSwordBlocked(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{

}

bool AMeleeWeapon::EquipRune(URuneBase* Rune)
{
    if (!Rune) return false;

    // Find first empty rune slot (null entry)
    for (int32 i = 0; i < Runes.Num(); i++)
    {
        if (!Runes[i])
        {
            Runes[i] = Rune;
            UE_LOG(LogTemp, Warning, TEXT("Rune equipped to slot %d"), i);
            return true;
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("No empty rune slots available"));
    return false;
}

void AMeleeWeapon::ApplyTimeStop(float Duration, float TimeDilation)
{
    if (!GetWorld()) return;

    PreviousGlobalTimeDilation = UGameplayStatics::GetGlobalTimeDilation(GetWorld());

    const float EffectiveDilation = FMath::Max(TimeDilation, 0.001f);

    UGameplayStatics::SetGlobalTimeDilation(GetWorld(), EffectiveDilation);

    TimeStopEndTime = GetWorld()->GetRealTimeSeconds() + Duration;

    SetActorTickEnabled(true);
}

void AMeleeWeapon::RestoreGlobalTimeDilation()
{
    if (!GetWorld()) return;

    UGameplayStatics::SetGlobalTimeDilation(GetWorld(), PreviousGlobalTimeDilation);

    // Clear the handle
    GetWorld()->GetTimerManager().ClearTimer(TimeStopTimerHandle);
}
