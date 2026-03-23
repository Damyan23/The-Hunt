#pragma once
#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "Engine/DataAsset.h"
#include "Engine/Texture2D.h"
#include "ItemDefinition.generated.h"

UCLASS(BlueprintType)
class THEHUNT_API UItemDefinition : public UPrimaryDataAsset
{
    GENERATED_BODY()
public:
    UItemDefinition();

    UPROPERTY(EditDefaultsOnly, Category = "Item")
    FName ItemID;

    UPROPERTY(EditDefaultsOnly, Category = "Item")
    TSoftObjectPtr<UTexture2D> ItemIcon;

    UPROPERTY(EditDefaultsOnly, Category = "Combat")
    TSubclassOf<UGameplayEffect> DamageEffect;

    UPROPERTY(EditDefaultsOnly, Category = "Item")
    TSoftClassPtr<AActor> PickupClass;
};