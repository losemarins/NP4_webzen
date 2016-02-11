// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "NP4GameState.h"

void ANP4GameState::SetGameDifficulty(EGameDifficulty::Type NewDifficulty)
{
}

void ANP4GameState::StartGameplayStateMachine()
{
	OnGameStart();
}

void ANP4GameState::OnGameStart()
{
	SetGameplayState(EGameplayState::Playing);
}

void ANP4GameState::SetGameplayState(EGameplayState::Type NewState)
{
	GameplayState = NewState; 

	for (int32 i = 0; i < PlayersData.Num(); i++)
	{
		/*if (PlayersData[i].Brewery.IsValid())
		{
			PlayersData[i].Brewery->OnGameplayStateChange(NewState);
		}*/
	}

}

void ANP4GameState::SetGameMap(EGameMapState::Type NewState)
{
	GameMapState = NewState;
}

