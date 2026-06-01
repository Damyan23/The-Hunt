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
}

#if WITH_EDITOR
void AMapManager::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);
    if (!GetWorld()) return;
    FlushPersistentDebugLines(GetWorld());
    ClearMap();

    UMapGenerator* Generator = NewObject<UMapGenerator>();
    TArray<FVector2D> Points = Generator->PoissonDiskSample(BoardSize, MinDistPath, SamplesBeforeRejectionPath);

    // Draw edges
    TArray<TPair<int32, int32>> Edges = Generator->BuildDelaunayConnections(Points);
    for (auto& Edge : Edges)
    {
        FVector A = FVector(Points[Edge.Key].X, Points[Edge.Key].Y, 0.f) + GetActorLocation();
        FVector B = FVector(Points[Edge.Value].X, Points[Edge.Value].Y, 0.f) + GetActorLocation();
        DrawDebugLine(GetWorld(), A, B, FColor::Blue, true, -1.f, 0, 1.f);
    }

    // Draw path
    TArray<FColor> PathColors = { FColor::Yellow, FColor::Orange, FColor::Cyan, FColor::Purple, FColor::Red };
    TArray<TArray<int32>> AllPaths = Generator->GeneratePaths(Edges, Points, BoardSize, 5, 1, 2, 4, 8);

    for (int32 p = 0; p < AllPaths.Num(); p++)
    {
        FColor Color = PathColors[p % PathColors.Num()];
        TArray<int32>& Path = AllPaths[p];

        for (int32 i = 0; i < Path.Num() - 1; i++)
        {
            FVector A = FVector(Points[Path[i]].X, Points[Path[i]].Y, 0.f) + GetActorLocation();
            FVector B = FVector(Points[Path[i + 1]].X, Points[Path[i + 1]].Y, 0.f) + GetActorLocation();
            DrawDebugLine(GetWorld(), A, B, Color, true, -1.f, 0, 10.f);
        }
    }
    
    // Vegetation
    TArray<FVector2D> PathNodePositions;
    TSet<int32> PathNodeIndices;
    for (TArray<int32>& Path : AllPaths)
        for (int32 Index : Path)
            PathNodeIndices.Add(Index);

    for (int32 Index : PathNodeIndices)
        PathNodePositions.Add(Points[Index]);

    TArray<TPair<FVector2D, FVector2D>> PathSegments;
    for (TArray<int32>& Path : AllPaths)
        for (int32 i = 0; i < Path.Num() - 1; i++)
            PathSegments.Add({ Points[Path[i]], Points[Path[i + 1]] });

    TArray<FVector2D> HousePoints;
    TArray<FVector2D> RuinPoints;
    TArray<FVector2D> VegetationPoints = Generator->PoissonDiskSample(
        BoardSize, MinDistFoliage, SamplesBeforeRejectionFoliage,
        PathNodePositions, MinDistFoliage,
        PathSegments, PathClearanceRadius,
        SpawnChanceHouses, ClearanceRadiusHouses, HousePoints, 
        SpawnChanceRuins, ClearanceRadiusRuins, RuinPoints);

    // Remove vegetation points inside any house radius
    VegetationPoints.RemoveAll([&](const FVector2D& VP)
        {
            for (FVector2D& HP : HousePoints)
                if (FVector2D::Distance(VP, HP) < ClearanceRadiusHouses)
                    return true;

            for (FVector2D& RP : RuinPoints)
                if (FVector2D::Distance(VP, RP) < ClearanceRadiusRuins)
                    return true;

            return false;
        });


    SpawnEnvironment(VegetationPoints, HousePoints, RuinPoints);

    TMap<int32, AMapNode*> MapGraph = Generator->BuildMapGraph(AllPaths, Points, GetWorld(), GetActorLocation(), MapNodeClass, this);

    if (NodeEventData)
    {
        TArray<TEnumAsByte<ENodeType>> Types = { Combat, Shop, Event };

        for (auto& Pair : MapGraph)
        {
            AMapNode* Node = Pair.Value;

            Node->NodeType = ENodeType::Combat;

            UMapEventData* Event = NodeEventData->NodeMappings.Find(ENodeType::Combat)->Events[0].LoadSynchronous();

            Node->AssignEvent(Event);
            Node->MeshComponent->SetStaticMesh(Event->NodeMesh);
        }
    }

    // Guard at the top after generating paths
    if (AllPaths.Num() == 0 || AllPaths[0].Num() == 0) return;
    int StartIndex = AllPaths[0][0];
    StartNode = MapGraph[StartIndex];

    for (auto& Pair : MapGraph)
        SpawnedNodes.Add(Pair.Value);
    /*
    UE_LOG(LogTemp, Warning, TEXT("MapGraph Nodes: %i"), MapGraph.Num());

    for (auto& Pair : MapGraph)
    {
        AMapNode* Node = Pair.Value;
        FVector From = FVector(Points[Node->PointIndex].X, Points[Node->PointIndex].Y, 200.f) + GetActorLocation();
        DrawDebugSphere(GetWorld(), From, 20.f, 8, FColor::White, true, -1.f);

        SpawnedNodes.Add(Pair.Value);

        UE_LOG(LogTemp, Warning, TEXT("Node %i has %i connections"), Node->PointIndex, Node->NextNodes.Num());

        for (AMapNode* NextNode : Node->NextNodes)
        {
            if (!NextNode) continue;
            FVector To = NextNode->GetActorLocation() + FVector(0, 0, 200.f);
            DrawDebugLine(GetWorld(), From, To, FColor::Green, true, -1.f, 0, 8.f);
        }
    }
    */

    // Draw start and end points bigger so they're visible
    if (AllPaths.Num() > 0)
    {
        // Start is the first point of the first path
        FVector Start = FVector(Points[AllPaths[0][0]].X, Points[AllPaths[0][0]].Y, 0.f) + GetActorLocation();

        // End is the last point of the first path
        FVector End = FVector(Points[AllPaths[0].Last()].X, Points[AllPaths[0].Last()].Y, 0.f) + GetActorLocation();

        DrawDebugSphere(GetWorld(), Start, 20.f, 8, FColor::Orange, true, -1.f);
        DrawDebugSphere(GetWorld(), End, 20.f, 8, FColor::Red, true, -1.f);
    }

    // Draw bounding box
    FVector Center = GetActorLocation() + FVector(BoardSize.X / 2.f, BoardSize.Y / 2.f, 0.f);
    FVector Extent = FVector(BoardSize.X / 2.f, BoardSize.Y / 2.f, 0.f);
    DrawDebugBox(GetWorld(), Center, Extent, FColor::Red, true, -1.f, 0, 3.f);
}
#endif

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
    TArray<FVector2D> Points = Generator->PoissonDiskSample(BoardSize, MinDistPath, SamplesBeforeRejectionPath);

   
    // Draw edges
    TArray<TPair<int32, int32>> Edges = Generator->BuildDelaunayConnections(Points);
    /*
    for (auto& Edge : Edges)
    {
        FVector A = FVector(Points[Edge.Key].X, Points[Edge.Key].Y, 0.f) + GetActorLocation();
        FVector B = FVector(Points[Edge.Value].X, Points[Edge.Value].Y, 0.f) + GetActorLocation();
        DrawDebugLine(GetWorld(), A, B, FColor::Blue, true, -1.f, 0, 1.f);
    }
    */

    // Draw path
    TArray<FColor> PathColors = { FColor::Yellow, FColor::Orange, FColor::Cyan, FColor::Purple, FColor::Red };
    TArray<TArray<int32>> AllPaths = Generator->GeneratePaths(Edges, Points, BoardSize, 5, 1, 2, 4, 8);

    /*
    for (int32 p = 0; p < AllPaths.Num(); p++)
    {
        FColor Color = PathColors[p % PathColors.Num()];
        TArray<int32>& Path = AllPaths[p];

        for (int32 i = 0; i < Path.Num() - 1; i++)
        {
            FVector A = FVector(Points[Path[i]].X, Points[Path[i]].Y, 0.f) + GetActorLocation();
            FVector B = FVector(Points[Path[i + 1]].X, Points[Path[i + 1]].Y, 0.f) + GetActorLocation();
            DrawDebugLine(GetWorld(), A, B, Color, true, -1.f, 0, 10.f);
        }
    }
    */
    // Vegetation


    TArray<FVector2D> PathNodePositions;
    TSet<int32> PathNodeIndices;
    for (TArray<int32>& Path : AllPaths)
        for (int32 Index : Path)
            PathNodeIndices.Add(Index);

    for (int32 Index : PathNodeIndices)
        PathNodePositions.Add(Points[Index]);

    TArray<TPair<FVector2D, FVector2D>> PathSegments;
    for (TArray<int32>& Path : AllPaths)
        for (int32 i = 0; i < Path.Num() - 1; i++)
            PathSegments.Add({ Points[Path[i]], Points[Path[i + 1]] });

    TArray<FVector2D> HousePoints;
    TArray<FVector2D> RuinPoints;
    TArray<FVector2D> VegetationPoints = Generator->PoissonDiskSample(
        BoardSize, MinDistFoliage, SamplesBeforeRejectionFoliage,
        PathNodePositions, MinDistFoliage,
        PathSegments, PathClearanceRadius,
        SpawnChanceHouses, ClearanceRadiusHouses, HousePoints,
        SpawnChanceRuins, ClearanceRadiusRuins, RuinPoints);

    // Remove vegetation points inside any house radius
    VegetationPoints.RemoveAll([&](const FVector2D& VP)
        {
            for (FVector2D& HP : HousePoints)
                if (FVector2D::Distance(VP, HP) < ClearanceRadiusHouses)
                    return true;

            for (FVector2D& RP : RuinPoints)
                if (FVector2D::Distance(VP, RP) < ClearanceRadiusRuins)
                    return true;

            return false;
        });


    SpawnEnvironment(VegetationPoints, HousePoints, RuinPoints);



    TMap<int32, AMapNode*> MapGraph = Generator->BuildMapGraph(AllPaths, Points, GetWorld(), GetActorLocation(), MapNodeClass, this);


    if (NodeEventData)
    {
        TArray<TEnumAsByte<ENodeType>> Types = { Combat, Shop, Event };

        for (auto& Pair : MapGraph)
        {
            AMapNode* Node = Pair.Value;
            Node->NodeType = ENodeType::Combat;

            UMapEventData* Event = NodeEventData->NodeMappings.Find(ENodeType::Combat)->Events[0].LoadSynchronous();

            Node->AssignEvent(Event);
            Node->MeshComponent->SetStaticMesh(Event->NodeMesh);

            for (AMapNode* NextNode : Node->NextNodes)
            {
                if (!NextNode) continue;

                FVector From = Node->GetActorLocation();
                FVector To = NextNode->GetActorLocation();

                FVector Direction = (To - From).GetSafeNormal();
                FRotator Rotation = Direction.Rotation();

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
    // Guard at the top after generating paths
    if (AllPaths.Num() == 0 || AllPaths[0].Num() == 0) return;
    int StartIndex = AllPaths[0][0];
    StartNode = MapGraph[StartIndex];

    for (auto& Pair : MapGraph)
        SpawnedNodes.Add(Pair.Value);
    /*
    UE_LOG(LogTemp, Warning, TEXT("MapGraph Nodes: %i"), MapGraph.Num());

    for (auto& Pair : MapGraph)
    {
        AMapNode* Node = Pair.Value;
        FVector From = FVector(Points[Node->PointIndex].X, Points[Node->PointIndex].Y, 200.f) + GetActorLocation();
        DrawDebugSphere(GetWorld(), From, 20.f, 8, FColor::White, true, -1.f);

        SpawnedNodes.Add(Pair.Value);

        UE_LOG(LogTemp, Warning, TEXT("Node %i has %i connections"), Node->PointIndex, Node->NextNodes.Num());

        for (AMapNode* NextNode : Node->NextNodes)
        {
            if (!NextNode) continue;
            FVector To = NextNode->GetActorLocation() + FVector(0, 0, 200.f);
            DrawDebugLine(GetWorld(), From, To, FColor::Green, true, -1.f, 0, 8.f);
        }
    }
    */

    // Draw start and end points bigger so they're visible
    if (AllPaths.Num() > 0)
    {
        // Start is the first point of the first path
        FVector Start = FVector(Points[AllPaths[0][0]].X, Points[AllPaths[0][0]].Y, 0.f) + GetActorLocation();

        // End is the last point of the first path
        FVector End = FVector(Points[AllPaths[0].Last()].X, Points[AllPaths[0].Last()].Y, 0.f) + GetActorLocation();

        DrawDebugSphere(GetWorld(), Start, 20.f, 8, FColor::Orange, true, -1.f);
        DrawDebugSphere(GetWorld(), End, 20.f, 8, FColor::Red, true, -1.f);
    }

    // Draw bounding box
    FVector Center = GetActorLocation() + FVector(BoardSize.X / 2.f, BoardSize.Y / 2.f, 0.f);
    FVector Extent = FVector(BoardSize.X / 2.f, BoardSize.Y / 2.f, 0.f);
    DrawDebugBox(GetWorld(), Center, Extent, FColor::Red, true, -1.f, 0, 3.f);
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
            float Scale = FMath::FRandRange(0.1f, 0.3f);
            BigStoneISMC->AddInstance(FTransform(RandomRot, WorldPos, FVector(Scale)));
        }
        else if (Roll < 0.2f && SmallStoneISMC && SmallStoneMesh)
        {
            float Scale = FMath::FRandRange(0.1f, 0.25f);
            SmallStoneISMC->AddInstance(FTransform(RandomRot, WorldPos, FVector(Scale)));
        }
        else if (FoliageISMC && FoliageMesh)
        {
            float Scale = FMath::FRandRange(0.25f, 0.5f);
            FoliageISMC->AddInstance(FTransform(RandomRot, WorldPos, FVector(Scale)));
        }
    }

    for (FVector2D& Point : HousePoints)
    {
        FVector WorldPos = FVector(Point.X, Point.Y, 0.f) + GetActorLocation();
        FRotator RandomRot = FRotator(0.f, FMath::FRandRange(0.f, 360.f), 0.f);

        HouseISMC->AddInstance(FTransform(RandomRot, WorldPos, FVector(0.5f)));
    }

    for (FVector2D& Point : RuinPoints)
    {
        FVector WorldPos = FVector(Point.X, Point.Y, 0.f) + GetActorLocation();
        FRotator RandomRot = FRotator(0.f, FMath::FRandRange(0.f, 360.f), 0.f);

        RuinsISMC->AddInstance(FTransform(RandomRot, WorldPos, FVector(0.5f)));
    }
}
