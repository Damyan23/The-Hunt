// Fill out your copyright notice in the Description page of Project Settings.


#include "MapNode.h"

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
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
	MeshComponent->SetupAttachment(RootComponent);
}


void AMapNode::AssignEvent(UMapEventData* AssignedEvent)
{
	Event = AssignedEvent;
}
