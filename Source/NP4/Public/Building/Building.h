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
	uint8 MyTeamNum;

public:	
	// Sets default values for this actor's properties
	ABuilding();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

public :
	FPlayerData* GetTeamData() const;
};
