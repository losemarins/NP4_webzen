// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Building/Building.h"
#include "Dungeon_Building.generated.h"

/**
 * 
 */
UCLASS()
class NP4_API ADungeon_Building : public ABuilding
{
	GENERATED_BODY()

protected:
	uint8 MyTeamNum;
	
public:
	ADungeon_Building(const FObjectInitializer& ObjectInitializer);
	FPlayerData* GetTeamData() const;
	
	
};
