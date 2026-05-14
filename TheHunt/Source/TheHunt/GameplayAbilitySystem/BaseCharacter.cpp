// Fill out your copyright notice in the Description page of Project Settings.
#include "BaseCharacter.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "InputPlayer/PlayerCharacter.h"
#include "Items/Weapon/MeleeWeapon.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
    BaseAttributes = CreateDefaultSubobject<UBaseAttributeSet>(TEXT("BaseAttributesSet"));
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
    Super::BeginPlay();

    FGameplayEffectContextHandle Context = AbilitySystemComponent->MakeEffectContext();
    FGameplayEffectSpecHandle Spec = AbilitySystemComponent->MakeOutgoingSpec(
        StaminaRegen, 1.f, Context);
    AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*Spec.Data.Get());

    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
        UBaseAttributeSet::GetHealthAttribute())
        .AddUObject(this, &ABaseCharacter::OnHealthChanged);

    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetStaggerAttribute()).AddUObject(this, &ABaseCharacter::OnStaggerChanged);
}


// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void ABaseCharacter::PostInitializeComponents()
{
    Super::PostInitializeComponents();
    AbilitySystemComponent->InitAbilityActorInfo(this, this);
    GrantDefaultAbilities();
    AttachWeapon();
}

void ABaseCharacter::InitializeAttributes()
{
}

void ABaseCharacter::GrantDefaultAbilities()
{
    if (!AbilitySystemComponent) return;

    for (TSubclassOf<UGameplayAbility>& Ability : DefaultAbilities)
    {
        if (Ability)
        {
            FGameplayAbilitySpec Spec = FGameplayAbilitySpec(Ability, 1);
            AbilitySystemComponent->GiveAbility(Spec);
        }
    }
}

void ABaseCharacter::AttachWeapon()
{
}   

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
    return AbilitySystemComponent;
}


void ABaseCharacter::Die()
{
}

void ABaseCharacter::OnHealthChanged(const FOnAttributeChangeData& Data)
{  
    if (IsDead) return;

    OnHealthUpdated(Data.NewValue, AbilitySystemComponent->GetNumericAttribute(
        UBaseAttributeSet::GetMaxHealthAttribute()));

    if (Data.NewValue <= 0.f)
    {
        IsDead = true;
        OnDeath();
        return;
    }   

    if (Data.NewValue < Data.OldValue) // took damage
    {
        bool bDamageFromActor = false;
        if (Data.GEModData != nullptr)
        {
            const FGameplayTagContainer& EffectTags = Data.GEModData->EffectSpec.Def->InheritableGameplayEffectTags.CombinedTags;
            if (EffectTags.HasTag(FGameplayTag::RequestGameplayTag("Damage.Direct")))
            {
                bDamageFromActor = true;
            }
        }

        if (GettingHitMontage && bDamageFromActor && HitVFX)
        {
            const UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
            UAnimMontage* CurrentMontage = AnimInstance->GetCurrentActiveMontage();
            FName CurrentSection = AnimInstance->Montage_GetCurrentSection(CurrentMontage);
            if (AnimInstance->Montage_GetCurrentSection(CurrentMontage) != FName("Non Cancelable"))
            {
                GetMesh()->GetAnimInstance()->Montage_Play(GettingHitMontage);
            }
        }

        APlayerCharacter* PC = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
        if (PC)
        {
            FGameplayTag AttackTag = FGameplayTag::RequestGameplayTag("State.Attacking");
            FGameplayCueParameters CueParams;
            CueParams.Location = GetActorLocation();

            if (IsPlayerControlled())
            {
                bool bEnemyIsAttacking = false;
                for (TActorIterator<ABaseCharacter> It(GetWorld()); It; ++It)
                {
                    ABaseCharacter* Character = *It;
                    if (Character && !Character->IsPlayerControlled())
                    {
                        if (Character->GetAbilitySystemComponent()->HasMatchingGameplayTag(AttackTag))
                        {
                            bEnemyIsAttacking = true;
                            break;
                        }
                    }
                }

                if (bEnemyIsAttacking)
                {
                    PC->AbilitySystemComponent->ExecuteGameplayCue(
                        FGameplayTag::RequestGameplayTag("GameplayCue.Hit.CameraShake"),
                        CueParams
                    );
                }
            }
            else
            {
                // Enemy got hit - only shake if player is attacking
                if (PC->AbilitySystemComponent->HasMatchingGameplayTag(AttackTag))
                {
                    PC->AbilitySystemComponent->ExecuteGameplayCue(
                        FGameplayTag::RequestGameplayTag("GameplayCue.Enemy.Hit.CameraShake"),
                        CueParams
                    );
                }
            }
        }
    }
}

void ABaseCharacter::OnDeath()
{
}

void ABaseCharacter::OnStaggerChanged(const FOnAttributeChangeData& Data)
{
    UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
    if (!AnimInstance) return;

    UAnimMontage* CurrentMontage = AnimInstance->GetCurrentActiveMontage();
    if (!CurrentMontage) return; // guard against null montage

    if (AnimInstance->Montage_GetCurrentSection(CurrentMontage) == FName("BlockHold"))
    {
        AnimInstance->Montage_JumpToSection(FName("BlockImpact"), CurrentMontage);
    }
}

void ABaseCharacter::OnGuardBroken()
{
    Weapon->DisableAttackHitbox();

    FGameplayTagContainer BlockTag;
    BlockTag.AddTag(FGameplayTag::RequestGameplayTag("Ability.Block"));
    AbilitySystemComponent->CancelAbilities(&BlockTag);

    AbilitySystemComponent->AddLooseGameplayTags(FGameplayTagContainer(FGameplayTag::RequestGameplayTag("State.Stunned")));

    if (StaggerMontage)
        GetMesh()->GetAnimInstance()->Montage_Play(StaggerMontage);

    FTimerHandle StunTimer;
    GetWorldTimerManager().SetTimer(StunTimer, [this]()
    {
        UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
        if (StaggerMontage && AnimInstance)
            AnimInstance->Montage_JumpToSection(FName("StaggerExit"), StaggerMontage);

        AbilitySystemComponent->RemoveLooseGameplayTags(FGameplayTagContainer(FGameplayTag::RequestGameplayTag("State.Stunned")));

        AbilitySystemComponent->ApplyGameplayEffectToSelf(
            StaggerResetEffect.GetDefaultObject(), 1.f,
            AbilitySystemComponent->MakeEffectContext());

    }, StunDuration, false);
}

