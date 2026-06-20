#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "Components/AudioComponent.h"
#include "GameFramework/Actor.h"
#include "ExitPortal.generated.h"

class USphereComponent;

UCLASS()
class THEHUNT_API AExitPortal : public AActor
{
	GENERATED_BODY()

public:
	AExitPortal();


protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* Trigger;

	UPROPERTY(EditAnywhere, Category = "Portal")
	FName LevelToLoad = "Lvl_Map";

	UPROPERTY(EditAnywhere, Category = "Portal")
	float TravelDelay = 2.0f;

	FTimerHandle TravelTimer;

	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	void TriggerLevelLoad();

	bool bTriggered = false;

	UPROPERTY(VisibleAnywhere, Category = "Portal")
	UWidgetComponent* ChargeWidgetComp = nullptr;

	UPROPERTY(EditAnywhere, Category = "Portal")
	TSubclassOf<UUserWidget> ChargeWidgetClass = nullptr;

	UPROPERTY()
	UUserWidget* ChargeWidget = nullptr;

	float ChargeElapsed = 0.f;
	bool bCharging = false;

	void TickCharge(float DeltaTime);

	UPROPERTY(EditAnywhere, Category = "Portal")
	float DrainRate = 1.f;   // multiplier — how fast it drains vs fills (1 = same speed)

	UPROPERTY(EditAnywhere, Category = "Portal")
	USoundBase* ChargeSound = nullptr;   // looping hum while charging

	UPROPERTY()
	UAudioComponent* ChargeAudio = nullptr;

	bool bPlayerOnPad = false;

	void OnOverlapEnd(
		UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};