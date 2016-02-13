// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "define.h"
#include "Building.generated.h"

UCLASS()
class NP4_API ABuilding : public AActor
{
	GENERATED_BODY()
	
protected :
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	UStaticMeshComponent* MeshComp;

public:	
	// Sets default values for this actor's properties
	ABuilding(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	virtual void PostInitializeComponents() override;
};
