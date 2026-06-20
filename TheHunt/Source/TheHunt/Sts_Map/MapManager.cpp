// Fill out your copyright notice in the Description page of Project Settings.


#include "MapManager.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "MapGenerator.h"
#include "ProgressionSaveData.h"
#include "TheHuntGameInstance.h"
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
    UE_LOG(LogTemp, Warning, TEXT("map loads"));

    if (ConnectionsWidget)
        ConnectionsWidget->RemoveFromParent();

    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if (PC && ConnectionsWidgetClass)
    {
        ConnectionsWidget = CreateWidget<UMapNodeConnectionsWidget>(PC, ConnectionsWidgetClass);
        ConnectionsWidget->AddToViewport(-1);
    }

    UTheHuntGameInstance* GI = GetGameInstance<UTheHuntGameInstance>();
    if (GI && GI->bHasMapState)
        RebuildMapFromSave();
    else
        Regenerate();   // first time only
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

void AMapManager::RebuildMapFromSave()
{
    UTheHuntGameInstance* GI = GetGameInstance<UTheHuntGameInstance>();
    if (!GI) return;

    ClearMap();

    // First pass: spawn all nodes, build an index->node lookup
    TMap<int32, AMapNode*> Lookup;
    for (const FSavedMapNode& Saved : GI->SavedMap)
    {
        AMapNode* Node = GetWorld()->SpawnActor<AMapNode>(
            MapNodeClass, Saved.Location, NodeRotation);
        Node->PointIndex = Saved.Index;
        Node->NodeType = Saved.Type;
        if (Saved.Event) Node->AssignEvent(Saved.Event);

        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = Node;
        AActor* NodeActor = GetWorld()->SpawnActor<AActor>(
            Saved.Event->NodeActorClass, Node->GetActorLocation(), NodeRotation, SpawnParams);
        if (NodeActor)
        {
            NodeActor->AttachToActor(Node, FAttachmentTransformRules::KeepWorldTransform);

            // The visual inherits AMapNode — give it a pointer back to the graph node
            if (AMapNode* VisualNode = Cast<AMapNode>(NodeActor))
                VisualNode->GraphNode = Node;

            SpawnedVisualizationNodes.Add(NodeActor);
        }

        Lookup.Add(Saved.Index, Node);
        SpawnedNodes.Add(Node);
    }

    // Second pass: reconnect NextNodes using the indices
    for (const FSavedMapNode& Saved : GI->SavedMap)
    {
        AMapNode* Node = Lookup[Saved.Index];
        for (int32 NextIdx : Saved.NextIndices)
            if (AMapNode** Found = Lookup.Find(NextIdx))
                Node->NextNodes.Add(*Found);
    }

    // Third pass: spawn the spline paths between connected nodes
    for (AMapNode* Node : SpawnedNodes)
    {
        if (!Node) continue;

        for (AMapNode* NextNode : Node->NextNodes)
        {
            if (!NextNode) continue;

            FVector From = Node->GetActorLocation();
            FVector To = NextNode->GetActorLocation();

            AActor* PathActor = GetWorld()->SpawnActor<AActor>(
                SplinePathActorClass, FVector::ZeroVector, FRotator::ZeroRotator);

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

    SpawnEnvironment(GI->FoliagePoints, GI->HousePoints, GI->RuinPoints);
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

    // Compute start/end indices BEFORE assigning node types
    if (AllPaths.Num() == 0 || AllPaths[0].Num() == 0) return;
    int32 StartIndex = AllPaths[0][0];
    int32 EndIndex = AllPaths[0].Last();
    StartNode = MapGraph[StartIndex];

    SetNodeTypes(MapGraph, AllPaths, StartIndex, EndIndex);

    for (auto& Pair : MapGraph)
        SpawnedNodes.Add(Pair.Value);

    if (UTheHuntGameInstance* GI = GetGameInstance<UTheHuntGameInstance>())
        GI->CurrentNodeIndex = -1;

    SaveMapState(VegetationPoints, HousePoints, RuinPoints);
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

void AMapManager::SetNodeTypes(TMap<int32, AMapNode*>& MapGraph, const TArray<TArray<int32>>& AllPaths, int32 StartIndex, int32 EndIndex)
{
    if (!NodeEventData) return;

    // All node types from the enum (skip the _MAX entry)
    TArray<ENodeType> Types;
    const UEnum* EnumPtr = StaticEnum<ENodeType>();
    for (int32 i = 0; i < EnumPtr->NumEnums() - 1; i++)
        Types.Add((ENodeType)EnumPtr->GetValueByIndex(i));

    TMap<AMapNode*, ENodeType> Assigned;
    const int32 SpacingRadius = 3;   // no same type within this many steps along a path

    // --- Assign types path by path ---
    for (const TArray<int32>& Path : AllPaths)
    {
        // Track the type assigned at each position along THIS path,
        // so we can look back up to SpacingRadius steps.
        TArray<ENodeType> PathTypes;
        PathTypes.Reserve(Path.Num());

        for (int32 PosInPath = 0; PosInPath < Path.Num(); PosInPath++)
        {
            int32 NodeIndex = Path[PosInPath];
            AMapNode** NodePtr = MapGraph.Find(NodeIndex);
            if (!NodePtr || !*NodePtr) { PathTypes.Add(ENodeType::Combat); continue; }
            AMapNode* Node = *NodePtr;

            // Convergence point already assigned by an earlier path — keep it
            if (Assigned.Contains(Node))
            {
                PathTypes.Add(Assigned[Node]);
                continue;
            }

            ENodeType Chosen;

            if (NodeIndex == StartIndex || NodeIndex == EndIndex)
            {
                Chosen = ENodeType::Combat;
            }
            else
            {
                // Collect the types within SpacingRadius steps BEHIND us on this path
                TSet<ENodeType> Forbidden;
                int32 Back = FMath::Max(0, PosInPath - SpacingRadius);
                for (int32 j = Back; j < PosInPath; j++)
                    Forbidden.Add(PathTypes[j]);

                // Prefer Combat whenever spacing allows it
                if (!Forbidden.Contains(ENodeType::Combat))
                {
                    Chosen = ENodeType::Combat;
                }
                else
                {
                    TArray<ENodeType> Available = Types.FilterByPredicate([&](ENodeType T)
                        { return T != ENodeType::Combat && !Forbidden.Contains(T); });

                    if (Available.IsEmpty())
                        Available = Types.FilterByPredicate([&](ENodeType T) { return T != ENodeType::Combat; });

                    Chosen = Available.IsEmpty()
                        ? ENodeType::Combat
                        : Available[FMath::RandRange(0, Available.Num() - 1)];
                }
            }

            Assigned.Add(Node, Chosen);
            Node->NodeType = Chosen;
            PathTypes.Add(Chosen);
        }
    }

    // --- Now that every node has a type, spawn events / visuals / splines ---
    for (auto& Pair : MapGraph)
    {
        AMapNode* Node = Pair.Value;
        if (!Node) continue;

        ENodeType NodeType = Node->NodeType;

        FNodeEventPool* Pool = NodeEventData->NodeMappings.Find(TEnumAsByte<ENodeType>(NodeType));
        if (!Pool || Pool->Events.IsEmpty()) continue;

        UMapEventData* Event = Pool->Events[FMath::RandRange(0, Pool->Events.Num() - 1)].LoadSynchronous();
        if (!Event) continue;
        Node->AssignEvent(Event);

        // --- Visual actor ---
        if (Event->NodeActorClass)
        {
            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = Node;
            if (AActor* NodeActor = GetWorld()->SpawnActor<AActor>(
                Event->NodeActorClass, Node->GetActorLocation(), NodeRotation, SpawnParams))
            {
                NodeActor->AttachToActor(Node, FAttachmentTransformRules::KeepWorldTransform);
                if (AMapNode* VisualNode = Cast<AMapNode>(NodeActor))
                    VisualNode->GraphNode = Node;
                SpawnedVisualizationNodes.Add(NodeActor);
            }
        }

        // --- Spline paths to next nodes ---
        for (AMapNode* NextNode : Node->NextNodes)
        {
            if (!NextNode) continue;
            if (AActor* PathActor = GetWorld()->SpawnActor<AActor>(
                SplinePathActorClass, FVector::ZeroVector, FRotator::ZeroRotator))
            {
                if (USplineComponent* Spline = PathActor->FindComponentByClass<USplineComponent>())
                {
                    Spline->SetWorldLocationAtSplinePoint(0, Node->GetActorLocation());
                    Spline->SetWorldLocationAtSplinePoint(1, NextNode->GetActorLocation());
                    Spline->UpdateSpline();
                    if (UFunction* Func = PathActor->FindFunction(FName("RebuildSegments")))
                        PathActor->ProcessEvent(Func, nullptr);
                }
                SpawnedPathActors.Add(PathActor);
            }
        }
    }
}

void AMapManager::SaveMapState(TArray<FVector2D>& FoliagePoints, TArray<FVector2D>& HousePoints, TArray<FVector2D>& RuinPoints)
{
    UTheHuntGameInstance* GI = GetGameInstance<UTheHuntGameInstance>();
    if (!GI) return;

    GI->SavedMap.Empty();

    // First build a lookup so we can write connections as indices
    for (AMapNode* Node : SpawnedNodes)
    {
        if (!Node) continue;

        FSavedMapNode Saved;
        Saved.Index = Node->PointIndex;
        Saved.Location = Node->GetActorLocation();
        Saved.Type = Node->NodeType;
        Saved.Event = Node->GetAssignedEvent();   // whatever getter you have for the event

        // connections as indices
        for (AMapNode* Next : Node->NextNodes)
            if (Next) Saved.NextIndices.Add(Next->PointIndex);

        GI->SavedMap.Add(Saved);
    }

    GI->FoliagePoints = FoliagePoints;
    GI->HousePoints = HousePoints;
    GI->RuinPoints = RuinPoints;
    GI->bHasMapState = true;
}

