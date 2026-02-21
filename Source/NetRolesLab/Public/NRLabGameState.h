// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "NRLabGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSharedAmmoUpdate, int32, NewCount);

UCLASS()
class NETROLESLAB_API ANRLabGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	ANRLabGameState();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
public:
	UPROPERTY(BlueprintAssignable)
	FOnSharedAmmoUpdate OnSharedAmmoUpdate;

	void DecrementSharedAmmo();
	
protected:
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_SharedAmmo)
	int32 SharedAmmo = 10;
	
private:
	UFUNCTION()
	void OnRep_SharedAmmo();
};
