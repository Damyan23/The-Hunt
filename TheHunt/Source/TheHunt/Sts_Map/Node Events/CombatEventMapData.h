#pragma once

#include "CoreMinimal.h"
#include "MapEventData.h"
#include "CombatEventMapData.generated.h"

/**
 * 
 */
UCLASS()
class THEHUNT_API UCombatMapData : public UMapEventData
{
	GENERATED_BODY()
	
	virtual void OnEnter_Implementation(APlayerController* PC) override;
	virtual void OnComplete_Implementation(APlayerController* PC) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	TSoftObjectPtr<UWorld> CombatLevel;
};
