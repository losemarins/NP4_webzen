// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SpectatorPawn.h"
#include "define.h"
#include "MySpectatorPawn.generated.h"

/**
 * 
 */
UCLASS()
class NP4_API AMySpectatorPawn : public ASpectatorPawn
{
	GENERATED_BODY()
	
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	
public :
	//юс╫ц
	void EnemySpawn();
	void PlayerSpawn();
	void LevelChange();
};
