// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

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

		