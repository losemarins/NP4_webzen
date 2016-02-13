// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SpectatorPawn.h"
#include "define.h"
#include "MySpectatorPawn.generated.h"

/**
 * 
 */
 //임시클래스
UCLASS()
class NP4_API AMySpectatorPawn : public ASpectatorPawn
{
	GENERATED_BODY()
	class UMyCameraComponent* MyCameraComponent;

public :
	AMySpectatorPawn(const FObjectInitializer& ObjectInitializer);
	virtual void MoveForward(float Val) override;
	virtual void MoveRight(float Val) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	
	
public :
	void OnMouseScrollUp();
	void OnMouseScrollDown();
	void EnemySpawn();
	void PlayerSpawn();
	void LevelChange();
};
