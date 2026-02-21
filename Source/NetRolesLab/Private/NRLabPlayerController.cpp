// Fill out your copyright notice in the Description page of Project Settings.


#include "NRLabPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "NRLabCharacter.h"
#include "Blueprint/UserWidget.h"

class ANRLabCharacter;

void ANRLabPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ANRLabPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(MappingContext, 10);
	
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	
	EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &ThisClass::Input_Fire);	
}

void ANRLabPlayerController::Input_Fire()
{
	Server_Fire();
}

void ANRLabPlayerController::Server_Fire_Implementation()
{
	if (ANRLabCharacter* ControlledPawn = Cast<ANRLabCharacter>(GetPawn()))
	{
		ControlledPawn->Fire();
	}
}
