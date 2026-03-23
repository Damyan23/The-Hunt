// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Actor.h"
#include "TheHunt/Items/ItemDefinition.h"
#include "MeleeWeapon.generated.h"

UCLASS()
class THEHUNT_API AMeleeWeapon : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AMeleeWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

public:	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> WeaponMesh;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = "Item")
	TObjectPtr<UItemDefinition> ItemDefinition;;

	void EnableHitbox() const;
	void DisableHitbox() const;	

	UFUNCTION()
	void OnSwordHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly, Category = "Attachment")
	FTransform AttachOffset;


	UPROPERTY(EditDefaultsOnly, Category = "Attachment")
	FName AttachSocketName = "Hand_R_Socket";
};
