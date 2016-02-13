// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "AIDirector.h"
#include "NP4GameState.h"
#include "Building_Castle.h"
#include "NP4CharacterBase.h"
// Sets default values for this component's properties
UAIDirector::UAIDirector() :
	MyTeamNum(EGameTeam::Unknown)
	, CustomScale(1.0)
	, ProductNum(0)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	
	// ...
}

// Called when the game starts
void UAIDirector::BeginPlay()
{
	Super::BeginPlay();
	if (EnemyBrewery == nullptr) // 목표지점 설정
	{
		const EGameTeam::Type EnemyTeamNum = (MyTeamNum == EGameTeam::Player ? EGameTeam::Enemy : EGameTeam::Player);
		const FPlayerData* const EnemyTeamData = GetWorld()->GetGameState<ANP4GameState>()->GetPlayerData(EnemyTeamNum);

		if (EnemyTeamData != nullptr && EnemyTeamData->Castle != nullptr)
		{
			EnemyBrewery = EnemyTeamData->Castle;
		}
	}
	// ...
}

// Called every frame
void UAIDirector::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	//나중에 수정해야댐
	SpawnMinions();
	// ...
}

void UAIDirector::SpawnMinions()
{
	if (ProductNum > 0)
	{
		const ABuilding_Castle* const Owner = Cast<ABuilding_Castle>(GetOwner());
		check(Owner);

		if (Owner->CharClass != nullptr)
		{
			FVector Loc = Owner->GetActorLocation();
			const FVector X = Owner->GetTransform().GetScaledAxis(EAxis::X);
			const FVector Y = Owner->GetTransform().GetScaledAxis(EAxis::Y);
			Loc += X + Y;

			const FVector Scale(CustomScale);
			FActorSpawnParameters SpawnInfo;
			SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			ANP4CharacterBase* const Char = GetWorld()->SpawnActor<ANP4CharacterBase>(Owner->CharClass, Loc, Owner->GetActorRotation(), SpawnInfo);

			if ((Char != nullptr))
			{
				Char->SetTeamNum(GetTeamNum());
				Char->SpawnDefaultController();
				ProductNum -= 1;
			}
		}
	}
}

void UAIDirector::RequestSpawn()
{
	ProductNum++;
}

void UAIDirector::OnGameplayStateChange(EGameplayState::Type NewState)
{
	if (NewState == EGameplayState::Playing)
	{
		Activate();
	}
}

uint8 UAIDirector::GetTeamNum() const
{
	return MyTeamNum;
}
