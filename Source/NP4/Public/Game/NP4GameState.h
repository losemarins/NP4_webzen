// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameState.h"
#include "Define.h"
#include "NP4GameState.generated.h"

/**
 * 
 */
UCLASS()
class NP4_API ANP4GameState : public AGameState
{
	GENERATED_BODY()
	
public:
	// 맵 변수
	EGameMapState::Type GameMapState;
	// 게임의 난이도 값을 가지고 있는 변수 
	EGameDifficulty::Type GameDifficulty;
	// 게임 상태값을 가지고 있는 변수
	EGameplayState::Type GameplayState;
	// 게임의 난이도를 설정
	void SetGameDifficulty(EGameDifficulty::Type NewDifficulty);
	// 게임 상태 머신 시작 
	void StartGameplayStateMachine();
	// 게임 시작 
	void OnGameStart();
	// 게임의 상태값을 설정
	void SetGameplayState(EGameplayState::Type NewState);
	// 게임의 레벨을 설정(맵)
	void SetGameMap(EGameMapState::Type NewState);
	//게임의 진영 데이터 리턴
	FPlayerData* GetPlayerData(uint8 TeamNum) const;

protected:
	// @todo, get rid of mutable?
	/** Gameplay information about each player. */
	mutable TArray<FPlayerData> PlayersData;

};
