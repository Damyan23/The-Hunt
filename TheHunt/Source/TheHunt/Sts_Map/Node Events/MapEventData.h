// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MapEventData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class THEHUNT_API UMapEventData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
    // --- Identity ---
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Event")
    FText Title;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Event")
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Event")
    UStaticMesh* NodeMesh;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Event")
    int32 NodeIndex;

    // --- Core trigger — override in child classes ---
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Event")
    void OnEnter(APlayerController* PC);

    // Called when the event is fully completed (combat won, shop closed, choice made)
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Event")
    void OnComplete(APlayerController* PC);
};
