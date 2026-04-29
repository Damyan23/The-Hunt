// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapMaker.generated.h"

UCLASS()
class THEHUNT_API AMapMaker : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMapMaker();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Header
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	FVector2D BoardSize = FVector2D(1000.f, 1000.f);

	UPROPERTY(EditAnywhere)
	float MinDist = 50.f;

	UPROPERTY(EditAnywhere)
	float SamplesBeforeRejection = 30.f;
};
