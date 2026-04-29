
#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/AssetManager.h"
#include "Items/ItemDefinition.h"
#include "ItemFunctionLibrary.generated.h"

UCLASS()
class THEHUNT_API UItemFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category = "Items")
    static UItemDefinition* FindItemById(FString ItemID)
    {
        UAssetManager& Manager = UAssetManager::Get();

        TArray<FAssetData> Assets;
        Manager.GetPrimaryAssetDataList(FPrimaryAssetType("ItemDefinition"), Assets);

        UE_LOG(LogTemp, Warning, TEXT("Assets found: %d"), Assets.Num());

        for (const FAssetData& Asset : Assets)
        {
            UItemDefinition* ItemDef = Cast<UItemDefinition>(Asset.GetAsset());
            if (ItemDef && ItemDef->ItemID == ItemID)
            {
                return ItemDef;
            }
        }

        UE_LOG(LogTemp, Warning, TEXT("FindItemById: No item found with id %s"), *ItemID);
        return nullptr;
    }
};