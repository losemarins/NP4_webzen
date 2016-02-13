// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "Define.h"
#include "NP4PlayerBase.h"
#include "NP4PlayerState.h"

ANP4PlayerState::ANP4PlayerState()
{
	PrimaryActorTick.bCanEverTick = true;

	m_ePlayerState = eCharacterState::eIdle;
}

void ANP4PlayerState::BeginPlay()
{
	Super::BeginPlay();
}

void ANP4PlayerState::Tick(float _DeltaSeconds)
{
	Super::Tick(_DeltaSeconds);
}

void ANP4PlayerState::SetPlayerState(eCharacterState _State)
{
	m_ePlayerState = _State;
}

void ANP4PlayerState::SetStateOwner(ANP4PlayerBase* _pOwner)
{
	if (!m_pStateOwner)
	{
		m_pStateOwner = _pOwner;
	}

	else
	{
		//Owner is Already.
	}
}

eCharacterState ANP4PlayerState::GetPlayerState()
{
	return m_ePlayerState;
}

AActor* ANP4PlayerState::GetStateOwner()
{
	return m_pStateOwner;
}


