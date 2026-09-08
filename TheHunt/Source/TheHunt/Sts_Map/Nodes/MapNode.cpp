// Fill out your copyright notice in the Description page of Project Settings.


#include "MapNode.h"
#include "InputPlayer/PlayerCharacter.h"
#include "Sts_Map/Character/MapCharacter.h"

void AMapNode::OnEnter_Implementation(APlayerController* PC)
{
	if (Event && PC)
	{
		if (Event)
			Event->OnEnter(PC);

		UE_LOG(LogTemp, Warning, TEXT("does it go here?"));
	}
}

void AMapNode::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

AMapNode::AMapNode()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
	MeshComponent->SetupAttachment(RootComponent);

	HoverLight = CreateDefaultSubobject<UPointLightComponent>("HoverLight");
	HoverLight->SetupAttachment(MeshComponent);
	HoverLight->SetIntensity(0.f);          // off by default
	HoverLight->SetAttenuationRadius(250.f); // how far the light reaches
	HoverLight->SetLightColor(FLinearColor::White); // tweak to taste
	HoverLight->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
}

void AMapNode::NotifyActorOnClicked(FKey ButtonPressed)
{
	Super::NotifyActorOnClicked(ButtonPressed);

	// Only react to left click
	if (ButtonPressed != EKeys::LeftMouseButton) return;

	// Get the map character (the player pawn on the map)
	AMapCharacter* MapChar = Cast<AMapCharacter>(
		UGameplayStatics::GetPlayerCharacter(this, 0));

	if (MapChar)
	{
		MapChar->TravelToNode(this); // 'this' is the clicked node (TravelToNode redirects via GraphNode)
	}
}

void AMapNode::NotifyActorBeginCursorOver()
{
	Super::NotifyActorBeginCursorOver();
	bIsHovered = true;

	UGameplayStatics::PlaySoundAtLocation(this, HoverSoundFX, this->GetActorLocation(), this->GetActorRotation(), 0.25);
}

void AMapNode::NotifyActorEndCursorOver()
{
	Super::NotifyActorEndCursorOver();
	bIsHovered = false;
}

void AMapNode::BeginPlay()
{
	Super::BeginPlay();
}

void AMapNode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (HoverLight)
	{
		float TargetIntensity = bIsHovered ? HoverLightIntensity : 0.f;
		float NewIntensity = FMath::FInterpTo(
			HoverLight->Intensity, TargetIntensity, DeltaSeconds, HoverInterpSpeed);
		HoverLight->SetIntensity(NewIntensity);
	}
}


void AMapNode::AssignEvent(UMapEventData* AssignedEvent)
{
	Event = AssignedEvent;
}
