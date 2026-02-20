// Fill out your copyright notice in the Description page of Project Settings.


#include "AuthorityMarker.h"

#include "Components/TextRenderComponent.h"


AAuthorityMarker::AAuthorityMarker()
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
}

void AAuthorityMarker::BeginPlay()
{
	Super::BeginPlay();
	
	check(Mesh);
	check(TextRender);
	
	EnsureMaterial();
	VisualizeHasAuthority();
}

void AAuthorityMarker::VisualizeHasAuthority()
{
	if (HasAuthority())
	{
		Visualize(FText::FromString("Has Authority"), FColor::Red);
	}
	else
	{		
		Visualize(FText::FromString("Doesn't have Authority"), FColor::Black);
	}
}

void AAuthorityMarker::EnsureMaterial()
{
	if (MeshMaterial) return;

	// Set Dynamic Material to Mesh
	UMaterialInterface* BaseMat = Mesh->GetMaterial(0);
	if (!BaseMat) return;

	MeshMaterial = UMaterialInstanceDynamic::Create(BaseMat, this);
	Mesh->SetMaterial(0, MeshMaterial);
}

void AAuthorityMarker::Visualize(FText Text, FColor Color)
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

