// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NRLabCharacter.generated.h"

class UTextRenderComponent;
class UNetRoleVisualizerComponent;
class ANRLabGameState;
class UWidgetComponent;
class UUserWidget;

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
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UWidgetComponent> PlayerWidgetComponent;
	
public:
	void Fire();
	
private:
	void SpawnProjectile();
	void PrintIsLocallyControlled() const;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> PlayerWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UUserWidget> PlayerWidget;
};
