// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Interactable.h"
#include "ExitPortal.generated.h"

/**
 * 
 */
UCLASS()
class THEHUNT_API AExitPortal : public AInteractable
{
	GENERATED_BODY()

protected:
	virtual void OnInteract_Implementation(AActor* Interactor) override;
};
