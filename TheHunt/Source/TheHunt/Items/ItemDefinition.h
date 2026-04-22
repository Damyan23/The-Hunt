#pragma once
#include "CoreMinimal.h"
#include "ItemType.h"
#include "Engine/DataAsset.h"
#include "Engine/Texture2D.h"
#include "ItemDef_Enums/ConsumableData.h"
#include "ItemDef_Enums/RuneData.h"
#include "ItemDef_Enums/WeaponData.h"
#include "ItemDefinition.generated.h"

class AMeleeWeapon;
class URuneBase;
class UTexture2D;

UCLASS(BlueprintType)
class THEHUNT_API UItemDefinition : public UPrimaryDataAsset
{
    GENERATED_BODY()
public:
    UItemDefinition();

    // -------------------------
    // GENERAL DATA
    // -------------------------
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
    EItemType ItemType = EItemType::Weapon;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
    FName ItemName;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
    FText ItemDescription;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
    TSoftObjectPtr<UTexture2D> ItemIcon;

    // -------------------------
    // WEAPON DATA
    // -------------------------
    UPROPERTY(EditDefaultsOnly, Category = "Weapon",
        meta = (EditCondition = "ItemType == EItemType::Weapon", EditConditionHides))
    FWeaponData WeaponData;

    // -------------------------
    // CONSUMABLE DATA
    // -------------------------
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Consumable",
        meta = (EditCondition = "ItemType == EItemType::Consumable", EditConditionHides))
    FConsumableData ConsumableData;

    // -------------------------
    // RUNE DATA
    // -------------------------
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Rune",
        meta = (EditCondition = "ItemType == EItemType::Rune", EditConditionHides))
    FRuneData RuneData;

    // -------------------------
    // INVENTORY DATA
    // -------------------------
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory",
        meta = (EditCondition = "ItemType != EItemType::Weapon", EditConditionHides))
    bool bIsStackable = false;
};