// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

#include "EnemyAIController.h"

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

        Weapon->WeaponMesh->SetVisibility(false);
    }
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


		