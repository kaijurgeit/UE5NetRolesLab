// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NetRoleVisualizerComponent.generated.h"

class UTextRenderComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NETROLESLAB_API UNetRoleVisualizerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UNetRoleVisualizerComponent();

protected:
	virtual void BeginPlay() override;

public:
	void VisualizeLocalNetRole();
	
private:	
	void EnsureMaterial();	
	void Visualize(FText Text, FColor Color);
	static FText NetRoleToText(ENetRole Role);
	TMap<TEnumAsByte<ENetRole>, FColor> NetRoleColors;
	
	UPROPERTY()
	TObjectPtr<UMeshComponent> Mesh;
	
	UPROPERTY()
	TObjectPtr<UTextRenderComponent> TextRender;
	
	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> MeshMaterial0;
	
	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> MeshMaterial1;
};
