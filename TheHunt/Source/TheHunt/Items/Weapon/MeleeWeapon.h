// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "Items/Interactable.h"
#include "MeleeWeapon.generated.h"

class URuneBase;
class USkeletalMeshComponent;
class UCapsuleComponent;

UCLASS()
class THEHUNT_API AMeleeWeapon : public AInteractable
{
	GENERATED_BODY()


public:	
	// Sets default values for this actor's properties
	AMeleeWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	void EnableAttackHitbox() const;
	void DisableAttackHitbox() const;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UCapsuleComponent> Capsule;
	
	UFUNCTION()
	void OnSwordHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnSwordBlocked(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly, Category = "Attachment")
	FTransform AttachOffset;

	UPROPERTY(EditDefaultsOnly, Category = "Attachment")
	FName AttachSocketName = "Hand_R_Socket";

	UFUNCTION(BlueprintCallable, Category = "Runes")
	bool EquipRune(URuneBase* Rune);

	UPROPERTY(EditDefaultsOnly, Instanced, Category = "Runes")
	TArray<TObjectPtr<URuneBase>> Runes;

	UFUNCTION(BlueprintCallable, Category = "Time")
	void ApplyTimeStop(float Duration = 0.5f, float TimeDilation = 0.0f);

protected:
	UFUNCTION()
	void RestoreGlobalTimeDilation();

private:
	FTimerHandle TimeStopTimerHandle;
	float PreviousGlobalTimeDilation = 1.0f;
	float TimeStopEndTime = 0.f;
};
