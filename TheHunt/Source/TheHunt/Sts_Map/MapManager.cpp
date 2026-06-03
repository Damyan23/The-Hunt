// Fill out your copyright notice in the Description page of Project Settings.


#include "MapManager.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "MapGenerator.h"
#include "Components/SplineComponent.h"
#include "Nodes/MapNode.h"
#include "Nodes/MapNodeConnectionWidget.h"
#include "Node Events/MapEventData.h"
#include "Nodes/NodeTypeData.h"

// Sets default values
AMapManager::AMapManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // In AMapManager constructor
    FoliageISMC = CreateDefaultSubobject<UInstancedStaticMeshComponent>("FoliageISMC");
    FoliageISMC->SetupAttachment(RootComponent);

    HouseISMC = CreateDefaultSubobject<UInstancedStaticMeshComponent>("HouseISMC");
    HouseISMC->SetupAttachment(RootComponent);

    // Constructor
    RuinsISMC = CreateDefaultSubobject<UInstancedStaticMeshComponent>("RuinsISMC");
    RuinsISMC->SetupAttachment(RootComponent);

    SmallStoneISMC = CreateDefaultSubobject<UInstancedStaticMeshComponent>("SmallStoneISMC");
    SmallStoneISMC->SetupAttachment(RootComponent);

    BigStoneISMC = CreateDefaultSubobject<UInstancedStaticMeshComponent>("BigStoneISMC");
    BigStoneISMC->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMapManager::BeginPlay()
{
    Super::BeginPlay();

    if (ConnectionsWidget)
        ConnectionsWidget->RemoveFromParent();

    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if (PC && ConnectionsWidgetClass)
    {
        ConnectionsWidget = CreateWidget<UMapNodeConnectionsWidget>(PC, ConnectionsWidgetClass);
        ConnectionsWidget->AddToViewport(-1);
    }

    Regenerate();
}

void AMapManager::ClearMap()
{
    for (AMapNode* Node : SpawnedNodes)
    {
        if (Node)
            Node->Destroy();
    }
    SpawnedNodes.Empty();

    if (FoliageISMC) FoliageISMC->ClearInstances();
    if (HouseISMC) HouseISMC->ClearInstances();

    for (AActor* Actor : SpawnedPathActors)
        if (Actor) Actor->Destroy();
    SpawnedPathActors.Empty();

    for (AActor* Actor : SpawnedVisualizationNodes)
        if (Actor) Actor->Destroy();
    SpawnedVisualizationNodes.Empty();
}

// Called every frame
void AMapManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMapManager::Regenerate()
{
    if (!GetWorld()) return;
    FlushPersistentDebugLines(GetWorld());
    ClearMap();

    UMapGenerator* Generator = NewObject<UMapGenerator>();
    Generator->Initialize(GeneratorSettings);

    TArray<TArray<int32>> AllPaths;
    TMap<int32, AMapNode*> MapGraph;
    TArray<FVector2D> VegetationPoints, HousePoints, RuinPoints;

    Generator->GenerateMap(AllPaths, MapGraph, VegetationPoints, HousePoints, RuinPoints,
        GetWorld(), GetActorLocation(), MapNodeClass, this);

    SpawnEnvironment(VegetationPoints, HousePoints, RuinPoints);

    SetNodeTypes(MapGraph);
    
    // Guard at the top after generating paths
    if (AllPaths.Num() == 0 || AllPaths[0].Num() == 0) return;
    int StartIndex = AllPaths[0][0];
    StartNode = MapGraph[StartIndex];

    for (auto& Pair : MapGraph)
        SpawnedNodes.Add(Pair.Value);
}

void AMapManager::SpawnEnvironment(TArray<FVector2D>& FoliagePoints, TArray<FVector2D>& HousePoints, TArray<FVector2D>& RuinPoints)
{
    // Set meshes and clear instances
    if (FoliageISMC && FoliageMesh) { FoliageISMC->SetStaticMesh(FoliageMesh); FoliageISMC->ClearInstances(); }
    if (SmallStoneISMC && SmallStoneMesh) { SmallStoneISMC->SetStaticMesh(SmallStoneMesh); SmallStoneISMC->ClearInstances(); }
    if (BigStoneISMC && BigStoneMesh) { BigStoneISMC->SetStaticMesh(BigStoneMesh); BigStoneISMC->ClearInstances(); }
    if (HouseISMC && HouseMesh) { HouseISMC->SetStaticMesh(HouseMesh); HouseISMC->ClearInstances(); }
    if (RuinsISMC && RuinsMesh) { RuinsISMC->SetStaticMesh(RuinsMesh); RuinsISMC->ClearInstances(); }

    for (FVector2D& Point : FoliagePoints)
    {
        FVector WorldPos = FVector(Point.X, Point.Y, 0.f) + GetActorLocation();
        FRotator RandomRot = FRotator(0.f, FMath::FRandRange(0.f, 360.f), 0.f);

        float Roll = FMath::FRand();

        if (Roll < 0.05f && BigStoneISMC && BigStoneMesh)
        {
            float Scale = FMath::FRandRange(0.8, 1.2f);
            BigStoneISMC->AddInstance(FTransform(RandomRot, WorldPos, FVector(Scale)));
        }
        else if (Roll < 0.2f && SmallStoneISMC && SmallStoneMesh)
        {
            float Scale = FMath::FRandRange(0.9, 1.05f);
            SmallStoneISMC->AddInstance(FTransform(RandomRot, WorldPos, FVector(Scale)));
        }
        else if (FoliageISMC && FoliageMesh)
        {
            float Scale = FMath::FRandRange(0.85f, 1.15f);
            FoliageISMC->AddInstance(FTransform(RandomRot, WorldPos, FVector(Scale)));
        }
    }

    for (FVector2D& Point : HousePoints)
    {
        FVector WorldPos = FVector(Point.X, Point.Y, 0.f) + GetActorLocation();
        FRotator RandomRot = FRotator(0.f, FMath::FRandRange(0.f, 360.f), 0.f);

        HouseISMC->AddInstance(FTransform(RandomRot, WorldPos));
    }

    for (FVector2D& Point : RuinPoints)
    {
        FVector WorldPos = FVector(Point.X, Point.Y, 0.f) + GetActorLocation();
        FRotator RandomRot = FRotator(0.f, FMath::FRandRange(0.f, 360.f), 0.f);

        RuinsISMC->AddInstance(FTransform(RandomRot, WorldPos));
    }
}

