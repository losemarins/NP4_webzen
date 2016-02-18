// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "NP4GameMode.h"
#include "NP4PlayerController.h"
#include "NP4HeroController.h"
#include "NP4PlayerHero.h"
#include "NP4PlayerBase.h"
#include "NP4HUD.h"
#include "NP4GameState.h"
#include "Define.h"
#include "MySpectatorPawn.h"
#include "NP4PlayerState.h"

ANP4GameMode::ANP4GameMode()
{
	PlayerControllerClass = ANP4HeroController::StaticClass();		
	//DefaultPawnClass = ANP4PlayerBase::StaticClass();
	static ConstructorHelpers::FClassFinder<ANP4PlayerBase> BPClass(TEXT("/Game/blueprint/PlayerBaseBP"));
	DefaultPawnClass = BPClass.Class;
	PlayerStateClass = ANP4PlayerState::StaticClass();
	GameStateClass = ANP4GameState::StaticClass();
	HUDClass = ANP4HUD::StaticClass();

	if ((GEngine != nullptr) && (GEngine->GameViewport != nullptr))
	{
		GEngine->GameViewport->SetSuppressTransitionMessage(true);
	}
}

const FString ANP4GameMode::DifficultyOptionName(TEXT("Difficulty"));

void ANP4GameMode::InitGameState()
{
	Super::InitGameState();

	ANP4GameState* const GameState = GetGameState<ANP4GameState>();
	if (GameState)
	{
		// 난이도 설정
		EGameDifficulty::Type const NewDifficulty = (EGameDifficulty::Type) UGameplayStatics::GetIntOption(OptionsString, DifficultyOptionName, 0);
		GameState->SetGameDifficulty(NewDifficulty);
		GameState->SetGameMap(EGameMapState::Town);
		// start the game!
		GameState->StartGameplayStateMachine();
	}
}

void ANP4GameMode::ReturnToMenu()
{

}

void ANP4GameMode::ExitGame()
{

}