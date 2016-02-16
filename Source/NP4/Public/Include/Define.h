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

/* Animation Path */

//MainPlayer_ Animation_BP
#define MainPlayer_Mesh_PATH "SkeletalMesh '/Game/Characters/MainPlayer/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Golden.SK_CharM_Golden'"
#define MainPlayer_Animation_BP_PATH "AnimBlueprint'/Game/BluePrint/MainPlayerAnimBP.MainPlayerAnimBP'"

//Animation Montage_BP
/* 1. TwoHandSword */
#define MainPlayer_Mon_TwoHand_Attack_PATH "AnimMontage'/Game/Characters/MainPlayer/InfinityBladeWarriors/Character/CompleteCharacters/Montage/MainPlayer_Mon_TwoHand_Attack.MainPlayer_Mon_TwoHand_Attack'"
#define MainPlayer_Mon_TwoHand_CastingEarthQuake_PATH "/Game/AnimationMontage/MainPlayer/MainPlayer_Mon_TwoHand_CastingEarthQuake.MainPlayer_Mon_TwoHand_CastingEarthQuake"
#define MainPlayer_Mon_TwoHand_ComboAttack_PATH "/Game/AnimationMontage/MainPlayer/MainPlayer_Mon_TwoHand_ComboAttack.MainPlayer_Mon_TwoHand_ComboAttack"
#define MainPlayer_Mon_TwoHand_Death_PATH "/Game/AnimationMontage/MainPlayer/MainPlayer_Mon_TwoHand_Death.MainPlayer_Mon_TwoHand_Death"
#define MainPlayer_Mon_TwoHand_DownAttack_PATH "/Game/AnimationMontage/MainPlayer/MainPlayer_Mon_TwoHand_DownAttack.MainPlayer_Mon_TwoHand_DownAttack"
#define MainPlayer_Mon_TwoHand_Draw_PATH "/Game/AnimationMontage/MainPlayer/MainPlayer_Mon_TwoHand_Draw.MainPlayer_Mon_TwoHand_Draw"
#define MainPlayer_Mon_TwoHand_Hit_PATH "/Game/AnimationMontage/MainPlayer/MainPlayer_Mon_TwoHand_Hit.MainPlayer_Mon_TwoHand_Hit"
#define MainPlayer_Mon_TwoHand_Idle1_PATH "AnimMontage'/Game/Characters/MainPlayer/InfinityBladeWarriors/Character/CompleteCharacters/Montage/MainPlayer_Mon_TwoHand_Idle.MainPlayer_Mon_TwoHand_Idle'"
#define MainPlayer_Mon_TwoHand_Idle2_PATH "/Game/AnimationMontage/MainPlayer/MainPlayer_Mon_TwoHand_Idle2.MainPlayer_Mon_TwoHand_Idle2"
#define MainPlayer_Mon_TwoHand_Jump_PATH "/Game/AnimationMontage/MainPlayer/MainPlayer_Mon_TwoHand_Jump.MainPlayer_Mon_TwoHand_Jump"
#define MainPlayer_Mon_TwoHand_JumpAttack_PATH "/Game/AnimationMontage/MainPlayer/MainPlayer_Mon_TwoHand_JumpAttack.MainPlayer_Mon_TwoHand_JumpAttack"
#define MainPlayer_Mon_TwoHand_Kick_PATH "/Game/AnimationMontage/MainPlayer/MainPlayer_Mon_TwoHand_Kick.MainPlayer_Mon_TwoHand_Kick"
#define MainPlayer_Mon_TwoHand_PowerUp_PATH "/Game/AnimationMontage/MainPlaye/MainPlayer_Mon_TwoHand_PowerUp.MainPlayer_Mon_TwoHand_PowerUp"
#define MainPlayer_Mon_TwoHand_Run_PATH "AnimMontage'/Game/Characters/MainPlayer/InfinityBladeWarriors/Character/CompleteCharacters/Montage/MainPlayer_Mon_TwoHand_Run.MainPlayer_Mon_TwoHand_Run'"
#define MainPlayer_Mon_TwoHand_Sheath_PATH "/Game/AnimationMontage/MainPlayer/MainPlayer_Mon_TwoHand_Sheath.MainPlayer_Mon_TwoHand_Sheath"
#define MainPlayer_Mon_TwoHand_SpellCast_PATH "/Game/AnimationMontage/MainPlayer/MainPlayer_Mon_TwoHand_SpellCast.MainPlayer_Mon_TwoHand_SpellCast"
#define MainPlayer_Mon_TwoHand_SpinAttack_PATH "AnimMontage'/Game/Characters/MainPlayer/InfinityBladeWarriors/Character/CompleteCharacters/Montage/MainPlayer_Mon_TwoHand_SpinAttack.MainPlayer_Mon_TwoHand_SpinAttack'	"
#define MainPlayer_Mon_TwoHand_TurnAttack_PATH "/Game/AnimationMontage/MainPlayer/MainPlayer_Mon_TwoHand_TurnAttack.MainPlayer_Mon_TwoHand_TurnAttack"
#define MainPlayer_Mon_TwoHand_Walk_PATH "AnimMontage'/Game/Characters/MainPlayer/InfinityBladeWarriors/Character/CompleteCharacters/Montage/MainPlayer_Mon_TwoHand_Walk.MainPlayer_Mon_TwoHand_Walk'"
//2016-02-13 ���ο� ���� End

/** when you modify this, please note that this information can be saved with instances
* also DefaultEngine.ini [/Script/Engine.CollisionProfile] should match with this list  ����**/
#define COLLISION_BUILDING		ECC_GameTraceChannel1
#define COLLISION_PROJECTILE	ECC_GameTraceChannel2
#define COLLISION_PANCAMERA		ECC_GameTraceChannel3
