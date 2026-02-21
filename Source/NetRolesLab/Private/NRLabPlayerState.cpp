// Fill out your copyright notice in the Description page of Project Settings.


#include "NRLabPlayerState.h"

#include "Net/UnrealNetwork.h"

ANRLabPlayerState::ANRLabPlayerState()
{	
	bReplicates = true;
}

void ANRLabPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);	
	
	DOREPLIFETIME(ThisClass, PlayerAmmo);
}

void ANRLabPlayerState::DecrementPlayerAmmo()
{	
	if (!HasAuthority()) return;	
	if (PlayerAmmo <= 0) return;
	
	PlayerAmmo--;
	
	OnPlayerAmmoUpdate.Broadcast(PlayerAmmo);
}

void ANRLabPlayerState::OnRep_PlayerAmmo()
{
	OnPlayerAmmoUpdate.Broadcast(PlayerAmmo);
}
