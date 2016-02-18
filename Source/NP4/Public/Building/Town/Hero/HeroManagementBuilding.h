// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Building/Town/TownBuilding.h"
#include "HeroManagementBuilding.generated.h"

/**
 * 
 */
UCLASS()
class NP4_API AHeroManagementBuilding : public ATownBuilding
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;
public:
	AHeroManagementBuilding();
	
	
};
