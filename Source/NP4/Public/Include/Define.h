#include "Engine.h"
#include "Define.generated.h"

#pragma once

// ������ ���� 
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

// ������ ���̵�
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
// ������ �������� ����
namespace EGameplayState
{
	enum Type
	{
		Waiting,
		Playing,
		Finished,
	};
}

// ������ �� 
namespace EGameMapState
{
	enum Type
	{
		Town,
		Stage1,
	};
}

// �÷��̾��� ������
struct FPlayerData
{
	/** current resources */
	uint32 ResourcesAvailable;

	/** total resources gathered */
	uint32 ResourcesGathered;

	/** total damage done */
	uint32 DamageDone;

	//�� ������ �����ǹ�
	TWeakObjectPtr<class ABuilding_Castle> Castle;
	///** HQ */
	//TWeakObjectPtr<class AStrategyBuilding_Brewery> Brewery;

	///** player owned buildings list */
	TArray<TWeakObjectPtr<class AActor>> BuildingsList;
};

// ���� ���� Ű Ÿ��
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

// ���������� �ִϸ��̼� Ÿ��

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

//2016-02-13 ���ο� ����
/* Enum Value */ 
UENUM()
enum class ECameraValue
{
	eStartCamera = -1,
	eDefulatCamera = 0,
	eAction_1 = 1,
	eAction_2 = 2,
	eEndCamera
};

UENUM()
enum class eErrorType
{
	eSuccess = 1,
	eFailed = -1
};

/* Value */
#define CAMERA_ARR_MAX ECameraValue::eEndCamera
#define Animation_Montage_Failed -1.f

/* Define Fuctnion */
#define GetPlayerCameraManager() Cast<ANP4CameraManager>(GEngine->GetFirstLocalPlayerController(GetWorld())->PlayerCameraManager)
#define GetNP4PlayerController() (GEngine->GetFirstLocalPlayerController(GetWorld()))
//2016-02-13 ���ο� ���� End