// Fill out your copyright notice in the Description page of Project Settings.


#include "NetRoleMarker.h"

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

	NetRoleColors = {
		{ ROLE_Authority, FColor::Red },
		{ ROLE_AutonomousProxy, FColor::Green },
		{ ROLE_SimulatedProxy, FColor::Blue },
		{ ROLE_None, FColor::White }
	};
}

void ANetRoleMarker::BeginPlay()
{
	Super::BeginPlay();
	
	check(Mesh);
	check(TextRender);
	
	EnsureMaterial();
	VisualizeLocalNetRole();
}

void ANetRoleMarker::VisualizeLocalNetRole()
{
	const ENetRole NetRole = GetLocalRole();
	const FColor* Color = NetRoleColors.Find(NetRole);
	
	if (!Color) return;

	Visualize(NetRoleToText(NetRole), *Color);
}

void ANetRoleMarker::EnsureMaterial()
{
	if (MeshMaterial) return;

	// Set Dynamic Material to Mesh
	UMaterialInterface* BaseMat = Mesh->GetMaterial(0);
	if (!BaseMat) return;

	MeshMaterial = UMaterialInstanceDynamic::Create(BaseMat, this);
	Mesh->SetMaterial(0, MeshMaterial);
}

void ANetRoleMarker::Visualize(FText Text, FColor Color)
{
	// Change Text
	if (TextRender)
	{
		TextRender->SetText(Text);
		TextRender->SetTextRenderColor(Color);		
	}
	
	// Change Material Color
	if (MeshMaterial)
	{
		MeshMaterial->SetVectorParameterValue(FName("Paint Tint"), Color.ReinterpretAsLinear());	
	}
}

FText ANetRoleMarker::NetRoleToText(ENetRole Role)
{
	const FString EnumString = StaticEnum<ENetRole>()->GetNameStringByValue((int64)Role);
	return FText::FromString(EnumString);
}

