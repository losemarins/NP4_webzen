// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "NP4TownGameMode.generated.h"

/**
 * 
 */

UCLASS()
class NP4_API ANP4TownGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:

	/** Name of the difficulty param on the URL options string. */
	static const FString DifficultyOptionName;

	/** Initialize the GameState actor. */
	virtual void InitGameState() override;

	void ReturnToMenu();

	void ExitGame();


private:
	ANP4TownGameMode();


	
	
	
};
