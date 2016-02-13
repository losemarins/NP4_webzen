// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "MySpectatorPawn.h"
#include "NP4GameState.h"
#include "Building_Castle.h"
#include "AIDirector.h"
#include "MyCameraComponent.h"

AMySpectatorPawn::AMySpectatorPawn(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	GetCollisionComponent()->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	bAddDefaultMovementBindings = false;
	MyCameraComponent = CreateDefaultSubobject<UMyCameraComponent>(TEXT("MyCameraComponent"));
}

void AMySpectatorPawn::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	InputComponent->BindAction("ZoomOut", IE_Pressed, this, &AMySpectatorPawn::OnMouseScrollUp);
	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &AMySpectatorPawn::OnMouseScrollDown);

	InputComponent->BindAction("Spawn_1", IE_Pressed, this, &AMySpectatorPawn::PlayerSpawn);
	InputComponent->BindAction("Spawn_2", IE_Pressed, this, &AMySpectatorPawn::EnemySpawn);
	InputComponent->BindAction("Level_Change", IE_Pressed, this, &AMySpectatorPawn::LevelChange);
}

void AMySpectatorPawn::PlayerSpawn()
{
	const FPlayerData* const PlayerTeamData = GetWorld()->GetGameState<ANP4GameState>()->GetPlayerData(EGameTeam::Player);
	{
		PlayerTeamData->Castle->GetAIDirector()->RequestSpawn();
	}
}

void AMySpectatorPawn::EnemySpawn()
{
	const FPlayerData* const EnemyTeamData = GetWorld()->GetGameState<ANP4GameState>()->GetPlayerData(EGameTeam::Enemy);
	{
		EnemyTeamData->Castle->GetAIDirector()->RequestSpawn();
	}
}

void AMySpectatorPawn::LevelChange()
{
	const FPlayerData* const PlayerTeamData = GetWorld()->GetGameState<ANP4GameState>()->GetPlayerData(EGameTeam::Player);
	{
		PlayerTeamData->Castle->GetAIDirector()->RequestSpawn();
	}
}

void AMySpectatorPawn::MoveForward(float Val)
{
	MyCameraComponent->MoveForward(Val);
}

void AMySpectatorPawn::MoveRight(float Val)
{
	MyCameraComponent->MoveRight(Val);
}

void AMySpectatorPawn::OnMouseScrollUp()
{
	MyCameraComponent->OnZoomIn();
}

void AMySpectatorPawn::OnMouseScrollDown()
{
	MyCameraComponent->OnZoomOut();
}