// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameState.h"
#include "Define.h"
#include "NP4ItemManager.h"
#include "NP4MathManager.h"
#include "NP4GameState.generated.h"

/**
 * 
 */
UCLASS()
class NP4_API ANP4GameState : public AGameState
{
	GENERATED_BODY()
public:
	// �� ����
	EGameMapState::Type GameMapState;
	// ������ ���̵� ���� ������ �ִ� ���� 
	EGameDifficulty::Type GameDifficulty;
	// ���� ���°��� ������ �ִ� ����
	EGameplayState::Type GameplayState;
	//�����ۿ� ���� ������ ������ �ִ� �ε� �Ŵ���.
	ANP4ItemManager* m_pItemLoadManager;
	UNP4MathManager* m_pMathManager;

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
	//������ ���� ������ ����
	FPlayerData* GetPlayerData(uint8 TeamNum) const;
	//������ �ε� �Ŵ��� Init & Get
	void InitItemLoadManager();
	ANP4ItemManager* GetItemLoadManager();
	//���� ���� �Ŵ��� Init
	void InitMathManager();
	UNP4MathManager* GetMathManager();
	
protected:
	// @todo, get rid of mutable?
	/** Gameplay information about each player. */
	mutable TArray<FPlayerData> PlayersData;

public :
	ANP4GameState(const FObjectInitializer& ObjectInitializer);
	class UFormationManager* FormationManager;
};
