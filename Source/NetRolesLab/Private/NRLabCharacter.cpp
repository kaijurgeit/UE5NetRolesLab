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
	
	PrintIsLocallyControlled();	
}

void ANRLabCharacter::Fire()
{
	PrintIsLocallyControlled();
	
	if (!ProjectileClass) return;
	
	SpawnProjectile();
}

void ANRLabCharacter::SpawnProjectile()
{
	FVector FireSpawnLocation = GetActorLocation() + GetActorForwardVector() * 100.f;
	FRotator FireSpawnRotation = GetActorRotation();

	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.Instigator = this;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	GetWorld()->SpawnActor<AActor>(ProjectileClass, FireSpawnLocation, FireSpawnRotation, Params);
}

void ANRLabCharacter::PrintIsLocallyControlled() const
{
	const bool bLocallyControlled = IsLocallyControlled();
	
	FColor Color = bLocallyControlled ? FColor::Green : FColor::Red;
	const FString Message = FString::Printf(TEXT("[%hs] Locally Controlled? %s"), __FUNCTION__, IsLocallyControlled() ? TEXT("Yes") : TEXT("No"));
	GEngine->AddOnScreenDebugMessage(-1, 20, Color, *Message);
}

