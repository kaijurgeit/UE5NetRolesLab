// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NetRoleMarker.generated.h"

class UTextRenderComponent;

UCLASS()
class NETROLESLAB_API ANetRoleMarker : public AActor
{
	GENERATED_BODY()

public:
	ANetRoleMarker();

protected:
	virtual void BeginPlay() override;

public:
	void VisualizeLocalNetRole();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Mesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UTextRenderComponent> TextRender;
	
	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> MeshMaterial;
	
private:	
	void EnsureMaterial();	
	void Visualize(FText Text, FColor Color);
	static FText NetRoleToText(ENetRole Role);
	TMap<TEnumAsByte<ENetRole>, FColor> NetRoleColors;	
};
