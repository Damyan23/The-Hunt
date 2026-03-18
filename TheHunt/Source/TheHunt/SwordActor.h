// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Actor.h"
#include "SwordActor.generated.h"

UCLASS()
class THEHUNT_API ASwordActor : public AActor
{
    GENERATED_BODY()
public:
    ASwordActor();

    void EnableHitbox();
    void DisableHitbox();

    UPROPERTY(EditDefaultsOnly, Category = "Combat")
    TSubclassOf<UGameplayEffect> DamageEffect;

private:
    UPROPERTY(VisibleAnywhere)
    TObjectPtr<UCapsuleComponent> HitboxComponent;

    UFUNCTION()
    void OnSwordHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
        bool bFromSweep, const FHitResult& SweepResult);
};
