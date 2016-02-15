// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Building/Building.h"
#include "define.h"
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

public :
	UPROPERTY(EditInstanceOnly, Category = Building)
	TEnumAsByte<EGameTeam::Type> SpawnTeamNum;

public:
	virtual void PostInitializeComponents() override;
	ADungeon_Building(const FObjectInitializer& ObjectInitializer);
	virtual void SetTeamNum(uint8 NewTeamNum);
	FPlayerData* GetTeamData() const;
};
