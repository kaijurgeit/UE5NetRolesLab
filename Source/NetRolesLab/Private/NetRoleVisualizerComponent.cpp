// Fill out your copyright notice in the Description page of Project Settings.


#include "NetRoleVisualizerComponent.h"

#include "Components/TextRenderComponent.h"


UNetRoleVisualizerComponent::UNetRoleVisualizerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	NetRoleColors = {
		{ ROLE_Authority, FColor::Red },
		{ ROLE_AutonomousProxy, FColor::Green },
		{ ROLE_SimulatedProxy, FColor::Blue },
		{ ROLE_None, FColor::White }
	};
}


void UNetRoleVisualizerComponent::BeginPlay()
{
	Super::BeginPlay();

	Mesh = GetOwner()->FindComponentByClass<UMeshComponent>();
	check(Mesh);
	
	TextRender = GetOwner()->FindComponentByClass<UTextRenderComponent>();
	check(TextRender);
	
	EnsureMaterial();
	VisualizeLocalNetRole();
}

void UNetRoleVisualizerComponent::VisualizeLocalNetRole()
{
	const ENetRole NetRole = GetOwner()->GetLocalRole();
	const FColor* Color = NetRoleColors.Find(NetRole);
	
	if (!Color) return;

	Visualize(NetRoleToText(NetRole), *Color);
}

void UNetRoleVisualizerComponent::EnsureMaterial()
{
	if (MeshMaterial) return;

	// Set Dynamic Material to Mesh
	UMaterialInterface* BaseMat = Mesh->GetMaterial(0);
	if (!BaseMat) return;

	MeshMaterial = UMaterialInstanceDynamic::Create(BaseMat, this);
	Mesh->SetMaterial(0, MeshMaterial);
}

void UNetRoleVisualizerComponent::Visualize(FText Text, FColor Color)
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

FText UNetRoleVisualizerComponent::NetRoleToText(ENetRole Role)
{
	const FString EnumString = StaticEnum<ENetRole>()->GetNameStringByValue((int64)Role);
	return FText::FromString(EnumString);
}

