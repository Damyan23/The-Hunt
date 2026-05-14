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

    virtual FPrimaryAssetId GetPrimaryAssetId() const override
    {
        return FPrimaryAssetId("ItemDefinition", GetFName());
    }

    // -------------------------
    // GENERAL DATA
    // -------------------------
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
    FString ItemID;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
    EItemType ItemType = EItemType::Weapon;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
    FName ItemName;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
    FText ItemDescription;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
    TObjectPtr<UTexture2D> ItemIcon;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
    int CurrentQuantity;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item",
        meta = (EditCondition = "ItemType != EItemType::Rune", EditConditionHides))
    TSubclassOf<AInteractable> ItemClass;
    // -------------------------
    // WEAPON DATA
    // -------------------------
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon",
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


    UFUNCTION(BlueprintCallable)
    TSubclassOf<AMeleeWeapon> GetWeaponClass() const;


    UFUNCTION(BlueprintCallable, Category = "Rune")
    URuneBase* GetRune() const { return RuneData.Rune; }    
};