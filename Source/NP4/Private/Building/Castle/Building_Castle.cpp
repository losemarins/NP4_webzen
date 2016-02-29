// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "Building_Castle.h"
#include "AIDirector.h"
#include "NP4GameState.h"

ABuilding_Castle::ABuilding_Castle(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	AIDirector = CreateDefaultSubobject<UAIDirector>(TEXT("AIDirectorComp"));
	MeleeCollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("MeleeCollision"));
	MeshComp->AttachTo(RootComponent);
	MeleeCollisionComp->AttachTo(MeshComp);
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
	SetChannel(NewTeamNum);
	if (AIDirector != nullptr)
	{
		AIDirector->SetTeamNum(MyTeamNum);
		//if (NewTeamNum == EStrategyTeam::Player)
		//	AIDirector->WaveSize = 0;
	}
}

void ABuilding_Castle::SetChannel(uint8 TeamNum)
{
	if(TeamNum == EGameTeam::Player)
		MeleeCollisionComp->SetCollisionObjectType(ECollisionChannel::ECC_EngineTraceChannel2);
	
	else
		MeleeCollisionComp->SetCollisionObjectType(ECollisionChannel::ECC_EngineTraceChannel4);
}
