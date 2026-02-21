// Fill out your copyright notice in the Description page of Project Settings.


#include "NRLabGameState.h"

#include "Net/UnrealNetwork.h"

ANRLabGameState::ANRLabGameState()
{
	bReplicates = true;
}

void ANRLabGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ThisClass, SharedAmmo);
}

void ANRLabGameState::DecrementSharedAmmo()
{
	if (!HasAuthority()) return;
	
	SharedAmmo--;
	
	OnSharedAmmoUpdate.Broadcast(SharedAmmo);
}

void ANRLabGameState::OnRep_SharedAmmo()
{	
	OnSharedAmmoUpdate.Broadcast(SharedAmmo);
}
