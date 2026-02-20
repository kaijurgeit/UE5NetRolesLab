// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NRLabCharacter.generated.h"

class UTextRenderComponent;
class UNetRoleVisualizerComponent;

UCLASS()
class NETROLESLAB_API ANRLabCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ANRLabCharacter();
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	virtual void BeginPlay() override;

private:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UTextRenderComponent> TextRender;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UNetRoleVisualizerComponent> NetRoleVisualizer;
	
protected:
	UPROPERTY(BlueprintReadOnly, Replicated)
	int32 Ammo = 5;
	
public:
	void Fire();
	
private:
	void SpawnProjectile();
	void PrintIsLocallyControlled() const;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> ProjectileClass;
};
