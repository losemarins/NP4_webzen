// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "AIDirector.h"
#include "NP4GameState.h"
#include "Building_Castle.h"
#include "NP4CharacterBase.h"
#include "Character_Minion.h"
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
	if (EnemyCastle == nullptr) // 목표지점 설정
	{
		const EGameTeam::Type EnemyTeamNum = (MyTeamNum == EGameTeam::Player ? EGameTeam::Enemy : EGameTeam::Player);
		const FPlayerData* const EnemyTeamData = GetWorld()->GetGameState<ANP4GameState>()->GetPlayerData(EnemyTeamNum);

		if (EnemyTeamData != nullptr && EnemyTeamData->Castle != nullptr)
		{
			EnemyCastle = EnemyTeamData->Castle;
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

			if (MyTeamNum == EGameTeam::Player)
				Loc += FVector(100, 100, 0);
				
			else
				Loc += FVector(-100, -100, 0);

			const FVector Scale(CustomScale);
			FActorSpawnParameters SpawnInfo;
			SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			ANP4CharacterBase* const SpawnChar = GetWorld()->SpawnActor<ANP4CharacterBase>(Owner->CharClass, Loc, Owner->GetActorRotation(), SpawnInfo);
			

			if ((SpawnChar != nullptr))
			{
				SpawnChar->SetTeamNum(MyTeamNum);
				SpawnChar->SpawnDefaultController();
				Cast<ACharacter_Minion>(SpawnChar)->SetCollisionChannel(MyTeamNum);
				Cast<ACharacter_Minion>(SpawnChar)->SetEnemyCastle(GetEnemyCastle());
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

ABuilding_Castle* UAIDirector::GetEnemyCastle() const
{
	return EnemyCastle.Get();
}

void UAIDirector::SetTeamNum(uint8 inTeamNum)
{
	MyTeamNum = inTeamNum;
}
