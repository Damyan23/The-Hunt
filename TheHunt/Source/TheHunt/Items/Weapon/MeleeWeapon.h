// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Actor.h"
#include "MeleeWeapon.generated.h"

class UItemDefinition;
class URuneBase;
class USkeletalMeshComponent;
class UCapsuleComponent;

UCLASS()
class THEHUNT_API AMeleeWeapon : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AMeleeWeapon();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UCapsuleComponent> Capsule;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = "Item")
	TObjectPtr<UItemDefinition> ItemDefinition;

	
	void EnableAttackHitbox() const;
	void DisableAttackHitbox() const;	

	
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

	UPROPERTY(EditDefaultsOnly, Category = "Runes")
	TArray<TObjectPtr<URuneBase>> Runes;

	// Time-stop helpers
public:
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
