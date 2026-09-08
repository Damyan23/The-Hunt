// Fill out your copyright notice in the Description page of Project Settings.


#include "Item-Spawn-System/ItemSpawner.h"

#include "Components/TextRenderComponent.h"
#include "Items/Weapon/MeleeWeapon.h"
#include "UObject/ConstructorHelpers.h"


#if WITH_EDITOR
#include "Editor.h"
#include "LevelEditorViewport.h"
#endif

// Sets default values
ALootSpawner::ALootSpawner()
{
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bStartWithTickEnabled = true;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    SetRootComponent(Mesh);

    // --- Debug sphere (editor-only gizmo) ---
    DebugSphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DebugSphere"));
    DebugSphere->SetupAttachment(Mesh);
    DebugSphere->SetRelativeLocation(FVector(0, 0, 80));
    DebugSphere->SetRelativeScale3D(FVector(0.3f));
    DebugSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    DebugSphere->bHiddenInGame = true;
    DebugSphere->SetCastShadow(false);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(
        TEXT("/Engine/BasicShapes/Sphere.Sphere"));
    if (SphereMesh.Succeeded())
    {
        DebugSphere->SetStaticMesh(SphereMesh.Object);
    }

    // --- Debug text label (editor-only gizmo) ---
    DebugLabel = CreateDefaultSubobject<UTextRenderComponent>(TEXT("DebugLabel"));
    DebugLabel->SetupAttachment(Mesh);
    DebugLabel->SetRelativeLocation(FVector(0, 0, 130));
    DebugLabel->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
    DebugLabel->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextCenter);
    DebugLabel->SetWorldSize(20.f);
    DebugLabel->bHiddenInGame = true;
    DebugLabel->SetAbsolute(false, true, false);
}

bool ALootSpawner::ShouldTickIfViewportsOnly() const
{
    return true;
}

void ALootSpawner::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

#if WITH_EDITOR
    if (!GetWorld() || GetWorld()->IsGameWorld()) return;
    if (!DebugLabel) return;

    // Get the active editor viewport camera location
    FVector CameraLocation = FVector::ZeroVector;
    if (GEditor)
    {
        for (FLevelEditorViewportClient* ViewportClient : GEditor->GetLevelViewportClients())
        {
            if (ViewportClient && ViewportClient->IsPerspective())
            {
                CameraLocation = ViewportClient->GetViewLocation();
                break;
            }
        }
    }

    // Rotate the label to face the editor camera
    FVector LabelLocation = DebugLabel->GetComponentLocation();
    FVector Direction = CameraLocation - LabelLocation;

    if (!Direction.IsNearlyZero())
    {
        FRotator LookAtRotation = Direction.Rotation();
        DebugLabel->SetWorldRotation(LookAtRotation);
    }
#endif
}

void ALootSpawner::BeginPlay()
{
    Super::BeginPlay();

    SpawnItem();
}

void ALootSpawner::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    // Update debug visuals — runs in editor whenever a property changes
    FColor Color = GetRarityColor();
    // FString Label = GetItemTypeLabel(); // Disabled: header currently has these members commented out
    // DebugLabel->SetText(FText::FromString(Label));
    DebugLabel->SetTextRenderColor(Color);

    if (DebugSphere)
    {
        UMaterialInstanceDynamic* SphereMID = DebugSphere->CreateAndSetMaterialInstanceDynamic(0);
        if (SphereMID)
        {
            SphereMID->SetVectorParameterValue(FName("Color"), FLinearColor(Color));
        }
    }

    // Update spawner mesh material
    if (!ItemRegistry || !Mesh) return;

    UMaterialInstanceDynamic* MID = Mesh->CreateAndSetMaterialInstanceDynamic(0);
    if (!MID) return;

    FLinearColor RarityColor(Color);
    MID->SetVectorParameterValue(FName("Color"), RarityColor);
    MID->SetVectorParameterValue(FName("Emission"), RarityColor);
}

FColor ALootSpawner::GetRarityColor() const
{
    switch (AllowedRarity)
    {
    case EItemRarity::Common: return FColor::Silver;
    case EItemRarity::Rare:   return FColor::Blue;
    case EItemRarity::Epic:   return FColor::Magenta;
    default:                  return FColor::White;
    }
}


FString ALootSpawner::GetItemTypeLabel() const
{
    switch (AllowedItemTypes)
    {
    case EItemType::Weapon:     return TEXT("[WEAPON]");
    case EItemType::Consumable: return TEXT("[CONSUMABLE]");
    case EItemType::Item:       return TEXT("[ITEM]");
    case EItemType::Rune:       return TEXT("[RUNE]");
    default:                    return TEXT("[UNKNOWN]");
    }
}

void ALootSpawner::SpawnItem()
{
    if (!ItemRegistry)
    {
        UE_LOG(LogTemp, Warning, TEXT("SpawnItem: ItemRegistry is null"));
        return;
    }

    TArray<FLootTableRow*> AllRows;
    FString ContextString(TEXT("LootSpawner"));
    ItemRegistry->GetAllRows<FLootTableRow>(ContextString, AllRows);

    TArray<FLootTableRow*> FilteredRows;
    for (FLootTableRow* Row : AllRows)
    {
        if (!Row) continue;
        if (Row->Rarity == AllowedRarity && Row->ItemType == AllowedItemTypes)
        {
            FilteredRows.Add(Row);
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("SpawnItem: %d total rows, %d matched rarity=%d type=%d"),
        AllRows.Num(), FilteredRows.Num(), (int)AllowedRarity, (int)AllowedItemTypes);

    if (FilteredRows.IsEmpty())
    {
        UE_LOG(LogTemp, Warning, TEXT("SpawnItem: no rows matched the allowed rarity/type"));
        return;
    }

    FLootTableRow* ChosenRow = FilteredRows[FMath::RandRange(0, FilteredRows.Num() - 1)];
    if (!ChosenRow || !ChosenRow->ItemDefinition)
    {
        UE_LOG(LogTemp, Warning, TEXT("SpawnItem: chosen row or its ItemDefinition is null"));
        return;
    }

    UItemDefinition* ItemDefinition = ChosenRow->ItemDefinition;
    if (!ItemDefinition->ItemClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("SpawnItem: ItemDefinition %s has no ItemClass set"),
            *ItemDefinition->GetName());
        return;
    }

    FActorSpawnParameters Params;
    Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    FTransform SpawnTransform(GetActorRotation(), GetActorLocation(), FVector(1.f));

    AActor* Spawned = GetWorld()->SpawnActor<AActor>(ItemDefinition->ItemClass, SpawnTransform, Params);
    if (!Spawned)
    {
        UE_LOG(LogTemp, Warning, TEXT("SpawnItem: SpawnActor failed for class %s"),
            *ItemDefinition->ItemClass->GetName());
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("SpawnItem: spawned %s"), *Spawned->GetName());
}