#pragma once
#include "CoreMinimal.h"
#include "RuneData.generated.h"

class URuneBase;

USTRUCT(BlueprintType)
struct FRuneData
{
    GENERATED_BODY()
public:
    UPROPERTY(EditDefaultsOnly, Instanced, Category = "Rune")
    TObjectPtr<URuneBase> Rune;
};