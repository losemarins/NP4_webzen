#include "Define.generated.h"

#pragma once

// 게임의 진영 
UENUM()
namespace EGameTeam
{
	enum Type
	{
		Unknown,
		Player,
		Enemy,
		MAX
	};
}

// 게임의 난이도
UENUM()
namespace EGameDifficulty
{
	enum Type
	{
		Easy,
		Medium,
		Hard,
	};
}
// 게임의 진행중인 상태
namespace EGameplayState
{
	enum Type
	{
		Waiting,
		Playing,
		Finished,
	};
}

// 게임의 맵 
namespace EGameMapState
{
	enum Type
	{
		Town,
		Stage1,
	};
}

// 플레이어의 데이터
struct FPlayerData
{
	/** current resources */
	uint32 ResourcesAvailable;

	/** total resources gathered */
	uint32 ResourcesGathered;

	/** total damage done */
	uint32 DamageDone;

	//각 진영의 최종건물
	TWeakObjectPtr<class ABuilding_Castle> Castle;
	///** HQ */
	//TWeakObjectPtr<class AStrategyBuilding_Brewery> Brewery;

	///** player owned buildings list */
	TArray<TWeakObjectPtr<class AActor>> BuildingsList;
};

// 게임 내의 키 타입
namespace EGameKey
{
	enum Type
	{
		Tap,
		Hold,
		Swipe,
		SwipeTwoPoints,
		Pinch,
	};
}

// 보스몬스터의 애니메이션 타입

namespace EBossAnim
{
	enum Type
	{
		Idle,
		Walk,
		Run,
		Attack,
		Skill,
		Hit,
		Die,
	};
}
