#pragma once
#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "Interactable.generated.h"

class UItemDefinition;

UCLASS(Abstract)
class THEHUNT_API AInteractable : public AActor
{
    GENERATED_BODY()
    
    void InitializeItemDefinition();

public:
    AInteractable();

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Item")
    TObjectPtr<UItemDefinition> ItemDefinition;

    UPROPERTY(EditDefaultsOnly, Category = "Item")
    FString ItemID;

    UPROPERTY(EditDefaultsOnly, Category = "Item")
    FName ItemName;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    TObjectPtr<UStaticMeshComponent> ItemMesh;

    // Override in subclasses to define interact behavior
    UFUNCTION(BlueprintNativeEvent, Category = "Interaction")
    void OnInteract(AActor* Interactor);

    virtual void OnInteract_Implementation(AActor* Interactor);

protected:
    void AddToInventory(AActor* Interactor);
};