// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Unit/NP4PlayerStateBase.h"
#include "NP4PlayerState.generated.h"

class ANP4PlayerBase;

enum eCharacterState
{
	eIdle = 0,
	eWalk = 10,
	eRun = 20,
	eAttack = 30,
	eHit = 40,
	eSkilling = 50,
	eEnd
};

UCLASS()
class NP4_API ANP4PlayerState : public ANP4PlayerStateBase
{
	GENERATED_BODY()
	ANP4PlayerState();

	/* State를 소유한 케릭터 */
	ANP4PlayerBase* m_pStateOwner;

	/* 현재 케릭터의 state */
	eCharacterState m_ePlayerState;
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

public:
	UFUNCTION()
	void SetStateOwner(ANP4PlayerBase* _pOwner);
	void SetPlayerState(eCharacterState _State);

	/* Get */
	eCharacterState GetPlayerState();
	AActor* GetStateOwner();

};
