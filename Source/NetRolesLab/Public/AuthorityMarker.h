// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuthorityMarker.generated.h"

class UTextRenderComponent;

UCLASS()
class NETROLESLAB_API AAuthorityMarker : public AActor
{
	GENERATED_BODY()

public:
	AAuthorityMarker();

protected:
	virtual void BeginPlay() override;

public:
	void VisualizeHasAuthority();

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
};
