// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "NRLabPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerAmmoUpdate, int32, NewCount);

UCLASS()
class NETROLESLAB_API ANRLabPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	ANRLabPlayerState();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
public:
	UPROPERTY(BlueprintAssignable)
	FOnPlayerAmmoUpdate OnPlayerAmmoUpdate;

	void DecrementPlayerAmmo();
	int32 GetPlayerAmmo() const { return PlayerAmmo; }
	
protected:
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_PlayerAmmo)
	int32 PlayerAmmo = 5;
	
private:
	UFUNCTION()
	void OnRep_PlayerAmmo();
};
