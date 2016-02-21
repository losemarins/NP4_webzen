// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Building/Building.h"
#include "TownBuilding.generated.h"

/**
 * 
 */
UCLASS()
class NP4_API ATownBuilding : public ABuilding
{
	GENERATED_BODY()
public:
	virtual void Init() ;
	UFUNCTION(BlueprintCallable, Category = "TownBuilding")
	void WindowOpen();
protected:

	EBuilding::Type m_EBuildingType;
	bool m_bIsWindow;
	
	
};
