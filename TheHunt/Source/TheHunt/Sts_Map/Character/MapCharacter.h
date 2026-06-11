// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TheHuntGameInstance.h"
#include "Sts_Map/MapManager.h"
#include "Sts_Map/Nodes/MapNode.h"
#include "GameFramework/Character.h"
#include "MapCharacter.generated.h"

UCLASS()
class THEHUNT_API AMapCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AMapCharacter();


	//============================================================
	//  LIFECYCLE
	//============================================================
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;


	//============================================================
	//  Initialization / Setup
	//============================================================
protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void SetupMovement();
	void FindMapManager();
	bool LoadSaveData();
	void PlaceOnCurrentNode();


	//============================================================
	//  ABILITY SYSTEM
	//============================================================
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<UBaseAttributeSet> BaseAttributes;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;


	//============================================================
	//  MAP REFERENCES
	//============================================================
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<AMapManager> Map;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<AMapNode> CurrentNode;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AMapNode* SelectedNode;


	//============================================================
	//  NODE TRAVEL
	//============================================================
public:
	UPROPERTY(BlueprintReadOnly)
	bool bIsMoving = false;

	UPROPERTY(EditAnywhere)
	float TravelSpeed = 2.f; // seconds to reach next node

	UFUNCTION(BlueprintCallable)
	void TravelToNode(AMapNode* TargetNode);


	//============================================================
	//  INTERNAL TRAVEL STATE
	//============================================================
private:
	float TravelAlpha = 0.f;
	FVector TravelStart;
	FVector TravelEnd;

	UPROPERTY()
	TObjectPtr<AMapNode> PendingNode = nullptr;


	//============================================================
	//  CASHED REFERENCES
	//============================================================
private:
	UPROPERTY()
	TObjectPtr<APlayerController> PC;

	UPROPERTY()
	TObjectPtr<UTheHuntGameInstance> GI;
};