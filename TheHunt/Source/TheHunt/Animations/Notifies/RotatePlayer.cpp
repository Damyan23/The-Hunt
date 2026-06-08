// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/Notifies/RotatePlayer.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "InputPlayer/PlayerCharacter.h"

void URotatePlayer::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
    float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
    Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
    if (!MeshComp) return;
    APlayerCharacter* Player = Cast<APlayerCharacter>(MeshComp->GetOwner());
    if (!Player) return;

    FRotator DesiredRotation;

    // If locked on, dodge relative to the target in clean cardinal directions
    if (Player->IsLockedOn() && Player->GetLockOnTarget())
    {
        // Raw input, normalized
        FVector Input = Player->GetCharacterMovement()->GetLastInputVector();
        if (Input.IsNearlyZero())
        {
            // No input -> dodge backward away from target
            FVector ToTarget = Player->GetLockOnTarget()->GetActorLocation() - Player->GetActorLocation();
            ToTarget.Z = 0.f;
            DesiredRotation = (-ToTarget).Rotation();
        }
        else
        {
            Input.Z = 0.f;
            Input.Normalize();

            // Build target-relative axes
            FVector ToTarget = Player->GetLockOnTarget()->GetActorLocation() - Player->GetActorLocation();
            ToTarget.Z = 0.f;
            ToTarget.Normalize();
            FVector RightOfTarget = FVector::CrossProduct(FVector::UpVector, ToTarget);

            // Project input onto the two axes
            float fwd = FVector::DotProduct(Input, ToTarget);   // toward/away
            float right = FVector::DotProduct(Input, RightOfTarget); // strafe

            // Pick the dominant axis -> clean cardinal dodge
            FVector DodgeDir;
            if (FMath::Abs(right) > FMath::Abs(fwd))
                DodgeDir = (right > 0.f) ? RightOfTarget : -RightOfTarget;
            else
                DodgeDir = (fwd > 0.f) ? ToTarget : -ToTarget;

            DesiredRotation = DodgeDir.Rotation();
        }
    }
    else
    {
        // Not locked on -> dodge in raw input direction (free roam)
        FVector Input = Player->GetCharacterMovement()->GetLastInputVector();
        if (Input.IsNearlyZero()) return;
        DesiredRotation = Input.Rotation();
    }

    DesiredRotation.Pitch = 0.f;
    DesiredRotation.Roll = 0.f;

    FRotator NewRotation = FMath::RInterpConstantTo(
        Player->GetActorRotation(), DesiredRotation, FrameDeltaTime, InterpSpeed);
    Player->SetActorRotation(NewRotation);
}