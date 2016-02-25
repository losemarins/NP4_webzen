#include "Engine.h"
#include "Define.generated.h"

#pragma once

UENUM()
enum class eItemID : uint8
{
	BlackTwoHandSword = 1,
	WhiteAxe = 2
};

namespace EMinionUpgrade
{
	enum Type
	{
		KnightLevel,
		MagicianLevel,
		ArchorLevel,
	};
}
namespace EMinion
{
	enum Type
	{
		Knight,
		Magician,
		Archor,
	};
}
UENUM()
enum class EGameStrategy : uint8

{
	Defualt,
	Converging_Attack,
	Indian_File,
};

UENUM(BlueprintType)
namespace EBuilding
{
	enum Type
	{
		Defualt,
		Barrack,
		Laboratory,
		HeroManagement,
	};
}

// Color
namespace EColor
{
	enum Type
	{
		Red,
		Green,
		Original,
	};
}

//Tile
const int TileSizeX = 1280	;
const int TileSizeY = 1110;
const int TileX = 6;
const int TileY = 6;
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

//2016-02-13 강민욱 수정
/* Enum Value */ 
UENUM()
enum class ECameraValue
{
	eStartCamera = -1,
	eDefulatCamera = 0,
	eAction_1 = 1,
	eAction_2 = 2,
	eTownCamera =10,
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
//#define GetMeshLoadManager() ANP4MeshLoadManager::StaticClass()

/* Animation Path */

//MainPlayer_ Animation_BP
#define MainPlayer_Mesh_PATH "SkeletalMesh'/Game/Characters/MainPlayer/InfinityBladeWarriors/Character/After/Kachujin_G_Rosales_Maya.Kachujin_G_Rosales_Maya'"
#define MainPlayer_Animation_BP_PATH "AnimBlueprint'/Game/BluePrint/MainPlayerAnimBlueprint.MainPlayerAnimBlueprint'"

//Animation Montage_BP
/* 1. NoWeapon */
#define MainPlayer_Mon_BASE_Idle1_PATH "AnimMontage'/Game/Characters/MainPlayer/InfinityBladeWarriors/Character/CompleteCharacters/Montage/BaseTest/MainPlayer_Mon_BASE_Idle1.MainPlayer_Mon_BASE_Idle1'"
#define MainPlayer_Mon_BASE_Walk_PATH "AnimMontage'/Game/Characters/MainPlayer/InfinityBladeWarriors/Character/CompleteCharacters/Montage/BaseTest/MainPlayer_Mon_BASE_Walk.MainPlayer_Mon_BASE_Walk'"
#define MainPlayer_Mon_BASE_Run_PATH "AnimMontage'/Game/Characters/MainPlayer/InfinityBladeWarriors/Character/CompleteCharacters/Montage/BaseTest/MainPlayer_Mon_BASE_Run.MainPlayer_Mon_BASE_Run'"
#define MainPlayer_Mon_BASE_Punch_PATH "AnimMontage'/Game/Characters/MainPlayer/InfinityBladeWarriors/Character/CompleteCharacters/Montage/BaseTest/MainPlayer_Mon_BASE_Punch.MainPlayer_Mon_BASE_Punch'"
#define MainPlayer_Mon_BASE_Punch2_PATH "AnimMontage'/Game/Characters/MainPlayer/InfinityBladeWarriors/Character/CompleteCharacters/Montage/BaseTest/MainPlayer_Mon_BASE_Punch2.MainPlayer_Mon_BASE_Punch2'	"
#define MainPlayer_Mon_BASE_Kick_PATH "AnimMontage'/Game/Characters/MainPlayer/InfinityBladeWarriors/Character/CompleteCharacters/Montage/BaseTest/MainPlayer_Mon_BASE_Kick.MainPlayer_Mon_BASE_Kick'"
#define MainPlayer_Mon_BASE_Hit_PATH "AnimMontage'/Game/Characters/MainPlayer/InfinityBladeWarriors/Character/CompleteCharacters/Montage/BaseTest/MainPlayer_Mon_BASE_Hit.MainPlayer_Mon_BASE_Hit'"


#define MainPlayer_Mon_BASE_Death_PATH "AnimMontage'/Game/Characters/MainPlayer/InfinityBladeWarriors/Character/CompleteCharacters/Montage/BaseTest/MainPlayer_Mon_BASE_Death.MainPlayer_Mon_BASE_Death'"
#define MainPlayer_Mon_BASE_FrontSpell_PATH "AnimMontage'/Game/Characters/MainPlayer/InfinityBladeWarriors/Character/CompleteCharacters/Montage/BaseTest/MainPlayer_Mon_BASE_FrontSpell.MainPlayer_Mon_BASE_FrontSpell'"
#define MainPlayer_Mon_BASE_UpSpell_PATH "AnimMontage'/Game/Characters/MainPlayer/InfinityBladeWarriors/Character/CompleteCharacters/Montage/BaseTest/MainPlayer_Mon_BASE_UpSpell.MainPlayer_Mon_BASE_UpSpell'"
#define MainPlayer_Mon_BASE_ForceSpell_PATH "AnimMontage'/Game/Characters/MainPlayer/InfinityBladeWarriors/Character/CompleteCharacters/Montage/BaseTest/MainPlayer_Mon_BASE_Hit.MainPlayer_Mon_BASE_Hit'"


/* 2. TwoHandSword */
#define MainPlayer_Mon_TwoHand_Idle1_PATH "AnimMontage'/Game/Characters/MainPlayer/InfinityBladeWarriors/Character/CompleteCharacters/Montage/TwoHandTest/MainPlayer_Mon_TwoHand_Idle.MainPlayer_Mon_TwoHand_Idle'"
#define MainPlayer_Mon_TwoHand_Idle2_PATH "AnimMontage'/Game/Characters/MainPlayer/InfinityBladeWarriors/Character/CompleteCharacters/Montage/TwoHandTest/MainPlayer_Mon_TwoHand_Idle2.MainPlayer_Mon_TwoHand_Idle2'"
#define MainPlayer_Mon_TwoHand_Walk_PATH "AnimMontage'/Game/Characters/MainPlayer/InfinityBladeWarriors/Character/CompleteCharacters/Montage/TwoHandTest/MainPlayer_Mon_TwoHand_Walk.MainPlayer_Mon_TwoHand_Walk'"
#define MainPlayer_Mon_TwoHand_Run_PATH "AnimMontage'/Game/Characters/MainPlayer/InfinityBladeWarriors/Character/CompleteCharacters/Montage/TwoHandTest/MainPlayer_Mon_TwoHand_Run.MainPlayer_Mon_TwoHand_Run'"
#define MainPlayer_Mon_TwoHand_Attack_PATH "AnimMontage'/Game/Characters/MainPlayer/InfinityBladeWarriors/Character/CompleteCharacters/Montage/TwoHandTest/MainPlayer_Mon_TwoHand_Attack.MainPlayer_Mon_TwoHand_Attack'"
#define MainPlayer_Mon_TwoHand_Hit_PATH "AnimMontage'/Game/Characters/MainPlayer/InfinityBladeWarriors/Character/CompleteCharacters/Montage/TwoHandTest/MainPlayer_Mon_TwoHand_Hit.MainPlayer_Mon_TwoHand_Hit'"
#define MainPlayer_Mon_TwoHand_CastingEarthQuake_PATH "AnimMontage'/Game/Characters/MainPlayer/InfinityBladeWarriors/Character/CompleteCharacters/Montage/TwoHandTest/MainPlayer_Mon_TwoHand_CastingEarthQuake.MainPlayer_Mon_TwoHand_CastingEarthQuake'"
#define MainPlayer_Mon_TwoHand_SpinAttack_PATH "AnimMontage'/Game/Characters/MainPlayer/InfinityBladeWarriors/Character/CompleteCharacters/Montage/TwoHandTest/MainPlayer_Mon_TwoHand_SpinAttack.MainPlayer_Mon_TwoHand_SpinAttack'"
#define MainPlayer_Mon_TwoHand_TurnAttack_PATH "AnimMontage'/Game/Characters/MainPlayer/InfinityBladeWarriors/Character/CompleteCharacters/Montage/TwoHandTest/MainPlayer_Mon_TwoHand_TurnAttack.MainPlayer_Mon_TwoHand_TurnAttack'"
#define MainPlayer_Mon_TwoHand_DownAttack_PATH "AnimMontage'/Game/Characters/MainPlayer/InfinityBladeWarriors/Character/CompleteCharacters/Montage/TwoHandTest/MainPlayer_Mon_TwoHand_DownAttack.MainPlayer_Mon_TwoHand_DownAttack'"
#define MainPlayer_Mon_TwoHand_Kick_PATH "AnimMontage'/Game/Characters/MainPlayer/InfinityBladeWarriors/Character/CompleteCharacters/Montage/TwoHandTest/MainPlayer_Mon_TwoHand_Kick.MainPlayer_Mon_TwoHand_Kick'"
#define MainPlayer_Mon_TwoHand_Draw_PATH "AnimMontage'/Game/Characters/MainPlayer/InfinityBladeWarriors/Character/CompleteCharacters/Montage/TwoHandTest/MainPlayer_Mon_TwoHand_Draw.MainPlayer_Mon_TwoHand_Draw'"
#define MainPlayer_Mon_TwoHand_Sheath_PATH "AnimMontage'/Game/Characters/MainPlayer/InfinityBladeWarriors/Character/CompleteCharacters/Montage/TwoHandTest/MainPlayer_Mon_TwoHand_Sheath.MainPlayer_Mon_TwoHand_Sheath'"

#define MainPlayer_Mon_TwoHand_ComboAttack_PATH "/Game/AnimationMontage/MainPlayer/MainPlayer_Mon_TwoHand_ComboAttack.MainPlayer_Mon_TwoHand_ComboAttack"
#define MainPlayer_Mon_TwoHand_Death_PATH "/Game/AnimationMontage/MainPlayer/MainPlayer_Mon_TwoHand_Death.MainPlayer_Mon_TwoHand_Death"
#define MainPlayer_Mon_TwoHand_SpellCast_PATH "AnimMontage'/Game/Characters/MainPlayer/InfinityBladeWarriors/Character/CompleteCharacters/Montage/TwoHandMon/MainPlayer_Mon_TwoHand_SpellCast.MainPlayer_Mon_TwoHand_SpellCast'"

#define MainPlayer_Mon_TwoHand_Jump_PATH "/Game/AnimationMontage/MainPlayer/MainPlayer_Mon_TwoHand_Jump.MainPlayer_Mon_TwoHand_Jump"
#define MainPlayer_Mon_TwoHand_JumpAttack_PATH "/Game/AnimationMontage/MainPlayer/MainPlayer_Mon_TwoHand_JumpAttack.MainPlayer_Mon_TwoHand_JumpAttack"
#define MainPlayer_Mon_TwoHand_PowerUp_PATH "/Game/AnimationMontage/MainPlaye/MainPlayer_Mon_TwoHand_PowerUp.MainPlayer_Mon_TwoHand_PowerUp"



/* 3. OneHandSword */
//2016-02-13 강민욱 수정 End
