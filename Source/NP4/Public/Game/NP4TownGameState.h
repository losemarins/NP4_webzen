// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameState.h"
#include "Define.h"
#include "NP4TownGameState.generated.h"


/**
 * 
 */
class ABuilding;
class ATile;
UCLASS()
class NP4_API ANP4TownGameState : public AGameState
{
	GENERATED_BODY()
public:
	// �� ����
	EGameMapState::Type GameMapState;
	// ������ ���̵� ���� ������ �ִ� ���� 
	EGameDifficulty::Type GameDifficulty;
	// ���� ���°��� ������ �ִ� ����
	EGameplayState::Type GameplayState;
	// ������ ���̵��� ����
	void SetGameDifficulty(EGameDifficulty::Type NewDifficulty);
	// ���� ���� �ӽ� ���� 
	void StartGameplayStateMachine();
	// ���� ���� 
	void OnGameStart();
	// ������ ���°��� ����
	void SetGameplayState(EGameplayState::Type NewState);
	// ������ ������ ����(��)
	void SetGameMap(EGameMapState::Type NewState);

public:
	// tile
	void InitTile();
	void CreateBuilding(FVector SpawnPos, EBuilding::Type BuildingType);
	
private:
	ANP4TownGameState();


private:
	TArray<ATile*> m_TileArray;
	TArray<ABuilding*> m_BuildingArray;
	TSubclassOf<ATile> m_CharClass;

	
};
