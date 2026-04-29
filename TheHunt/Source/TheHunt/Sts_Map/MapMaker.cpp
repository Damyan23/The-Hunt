// Fill out your copyright notice in the Description page of Project Settings.


#include "Sts_Map/MapMaker.h"

#include "MapGenerator.h"

// Sets default values
AMapMaker::AMapMaker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMapMaker::BeginPlay()
{
	Super::BeginPlay();
}

#if WITH_EDITOR
void AMapMaker::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);
    if (!GetWorld()) return;
    FlushPersistentDebugLines(GetWorld());

    UMapGenerator* Generator = NewObject<UMapGenerator>();
    TArray<FVector2D> Points = Generator->PoissonDiskSample(BoardSize, MinDist, SamplesBeforeRejection);

    // Draw points
    for (FVector2D& Point : Points)
    {
        FVector WorldPos = FVector(Point.X, Point.Y, 0.f) + GetActorLocation();
        DrawDebugSphere(GetWorld(), WorldPos, 10.f, 8, FColor::Green, true, -1.f);
    }

    // Draw edges
    TArray<TPair<int32, int32>> Edges = Generator->BuildDelaunayConnections(Points);
    for (auto& Edge : Edges)
    {
        FVector A = FVector(Points[Edge.Key].X, Points[Edge.Key].Y, 0.f) + GetActorLocation();
        FVector B = FVector(Points[Edge.Value].X, Points[Edge.Value].Y, 0.f) + GetActorLocation();
        DrawDebugLine(GetWorld(), A, B, FColor::Blue, true, -1.f, 0, 1.f);
    }

    // Draw path
    TArray<int32> Path = Generator->GetPath(Edges, Points, BoardSize);
    for (int32 i = 0; i < Path.Num() - 1; i++)
    {
        FVector A = FVector(Points[Path[i]].X, Points[Path[i]].Y, 0.f) + GetActorLocation();
        FVector B = FVector(Points[Path[i + 1]].X, Points[Path[i + 1]].Y, 0.f) + GetActorLocation();
        DrawDebugLine(GetWorld(), A, B, FColor::Yellow, true, -1.f, 0, 4.f);
    }

    // Draw start and end points bigger so they're visible
    if (Path.Num() > 0)
    {
        FVector Start = FVector(Points[Path[0]].X, Points[Path[0]].Y, 0.f) + GetActorLocation();
        FVector End = FVector(Points[Path.Last()].X, Points[Path.Last()].Y, 0.f) + GetActorLocation();
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
void AMapMaker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

