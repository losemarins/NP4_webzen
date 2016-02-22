// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "NP4GameState.h"
#include "Building_Castle.h"
#include "NP4TownPlayer.h"

ANP4GameState::ANP4GameState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PlayersData.AddZeroed(EGameTeam::MAX);
	
}

void ANP4GameState::SetGameDifficulty(EGameDifficulty::Type NewDifficulty)
{

}

void ANP4GameState::StartGameplayStateMachine()
{
	OnGameStart();
	FormationManager = NewObject<UFormationManager>(this);
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
		if (PlayersData[i].Castle.IsValid())
		{
			PlayersData[i].Castle->OnGameplayStateChange(NewState);
		}
	}
	FRotator Rotation = FRotator( 0, 0, 0);
	FVector Location = FVector(10, 0, 0);

	
	//ANP4TownPlayer* pSpawnActor = (ANP4TownPlayer*)GetWorld()->SpawnActor(ANP4TownPlayer::StaticClass(), &Location, &Rotation);
}

void ANP4GameState::SetGameMap(EGameMapState::Type NewState)
{
	GameMapState = NewState;
}

FPlayerData* ANP4GameState::GetPlayerData(uint8 TeamNum) const
{
	if (TeamNum != EGameTeam::Unknown)
	{
		return &PlayersData[TeamNum];
	}

	return nullptr;
}
