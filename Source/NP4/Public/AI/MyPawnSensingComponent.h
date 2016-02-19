// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Perception/PawnSensingComponent.h"
#include "MyPawnSensingComponent.generated.h"

/**
 * 
 */
UCLASS()
class NP4_API UMyPawnSensingComponent : public UPawnSensingComponent
{
	GENERATED_BODY()
	
	
	virtual FVector GetSensorLocation() const;
	
};
