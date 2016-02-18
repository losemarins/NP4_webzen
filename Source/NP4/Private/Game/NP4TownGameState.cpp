// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "NP4TownGameState.h"
#include "HeroManagementBuilding.h"
#include "Tile.h"



ANP4TownGameState::ANP4TownGameState()
{
	ConstructorHelpers::FClassFinder<ATile> BPClass(TEXT("/Game/Blueprint/Tile_BP"));
	m_CharClass = BPClass.Class;
}



void ANP4TownGameState::SetGameDifficulty(EGameDifficulty::Type NewDifficulty)
{

}

void ANP4TownGameState::StartGameplayStateMachine()
{
	OnGameStart();
}

void ANP4TownGameState::OnGameStart()
{
	SetGameplayState(EGameplayState::Playing);
	InitTile();
	
}

void ANP4TownGameState::SetGameplayState(EGameplayState::Type NewState)
{
	GameplayState = NewState;
}

void ANP4TownGameState::SetGameMap(EGameMapState::Type NewState)
{
	GameMapState = NewState;
}

void ANP4TownGameState::InitTile()
{
	// Tile Size = 350;
	for (int y = -TileY; y < TileY; ++y)
	{
		for (int x = -TileX; x < TileX; ++x)
		{
			FVector Location;

			if (abs(y) % 2 == 0)
			{				
				Location = FVector(y * TileSizeY, x * TileSizeX, 0);
			}
			else
			{
				Location = FVector(y * TileSizeY, x * TileSizeX + TileSizeX /2, 0);
			}
			FRotator Rotation = FRotator(0, 0, 0);


			ATile* pTile = (ATile*)GetWorld()->SpawnActor(m_CharClass, &Location, &Rotation);
			m_TileArray.Add(pTile);
		}		
	}
}

void ANP4TownGameState::CreateBuilding(FVector SpawnPos, EBuilding::Type BuildingType)
{

	ABuilding* pBuilding = NULL;
	FVector Location = SpawnPos;
	Location.Z += 200;
	FRotator Rotation = FRotator(0, 90, 0);
	switch (BuildingType)
	{
	case EBuilding::Barrack:
		break;
	case EBuilding::HeroManagement:
		pBuilding = (AHeroManagementBuilding*)GetWorld()->SpawnActor(AHeroManagementBuilding::StaticClass(), &Location, &Rotation);
		break;
	case EBuilding::Laboratory:
		break;
	}

	m_BuildingArray.Add(pBuilding);
	
}
