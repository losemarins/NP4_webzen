// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "Building_Castle.h"
#include "AIDirector.h"
#include "NP4GameState.h"
ABuilding_Castle::ABuilding_Castle(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	AIDirector = CreateDefaultSubobject<UAIDirector>(TEXT("AIDirectorComp"));
	static ConstructorHelpers::FClassFinder<ANP4CharacterBase> BPClass(TEXT("/Game/Blueprint/Minion2"));
	CharClass = BPClass.Class;
}

void ABuilding_Castle::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	FPlayerData* const MyData = GetTeamData();
	if(MyData != nullptr)
		MyData->Castle = this;
}

void ABuilding_Castle::OnGameplayStateChange(EGameplayState::Type NewState)
{
	if (AIDirector != nullptr)
	{
		AIDirector->OnGameplayStateChange(NewState);
	}
}

void ABuilding_Castle::SetTeamNum(uint8 NewTeamNum)
{
	Super::SetTeamNum(NewTeamNum);

	if (AIDirector != nullptr)
	{
		AIDirector->SetTeamNum(MyTeamNum);

		//if (NewTeamNum == EStrategyTeam::Player)
		//	AIDirector->WaveSize = 0;
	}
}