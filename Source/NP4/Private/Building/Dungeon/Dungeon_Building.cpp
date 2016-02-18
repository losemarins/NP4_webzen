// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "Dungeon_Building.h"
#include "NP4GameState.h"

ADungeon_Building::ADungeon_Building(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	
}

void ADungeon_Building::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (SpawnTeamNum != EGameTeam::Unknown)
	{
		SetTeamNum(SpawnTeamNum);
	}
}

void ADungeon_Building::SetTeamNum(uint8 NewTeamNum)
{
	MyTeamNum = NewTeamNum;
	FPlayerData* const PlayerData = GetTeamData();

	if (PlayerData != nullptr)
	{
		PlayerData->BuildingsList.Add(this);
	}
}

FPlayerData* ADungeon_Building::GetTeamData() const
{
	check(GetWorld());
	ANP4GameState* const MyGame = GetWorld()->GetGameState<ANP4GameState>();
	if (MyGame != nullptr)
	{
		return MyGame->GetPlayerData(MyTeamNum);
	}
	return nullptr;
}

