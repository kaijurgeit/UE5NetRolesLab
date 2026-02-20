// Fill out your copyright notice in the Description page of Project Settings.


#include "NRLabCharacter.h"

#include "NetRoleVisualizerComponent.h"
#include "Components/TextRenderComponent.h"


ANRLabCharacter::ANRLabCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	TextRender = CreateDefaultSubobject<UTextRenderComponent>(TEXT("NetRoleTextRender"));
	TextRender->SetupAttachment(GetMesh());
	TextRender->SetWorldSize(42);
	TextRender->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);

	NetRoleVisualizer = CreateDefaultSubobject<UNetRoleVisualizerComponent>(TEXT("NetRoleVisualizer"));
}

void ANRLabCharacter::BeginPlay()
{
	Super::BeginPlay();	
}

