// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "Building_Castle.h"
#include "AIDirector.h"
#include "NP4GameState.h"
ABuilding_Castle::ABuilding_Castle(const FObjectInitializer& ObjectInitializer)
{
	AIDirector = CreateDefaultSubobject<UAIDirector>(TEXT("AIDirectorComp"));
}

void ABuilding_Castle::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	FPlayerData* const MyData = GetTeamData();
	MyData->Castle = this;
}

void ABuilding_Castle::OnGameplayStateChange(EGameplayState::Type NewState)
{
	if (AIDirector != nullptr)
	{
		AIDirector->OnGameplayStateChange(NewState);
	}
}
