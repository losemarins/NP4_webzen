// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "NP4TownGameMode.h"
#include "NP4PlayerController.h"
#include "NP4TownPlayerController.h"
#include "NP4PlayerHero.h"
#include "NP4TownPlayer.h"
#include "NP4HUD.h"
#include "NP4GameState.h"
#include "Define.h"
#include "MySpectatorPawn.h"
#include "NP4PlayerState.h"

ANP4TownGameMode::ANP4TownGameMode()
{
	PlayerControllerClass = ANP4TownPlayerController::StaticClass();
	DefaultPawnClass = ANP4TownPlayer::StaticClass();
	PlayerStateClass = ANP4PlayerState::StaticClass();
	GameStateClass = ANP4GameState::StaticClass();
	HUDClass = ANP4HUD::StaticClass();

	if ((GEngine != nullptr) && (GEngine->GameViewport != nullptr))
	{
		GEngine->GameViewport->SetSuppressTransitionMessage(true);
	}
}

const FString ANP4TownGameMode::DifficultyOptionName(TEXT("Difficulty"));

void ANP4TownGameMode::InitGameState()
{
	Super::InitGameState();

	ANP4GameState* const GameState = GetGameState<ANP4GameState>();
	if (GameState)
	{
		// ���̵� ����
		EGameDifficulty::Type const NewDifficulty = (EGameDifficulty::Type) UGameplayStatics::GetIntOption(OptionsString, DifficultyOptionName, 0);
		GameState->SetGameDifficulty(NewDifficulty);
		GameState->SetGameMap(EGameMapState::Town);
		// start the game!
		GameState->StartGameplayStateMachine();
	}
}

void ANP4TownGameMode::ReturnToMenu()
{

}

void ANP4TownGameMode::ExitGame()
{

}