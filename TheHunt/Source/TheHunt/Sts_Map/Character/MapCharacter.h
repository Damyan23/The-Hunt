// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Sts_Map/MapManager.h"
#include "Sts_Map/Nodes/MapNode.h"
#include "GameFramework/Character.h"
#include "MapCharacter.generated.h"

UCLASS()
class THEHUNT_API AMapCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMapCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<AMapManager> Map;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<AMapNode> CurrentNode;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AMapNode* SelectedNode;

	UPROPERTY(BlueprintReadOnly)
	bool bIsMoving = false;

	UPROPERTY(EditAnywhere)
	float TravelSpeed = 2.f; // seconds to reach next node

	UFUNCTION(BlueprintCallable)
	void TravelToNode(AMapNode* TargetNode);

private:
	float TravelAlpha = 0.f;
	FVector TravelStart;
	FVector TravelEnd;
	AMapNode* PendingNode = nullptr;

	TObjectPtr<APlayerController> PC;
};
