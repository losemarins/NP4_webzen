// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "MySpectatorPawn.h"
#include "NP4GameState.h"

void AMySpectatorPawn::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	InputComponent->BindAction("Spawn_1", IE_Pressed, this, &AMySpectatorPawn::PlayerSpawn);
	InputComponent->BindAction("Spawn_2", IE_Pressed, this, &AMySpectatorPawn::EnemySpawn);
	InputComponent->BindAction("Level_Change", IE_Pressed, this, &AMySpectatorPawn::LevelChange);
}

void AMySpectatorPawn::PlayerSpawn()
{
	/*const FPlayerData* const PlayerTeamData = GetWorld()->GetGameState<ANP4GameState>()->GetPlayerData(EGameTeam::Player);
	{
		PlayerTeamData->Brewery->GetAIDirector()->RequestSpawn();
	}*/
}

void AMySpectatorPawn::EnemySpawn()
{

}

void AMySpectatorPawn::LevelChange()
{

}