// Fill out your copyright notice in the Description page of Project Settings.


#include "NRLabCharacter.h"

#include "NetRoleVisualizerComponent.h"
#include "NRLabGameState.h"
#include "NRLabPlayerState.h"
#include "Components/TextRenderComponent.h"
#include "Components/WidgetComponent.h"
#include "Net/UnrealNetwork.h"


ANRLabCharacter::ANRLabCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	TextRender = CreateDefaultSubobject<UTextRenderComponent>(TEXT("NetRoleTextRender"));
	TextRender->SetupAttachment(GetMesh());
	TextRender->SetWorldSize(42);
	TextRender->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);

	NetRoleVisualizer = CreateDefaultSubobject<UNetRoleVisualizerComponent>(TEXT("NetRoleVisualizer"));
		
	PlayerWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("PlayerWidget"));
	PlayerWidgetComponent->SetupAttachment(GetMesh());
}

void ANRLabCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (PlayerWidgetComponent)
	{
		PlayerWidgetComponent->InitWidget();
	}
	TryInitializeWidget();
}

void ANRLabCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	// Runs on Server - PlayerStates guarantee to exist
	TryInitializeWidget();
}

void ANRLabCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	// Runs on Clients - PlayerStates guarantee to exist
	TryInitializeWidget();
}

void ANRLabCharacter::Fire()
{
	if (!HasAuthority()) return;	
	if (!ProjectileClass) return;
	
	ANRLabPlayerState* NRLabPlayerState = GetPlayerState<ANRLabPlayerState>();
	if (!NRLabPlayerState) return;
	
	if (NRLabPlayerState->GetPlayerAmmo() <= 0) return;
	
	NRLabPlayerState->DecrementPlayerAmmo();
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

void ANRLabCharacter::TryInitializeWidget()
{
	if (bIsWidgetInitialized) return;
	
	ANRLabPlayerState* NRLabPlayerState = GetPlayerState<ANRLabPlayerState>();
	if (!NRLabPlayerState) return;

	if (!PlayerWidgetComponent) return;

	UUserWidget* Widget = PlayerWidgetComponent->GetUserWidgetObject();
	if (!Widget) return;
	
	bIsWidgetInitialized = true;

	OnPlayerStateReady();
}
