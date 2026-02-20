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

protected:
	virtual void BeginPlay() override;

private:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UTextRenderComponent> TextRender;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UNetRoleVisualizerComponent> NetRoleVisualizer;
	
public:
	void Fire();
	
private:
	void SpawnProjectile();
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> ProjectileClass;
};
