// Fill out your copyright notice in the Description page of Project Settings.


#include "NetRoleMarker.h"

#include "NetRoleVisualizerComponent.h"
#include "Components/TextRenderComponent.h"


ANetRoleMarker::ANetRoleMarker()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(Mesh);
	Mesh->SetMobility(EComponentMobility::Movable);
	Mesh->SetSimulatePhysics(true);
	
	TextRender = CreateDefaultSubobject<UTextRenderComponent>(TEXT("NetRoleTextRender"));
	TextRender->SetupAttachment(Mesh);
	TextRender->SetWorldSize(42);
	TextRender->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);

	NetRoleVisualizer = CreateDefaultSubobject<UNetRoleVisualizerComponent>(TEXT("NetRoleVisualizer"));
}

void ANetRoleMarker::BeginPlay()
{
	Super::BeginPlay();
	
	check(Mesh);
	check(TextRender);
}

