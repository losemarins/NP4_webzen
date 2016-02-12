// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "Dungeon_Building.h"
#include "NP4GameState.h"

ADungeon_Building::ADungeon_Building(const FObjectInitializer& ObjectInitializer)
{
	
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
