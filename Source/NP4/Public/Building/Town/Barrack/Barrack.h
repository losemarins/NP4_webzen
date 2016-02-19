// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TownBuilding.h"
#include "Barrack.generated.h"

/**
 * 
 */
UCLASS()
class NP4_API ABarrack : public ATownBuilding
{
	GENERATED_BODY()
public:
	virtual void Init() override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

public:
	ABarrack();
		
	
};
