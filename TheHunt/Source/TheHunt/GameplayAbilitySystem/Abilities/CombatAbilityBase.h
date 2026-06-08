#pragma once
#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "CombatAbilityBase.generated.h"

UCLASS()
class THEHUNT_API UCombatAbilityBase : public UGameplayAbility
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, Category = "Attack")
    TSubclassOf<UGameplayEffect> DamageEffect;

    UPROPERTY(EditDefaultsOnly, Category = "Attack")
    TSubclassOf<UGameplayEffect> StaggerEffect;
};