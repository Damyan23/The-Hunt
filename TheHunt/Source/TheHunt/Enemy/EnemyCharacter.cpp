// Fill out your copyright notice in the Description page of Project Settings.
#include "EnemyCharacter.h"

#include "EnemyAIController.h"
#include "Components/CapsuleComponent.h"
#include "Items/Weapon/MeleeWeapon.h"

AEnemyCharacter::AEnemyCharacter()
{

}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;

    Weapon = GetWorld()->SpawnActor<AMeleeWeapon>(WeaponClass, FTransform::Identity, SpawnParams);

    if (Weapon)
    {
        Weapon->AttachToComponent(GetMesh(),
            FAttachmentTransformRules::SnapToTargetNotIncludingScale,
                FName("Sword_joint"));

        Weapon->SetActorRelativeRotation(Weapon->AttachOffset.Rotator());
        Weapon->ItemMesh->SetVisibility(false);
    }

    float CurrentHealth = AbilitySystemComponent->GetNumericAttribute(
        UBaseAttributeSet::GetHealthAttribute());
    float MaxHealth = AbilitySystemComponent->GetNumericAttribute(
        UBaseAttributeSet::GetMaxHealthAttribute());
    OnHealthUpdated(CurrentHealth, MaxHealth);
}

void AEnemyCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

  
}

void AEnemyCharacter::OnDeath()
{
    Super::OnDeath();

    if (AEnemyAIController* AIController = Cast<AEnemyAIController>(GetController()))
        AIController->StopMovement();

    GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    AbilitySystemComponent->CancelAllAbilities();

    if (DeathMontage)
    {
        UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
        float Duration = AnimInstance->Montage_Play(DeathMontage);

        FTimerHandle DestroyTimer;
        GetWorldTimerManager().SetTimer(DestroyTimer, [this]()
            {
                Destroy();
            }, Duration + FreezeAfterDeathDuration, false);

        DetachFromControllerPendingDestroy();
    }
    else
    {
        Destroy();
    }
}

void AEnemyCharacter::OpenParryWindow()
{
    AbilitySystemComponent->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("State.Parryable")));
}

void AEnemyCharacter::CloseParryWindow()
{
    AbilitySystemComponent->RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("State.Parryable")));
}

bool AEnemyCharacter::SetStagger()
{
    float CurrentStagger = AbilitySystemComponent->GetNumericAttribute(UBaseAttributeSet::GetStaggerAttribute());
    float MaxStagger = AbilitySystemComponent->GetNumericAttribute(UBaseAttributeSet::GetMaxStaggerAttribute());

    if (CurrentStagger >= MaxStagger)
    {
        UE_LOG(LogTemp, Warning, TEXT("sDADASDAS"));
        AbilitySystemComponent->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("State.Staggered")));
        return true;
    }

    return false;
}