void AMapManager::SetNodeTypes(TMap<int32, AMapNode*>& MapGraph)
{
    if (NodeEventData)
    {
        TArray<ENodeType> Types = {ENodeType::Combat, ENodeType::RandomEncounter};
        /*
        const UEnum* EnumPtr = StaticEnum<ENodeType>();
        for (int32 i = 0; i < EnumPtr->NumEnums() - 1; i++)
            Types.Add((ENodeType)EnumPtr->GetValueByIndex(i));
            */
        TMap<AMapNode*, ENodeType> AssignedTypes;

        for (auto& Pair : MapGraph)
        {
            AMapNode* Node = Pair.Value;

            // Collect forbidden types from neighbours and neighbours-of-neighbours
            TSet<ENodeType> ForbiddenTypes;
            for (AMapNode* Next : Node->NextNodes)
            {
                if (AssignedTypes.Contains(Next))
                    ForbiddenTypes.Add(AssignedTypes[Next]);
                for (AMapNode* NextNext : Next->NextNodes)
                    if (AssignedTypes.Contains(NextNext))
                        ForbiddenTypes.Add(AssignedTypes[NextNext]);
            }

            // Filter available types
            TArray<ENodeType> Available = Types.FilterByPredicate([&](ENodeType T)
                {
                    return !ForbiddenTypes.Contains(T);
                });

            if (Available.IsEmpty()) Available = Types; // fallback if all types forbidden

            // Pick random available type
            ENodeType AssignedType = Available[FMath::RandRange(0, Available.Num() - 1)];
            AssignedTypes.Add(Node, AssignedType);
            Node->NodeType = AssignedType;

            // Look up event pool for this type
            FNodeEventPool* Pool = NodeEventData->NodeMappings.Find(TEnumAsByte<ENodeType>(AssignedType));
            if (!Pool || Pool->Events.IsEmpty()) continue;

            // Pick random event from pool
            int32 EventIndex = FMath::RandRange(0, Pool->Events.Num() - 1);
            UMapEventData* Event = Pool->Events[EventIndex].LoadSynchronous();
            if (!Event) continue;

            Node->AssignEvent(Event);

            // Spawn the node's visual actor
            if (Event->NodeActorClass)
            {
                FActorSpawnParameters SpawnParams;
                SpawnParams.Owner = Node;
                AActor* NodeActor = GetWorld()->SpawnActor<AActor>(
                    Event->NodeActorClass,
                    Node->GetActorLocation(),
                    Node->GetActorRotation(),
                    SpawnParams
                );
                if (NodeActor)
                {
                    NodeActor->AttachToActor(Node, FAttachmentTransformRules::KeepWorldTransform);
                    SpawnedVisualizationNodes.Add(NodeActor);
                }
            }
       

            // Spawn spline paths to next nodes
            for (AMapNode* NextNode : Node->NextNodes)
            {
                if (!NextNode) continue;

                FVector From = Node->GetActorLocation();
                FVector To = NextNode->GetActorLocation();

                AActor* PathActor = GetWorld()->SpawnActor<AActor>(
                    SplinePathActorClass,
                    FVector::ZeroVector,
                    FRotator::ZeroRotator
                );

                if (PathActor)
                {
                    USplineComponent* Spline = PathActor->FindComponentByClass<USplineComponent>();
                    if (Spline)
                    {
                        Spline->SetWorldLocationAtSplinePoint(0, From);
                        Spline->SetWorldLocationAtSplinePoint(1, To);
                        Spline->UpdateSpline();

                        UFunction* Func = PathActor->FindFunction(FName("RebuildSegments"));
                        if (Func) PathActor->ProcessEvent(Func, nullptr);
                    }
                    SpawnedPathActors.Add(PathActor);
                }
            }
        }
    }
}


