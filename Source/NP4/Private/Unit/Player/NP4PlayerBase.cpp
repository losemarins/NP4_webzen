// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "NP4HeroController.h"
#include "NP4CameraActor.h"
#include "NP4PlayerBase.h"

// Sets default values
const FRotator ANP4PlayerBase::msBaseRotation(0, -90, 0);
const FVector ANP4PlayerBase::msBaseLocation(0, 0, -90);

ANP4PlayerBase::ANP4PlayerBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Spring Arm 세팅(부드러운 카메라 연출을 위해 사용)
	m_OurCameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	m_OurCameraSpringArm->bUsePawnControlRotation = true;
	m_OurCameraSpringArm->AttachTo(RootComponent);
	m_MaxSpringArmLength = 400.0f;
	m_MinSpringArmLength = 300.0f;

	////카메라 셋팅
	m_OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	m_OurCamera->AttachTo(m_OurCameraSpringArm, USpringArmComponent::SocketName);

	//케릭터 매쉬가 회전을 먹도록 Setting
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECR_Ignore);

	//Skeleton Mesh Setting
	USkeletalMeshComponent* pMesh = GetMesh();
	
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshLoadAsset(TEXT(MainPlayer_Mesh_PATH));
	if (MeshLoadAsset.Succeeded())
	{
		pMesh->SetSkeletalMesh(MeshLoadAsset.Object);
		pMesh->SetWorldScale3D(FVector(0.8f));
		pMesh->SetWorldRotation(GetControlRotation());
		pMesh->SetRelativeRotation(msBaseRotation);
		pMesh->SetRelativeLocation(msBaseLocation);
	}

	//Anmation BP Setting
	static ConstructorHelpers::FObjectFinder<UAnimBlueprint> lAnimBlueprint(TEXT(MainPlayer_Animation_BP_PATH));
	if (lAnimBlueprint.Succeeded())
	{
		static UClass* lAnimBlueprintClass = (UClass*)lAnimBlueprint.Object->GeneratedClass;

		pMesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		pMesh->SetAnimInstanceClass(lAnimBlueprintClass);
	}

	//AnimationMontage Initialize
	if(m_ArrAnimMontage.Num() <= 0)
		InitAnimationMontage();

	/* Combo Init */
	m_ComboStep = Combo_None;

	/* Create Hit Capsule Component */
	GetMesh()->BodyInstance.SetCollisionEnabled(ECollisionEnabled::NoCollision);

	MeleeCollisionComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MeleeCollision"));
	MeleeCollisionComp->AttachTo(RootComponent);
	MeleeCollisionComp->bHiddenInGame = false;
	MeleeCollisionComp->SetVisibility(true);

	MeleeCollisionComp->SetCollisionObjectType(ECollisionChannel::ECC_EngineTraceChannel2);
	MeleeCollisionComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	MeleeCollisionComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel1, ECollisionResponse::ECR_Ignore);
	MeleeCollisionComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel3, ECollisionResponse::ECR_Ignore);
	MeleeCollisionComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel4, ECollisionResponse::ECR_Overlap);

	/* Create Attack Capsule Component */
	//Left Punch
	m_pLeftPunchCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("LeftPunchCollision"));
	m_pLeftPunchCapsule->AttachTo(pMesh, "LeftHand");
	m_pLeftPunchCapsule->bHiddenInGame = false;
	m_pLeftPunchCapsule->SetVisibility(true);
	m_pLeftPunchCapsule->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	m_pLeftPunchCapsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//Right Punch
	m_pRightPunchCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("RightPunchCollision"));
	m_pRightPunchCapsule->AttachTo(pMesh, "RightHand");
	m_pRightPunchCapsule->bHiddenInGame = false;
	m_pRightPunchCapsule->SetVisibility(true);
	m_pRightPunchCapsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//Left Kick
	m_pLeftKickCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("LeftKickCollision"));
	m_pLeftKickCapsule->AttachTo(pMesh, "LeftFoot");
	m_pLeftKickCapsule->bHiddenInGame = false;
	m_pLeftKickCapsule->SetVisibility(true);

	////Right Kick
	//m_pRightKickCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("RightKickCollision"));
	//m_pRightKickCapsule->AttachTo(pMesh, "RightFoot");
	//m_pRightKickCapsule->bHiddenInGame = false;
	//m_pRightKickCapsule->SetVisibility(true);

	/* Set Team */
	MyTeamNum = EGameTeam::Player;
	
}

void ANP4PlayerBase::BeginPlay()
{
	Super::BeginPlay();

	if (IsPlayerControllerNull())
	{
		SetPlayerController(Cast<ANP4HeroController>(GetNP4PlayerController()));
	}

	/* 스프링암을 세팅된 값으로 기본 세팅한다. */
	FtCameraLocationInfo LocationInfo;
	if (!IsPlayerControllerNull())
	{
		eErrorType eType = m_pPlayerController->Request_GetDefaultCameraInfo(ECameraValue::eDefulatCamera, LocationInfo);

		if (eType == eErrorType::eSuccess)
		{
			SetSpringArm(LocationInfo);
			
			if (LocationInfo.bApplySpringArm)
			{
				SetSpringArmCameraRotation(LocationInfo.Rotation);
			}
			else
			{
				SetCameraRotaion(LocationInfo.Rotation);
			}
		}
	}

	/* PlayerState에게 Owner를 세팅한다.. */
	if (!m_pPlayerState)
	{
		m_pPlayerState = (Cast<ANP4PlayerState>(PlayerState));
		m_pPlayerState->SetStateOwner(this);
	}

	//임시로 무기를 인벤토리에 생성한다.
	Super::InitWeapon_TempFunction();
	m_AttackValue = 10;
}

void ANP4PlayerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckState(DeltaTime);
}

void ANP4PlayerBase::PossessedBy(AController* _pController)
{
	Super::PossessedBy(_pController);
	m_pPlayerController = Cast<ANP4HeroController>(_pController);
}

void ANP4PlayerBase::InitAnimationMontage()
{
	/* 순서는 FrameWorkPlayerState를 참조*/
	/* 스킬은 덧셈의 연산이 필요함(여러개의 모션이 있기 때문에 하나의 인덱스에 담을 수 없기 때문, 하지만 스테이트는 Skilling으로 같다. */

	m_ArrAnimMontage.Init(NULL, 100); /* 애니메이션몬티지 Init */

	eWeaponType weaponType = eWeaponType::eType_None;
	
	/* Weapon Type _ None*/
	////Idle
	m_ArrAnimMontage.Insert(FindAnimationMontage_byPath(TEXT(MainPlayer_Mon_BASE_Idle1_PATH)), (int)eCharacterState::eIdle + (int)weaponType);
	////Walk
	m_ArrAnimMontage.Insert(FindAnimationMontage_byPath(TEXT(MainPlayer_Mon_BASE_Walk_PATH)), (int)eCharacterState::eWalk + (int)weaponType);
	////Run
	m_ArrAnimMontage.Insert(FindAnimationMontage_byPath(TEXT(MainPlayer_Mon_BASE_Run_PATH)), (int)eCharacterState::eRun + (int)weaponType);
	////Attack
	m_ArrAnimMontage.Insert(FindAnimationMontage_byPath(TEXT(MainPlayer_Mon_BASE_Punch_PATH)), (int)eCharacterState::eAttack + (int)weaponType + (int)eCombo_Interpol::Combo_None);
	m_ArrAnimMontage.Insert(FindAnimationMontage_byPath(TEXT(MainPlayer_Mon_BASE_Punch2_PATH)), (int)eCharacterState::eAttack + (int)weaponType + (int)eCombo_Interpol::Combo_One);
	m_ArrAnimMontage.Insert(FindAnimationMontage_byPath(TEXT(MainPlayer_Mon_BASE_Kick_PATH)), (int)eCharacterState::eAttack + (int)weaponType + (int)eCombo_Interpol::Combo_Two);
	////HIT
	m_ArrAnimMontage.Insert(FindAnimationMontage_byPath(TEXT(MainPlayer_Mon_BASE_Hit_PATH)), (int)eCharacterState::eHit + (int)weaponType);
	////Skill_1
	m_ArrAnimMontage.Insert(FindAnimationMontage_byPath(TEXT(MainPlayer_Mon_BASE_FrontSpell_PATH)), (int)eCharacterState::eSkilling + (int)eAnimMontage_Skill_Interpol::eSkill_1 + (int)weaponType);
	////Skill_2
	m_ArrAnimMontage.Insert(FindAnimationMontage_byPath(TEXT(MainPlayer_Mon_BASE_UpSpell_PATH)), (int)eCharacterState::eSkilling + (int)eAnimMontage_Skill_Interpol::eSkill_2 + (int)weaponType);

	weaponType = eWeaponType::eType_1;
	/* Weapon Type _ 1 */
	////Idle
	m_ArrAnimMontage.Insert(FindAnimationMontage_byPath(TEXT(MainPlayer_Mon_TwoHand_Idle1_PATH)), (int)eCharacterState::eIdle + (int)weaponType);
	////Walk
	m_ArrAnimMontage.Insert(FindAnimationMontage_byPath(TEXT(MainPlayer_Mon_TwoHand_Walk_PATH)), (int)eCharacterState::eWalk + (int)weaponType);
	////Run
	m_ArrAnimMontage.Insert(FindAnimationMontage_byPath(TEXT(MainPlayer_Mon_TwoHand_Run_PATH)), (int)eCharacterState::eRun + (int)weaponType);
	////Attack
	m_ArrAnimMontage.Insert(FindAnimationMontage_byPath(TEXT(MainPlayer_Mon_TwoHand_Attack_PATH)), (int)eCharacterState::eAttack + (int)weaponType + (int)eCombo_Interpol::Combo_None);
	m_ArrAnimMontage.Insert(FindAnimationMontage_byPath(TEXT(MainPlayer_Mon_TwoHand_DownAttack_PATH)), (int)eCharacterState::eAttack + (int)weaponType + (int)eCombo_Interpol::Combo_One);
	m_ArrAnimMontage.Insert(FindAnimationMontage_byPath(TEXT(MainPlayer_Mon_TwoHand_Kick_PATH)), (int)eCharacterState::eAttack + (int)weaponType + (int)eCombo_Interpol::Combo_Two);
	////HIT
	m_ArrAnimMontage.Insert(FindAnimationMontage_byPath(TEXT(MainPlayer_Mon_TwoHand_Hit_PATH)), (int)eCharacterState::eHit + (int)weaponType);
	////Skill_1
	m_ArrAnimMontage.Insert(FindAnimationMontage_byPath(TEXT(MainPlayer_Mon_TwoHand_CastingEarthQuake_PATH)), (int)eCharacterState::eSkilling + (int)eAnimMontage_Skill_Interpol::eSkill_1 + (int)weaponType);
	////Skill_2
	m_ArrAnimMontage.Insert(FindAnimationMontage_byPath(TEXT(MainPlayer_Mon_TwoHand_TurnAttack_PATH)), (int)eCharacterState::eSkilling + (int)eAnimMontage_Skill_Interpol::eSkill_2 + (int)weaponType);
	////Draw Weapon ->칼 넣기
	m_ArrAnimMontage.Insert(FindAnimationMontage_byPath(TEXT(MainPlayer_Mon_TwoHand_Draw_PATH)), (int)eCharacterState::eSkilling + (int)eAnimMontage_Skill_Interpol::eDrawWeapon + (int)weaponType);
	////Sheath Weapon ->칼 빼기
	m_ArrAnimMontage.Insert(FindAnimationMontage_byPath(TEXT(MainPlayer_Mon_TwoHand_Sheath_PATH)), (int)eCharacterState::eSkilling + (int)eAnimMontage_Skill_Interpol::eSheathWeapon + (int)weaponType);
}

void ANP4PlayerBase::SetPlayerController(ANP4HeroController* _pPlayerController)
{
	if (IsPlayerControllerNull())
	{
		m_pPlayerController = _pPlayerController;
	}
}

void ANP4PlayerBase::SetSpringArm(FtCameraLocationInfo _Info)
{
	m_OurCameraSpringArm->SetRelativeLocation(_Info.Location);

	if (_Info.Init_ArmLength > _Info.Max_ArmLength)
	{
		_Info.Init_ArmLength = _Info.Max_ArmLength;
	}

	m_OurCameraSpringArm->TargetArmLength = _Info.Init_ArmLength;

	if (_Info.Max_ArmLength > _Info.Min_ArmLength)
	{
		if (_Info.Max_ArmLength != 0.f)
		{
			m_MaxSpringArmLength = _Info.Max_ArmLength;
		}
		m_MinSpringArmLength = _Info.Min_ArmLength;
	}
}

void ANP4PlayerBase::SetSpringArmCameraRotation(FRotator _Rot)
{
	m_OurCameraSpringArm->SetRelativeRotation(_Rot);
}

void ANP4PlayerBase::SetCameraRotaion(FRotator _Rot)
{
	m_OurCamera->SetRelativeRotation(_Rot);
}

UAnimMontage* ANP4PlayerBase::GetAnimationMontage_fromArrMontage(eCharacterState _eState, eAnimMontage_Skill_Interpol _eSkill_Interpolation)
{
	if (m_ArrAnimMontage.Num() <= (int)_eState + (int)_eSkill_Interpolation )
	{
		return NULL;
	}

	return (m_ArrAnimMontage)[(int)_eState + (int)_eSkill_Interpolation];
}

UAnimMontage* ANP4PlayerBase::GetAnimationMontage_fromArrMontage(int _idex)
{
	if (m_ArrAnimMontage.Num() <= _idex)
	{
		return NULL;
	}

	return (m_ArrAnimMontage)[_idex];
}

bool ANP4PlayerBase::IsPlayerControllerNull()
{
	return m_pPlayerController == NULL ? true : false;
}

UAnimMontage* ANP4PlayerBase::FindAnimationMontage_byPath(const TCHAR* _ObjectToFindPath)
{
	ConstructorHelpers::FObjectFinder<UAnimMontage> MontageLoadAsset(_ObjectToFindPath);
	if (MontageLoadAsset.Succeeded())
		return MontageLoadAsset.Object;

	else
		return NULL;
}

void ANP4PlayerBase::SetDefaultCameraActive()
{
	if (m_pPlayerController)
		m_pPlayerController->SetViewTargetWithBlend(m_OurCameraSpringArm->GetOwner(), 0.75f);
}

void ANP4PlayerBase::ZoomTickFunc(float _DeltaTime, bool _bZoomIn)
{
	//카메라 줌인,줌아웃
	if (_bZoomIn)
	{
		m_ZoomFactor += _DeltaTime / 0.9f;         //0.5 초에 걸쳐 줌인
	}
	else
	{
		m_ZoomFactor -= _DeltaTime / 0.25f;        //0.25 초에 걸쳐 줌아웃
	}

	m_ZoomFactor = FMath::Clamp<float>(m_ZoomFactor, 0.0f, 1.0f);
	m_OurCamera->FieldOfView = FMath::Lerp<float>(90.0f, 60.0f, m_ZoomFactor);
	m_OurCameraSpringArm->TargetArmLength = FMath::Lerp<float>(m_MaxSpringArmLength, m_MinSpringArmLength, m_ZoomFactor);
}

void ANP4PlayerBase::Request_MakeActionCamera(ECameraValue _CameraValue, AActor* _pBaseObject, float _AnimDurationVal)
{
	/* 액션카메라를 만든다.. */
	ANP4CameraActor* pSpawnActor = NULL;
	if (!m_pPlayerController->IsCameraMangerNull() || _AnimDurationVal != 0.f)
	{
		pSpawnActor = m_pPlayerController->Request_MakeActionCamera(_CameraValue, this);

		if (!pSpawnActor)
		{
			return;
		}

		else
		{
			/* 에디터에서 세팅한 블랜드 값으로 하겠는가? */
			if (pSpawnActor->GetActionCameraBlendSpeedByEditor() ||
				pSpawnActor->GetActionCameraBlendSpeed() == 0.0f)
			{
				/* 안할 경우 Duration / 2 값으로 세팅한다. */
				pSpawnActor->SetCameraBleendSpeed(_AnimDurationVal / 2);
			}

			if (pSpawnActor->GetActionCameraNextCameraTime() == 0.0f)
			{
				/* 안되어 있을 경우 Duration 값으로 세팅한다. */
				pSpawnActor->SetCameraNextCamSpeed(_AnimDurationVal);
			}

			m_pPlayerController->Push_ActionCameraArray(pSpawnActor);
			m_pPlayerController->DoActionCamera();
		}
	}

	else
	{
		//CameraArray is not Empty
		int a = 10;
	}
}

void ANP4PlayerBase::CheckState(float _Deltatime)
{
	UAnimMontage* ExeAnimMontage = NULL;
	eCharacterState ExeAnimMontage_Type = eCharacterState::eEnd;
	float ReturnValue = Animation_Montage_Failed;
	eWeaponType iWeaponType = GetCurrentWeapon() == NULL ? eWeaponType::eType_None : GetCurrentWeapon()->GetWeaponType();
	eCharacterState CurState = m_pPlayerState->GetPlayerState();


	if (IsSomeAction())
	{
		return;
	}

	
	else if (IsWalking())
	{
		if(CurState == eCharacterState::eRun)
		{
			ExeAnimMontage = (m_ArrAnimMontage)[eCharacterState::eRun + (int)iWeaponType];
			ExeAnimMontage_Type = eCharacterState::eRun;
		}

		else
		{
			/* Change State */
			if(m_pPlayerState)
				m_pPlayerState->SetPlayerState(eCharacterState::eWalk);
			/* Change Speed */
			if (GetCharacterMovement())
				GetCharacterMovement()->MaxWalkSpeed = 150;

			ExeAnimMontage = (m_ArrAnimMontage)[eCharacterState::eWalk + (int)iWeaponType];
			ExeAnimMontage_Type = eCharacterState::eWalk;
		}
	}

	else if (CurState == eCharacterState::eRun)
	{
		ExeAnimMontage = (m_ArrAnimMontage)[eCharacterState::eRun + (int)iWeaponType];
		ExeAnimMontage_Type = eCharacterState::eRun;
	}

	/* Execution Montage Anim */
	if (ExeAnimMontage && ExeAnimMontage_Type != eCharacterState::eEnd)
		ReturnValue = PlayAnimMontage_CheckCurrent(ExeAnimMontage, ExeAnimMontage_Type);

	/* Is Succees change Montage Anim ? */
	if (ReturnValue != Animation_Montage_Failed)
		return;

	/* EntryPoint */
	else if (PlayAnimMontage_CheckCurrent((m_ArrAnimMontage)[eCharacterState::eIdle + (int)iWeaponType], eCharacterState::eIdle) != Animation_Montage_Failed)
	{
		if(m_pPlayerState)
			m_pPlayerState->SetPlayerState(eCharacterState::eIdle);
		return;
	}
}

bool ANP4PlayerBase::IsWalking()
{
	if (!GetCharacterMovement())
		return false;

	if (IsSomeAction())
	{
		return false;
	}

	/*
	GetVelocity().IsZero() : 속도가 0인가?
	GetVelocity().GetSafeNormal2D() : 정규화(노말라이즈)하기에 너무 작은 값이면 Zero Vector의 값을 리턴한다.
	GetActorForwardVector() : Actor의 전진 백터를 리턴한다.
	*/
	return !GetVelocity().IsZero() && ((GetVelocity().GetSafeNormal2D() | GetActorForwardVector()) > -0.1);
}

bool ANP4PlayerBase::IsSomeAction()
{
	if (!m_pPlayerState)
		return false;

	eCharacterState CurState = m_pPlayerState->GetPlayerState();

	if (CurState == eCharacterState::eAttack ||
		CurState == eCharacterState::eHit ||
		CurState == eCharacterState::eSkilling)
	{
		return true;
	}

	return false;
}

//////////////////////////////////////////////////* Character Action */
void ANP4PlayerBase::StartRunning()
{
	if (IsSomeAction())
	{
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, FString::Printf(TEXT("Run")));
	//SetRunning(true);
	
	/* Change State */
	if(m_pPlayerState)
		m_pPlayerState->SetPlayerState(eCharacterState::eRun);

	/* Change Speed */
	if (GetCharacterMovement())
		GetCharacterMovement()->MaxWalkSpeed = 600;
}

void ANP4PlayerBase::StopRunning()
{
	//SetRunning(false);
	if (m_pPlayerState)
		m_pPlayerState->SetPlayerState(eCharacterState::eNone);
}


void ANP4PlayerBase::ActionAttack()
{
	eCharacterState CurState = m_pPlayerState->GetPlayerState();

	if (CurState != eCharacterState::eAttack &&
		CurState != eCharacterState::eHit &&
		CurState != eCharacterState::eSkilling)
	{
		eWeaponType iWeaponType = GetCurrentWeapon() == NULL ? eWeaponType::eType_None : GetCurrentWeapon()->GetWeaponType();
		float fAnimDuationVal = 0.0f;
		//SetRunning(false);

		UAnimMontage* pAttackAnim = NULL;
		pAttackAnim = (m_ArrAnimMontage)[eCharacterState::eAttack + (int)iWeaponType];;

		if (pAttackAnim)
		{
			fAnimDuationVal = PlayAnimMontage_CheckCurrent(pAttackAnim, eCharacterState::eAttack);
			if(m_pPlayerState)
				m_pPlayerState->SetPlayerState(eCharacterState::eAttack);

			//Request_MakeActionCamera(ECameraValue::eAction_1, this, fAnimDuationVal);

			///* Collision Active */
			//if(m_pCurrentEquipWeapon)
			//	Super::SetColliderEnabled(true);

			//else
			//{
				//SetColliderEnabled(true);
			//}
		}


		else
		{
			//Hit Motion Animation is not vaild
		}
	}

	////Combo System
	else if (m_bComboNotifyEnter && CurState == eCharacterState::eAttack)
	{
		m_bComboClkOn = true;
	}
}

void ANP4PlayerBase::StopAttack()
{
	eWeaponType iWeaponType = GetCurrentWeapon() == NULL ? eWeaponType::eType_None : GetCurrentWeapon()->GetWeaponType();
	UAnimMontage* pAttackAnim = NULL;
	pAttackAnim = pAttackAnim = (m_ArrAnimMontage)[eCharacterState::eAttack + (int)iWeaponType + (int)m_ComboStep];;

	if (pAttackAnim)
	{
		StopNP4AnimationMontage(pAttackAnim);
		m_pPlayerState->SetPlayerState(eCharacterState::eNone);
		m_bComboClkOn = false;
		m_ComboStep = eCombo_Interpol::Combo_None;

		/* Collision no Active */
		//Super::SetColliderEnabled(false);
	}

	else
	{
		//Hit Motion Animation is not vaild
	}
}


void ANP4PlayerBase::ActionHit(FVector _Dir)
{
	eWeaponType iWeaponType = GetCurrentWeapon() == NULL ? eWeaponType::eType_None : GetCurrentWeapon()->GetWeaponType();
	
	eCharacterState CurState = m_pPlayerState->GetPlayerState();

	if (CurState != eCharacterState::eHit &&
		CurState != eCharacterState::eSkilling)
	{
		UAnimMontage* pHitAnim = NULL;
		pHitAnim = (m_ArrAnimMontage)[eCharacterState::eHit + (int)iWeaponType];;

		if (pHitAnim)
		{
			PlayAnimMontage_CheckCurrent(pHitAnim, eCharacterState::eHit);
		//	SetHit(true);
			if (m_pPlayerState)
				m_pPlayerState->SetPlayerState(eCharacterState::eHit);

		}

		else
		{
			//Hit Motion Animation is not vaild
		}
	}
}

void ANP4PlayerBase::StopHit()
{
	eWeaponType iWeaponType = GetCurrentWeapon() == NULL ? eWeaponType::eType_None : GetCurrentWeapon()->GetWeaponType();
	UAnimMontage* pHitAnim = NULL;
	pHitAnim = (m_ArrAnimMontage)[eCharacterState::eHit + (int)iWeaponType];;

	if (pHitAnim)
	{
		StopNP4AnimationMontage(pHitAnim);
		m_pPlayerState->SetPlayerState(eCharacterState::eNone);
	}

	else
	{
		//Hit Motion Animation is not vaild
	}
}

void ANP4PlayerBase::ActionSkill_1()
{
	eWeaponType iWeaponType = GetCurrentWeapon() == NULL ? eWeaponType::eType_None : GetCurrentWeapon()->GetWeaponType();
	UAnimMontage* pSkill_1_Anim = NULL;
	pSkill_1_Anim = (m_ArrAnimMontage)[eCharacterState::eSkilling + eAnimMontage_Skill_Interpol::eSkill_1 + (int)iWeaponType];;
	eCharacterState CurState = m_pPlayerState->GetPlayerState();

	if (pSkill_1_Anim && CurState != eCharacterState::eSkilling && CurState != eCharacterState::eAttack)
	{
		float fAnimDuationVal = 0.0f;
		//GetMesh()->AnimScriptInstance->Montage_Stop(0.0f); /* Stop All Montage Anim */
		fAnimDuationVal = PlayAnimMontage_CheckCurrent(pSkill_1_Anim, eCharacterState::eSkilling);
		if(m_pPlayerState)
			m_pPlayerState->SetPlayerState(eCharacterState::eSkilling);

	}
}

void ANP4PlayerBase::ActionSkill_2()
{
	eWeaponType iWeaponType = GetCurrentWeapon() == NULL ? eWeaponType::eType_None : GetCurrentWeapon()->GetWeaponType();
	UAnimMontage* pSkill_2_Anim = NULL;
	pSkill_2_Anim = (m_ArrAnimMontage)[eCharacterState::eSkilling + eAnimMontage_Skill_Interpol::eSkill_2 + (int)iWeaponType];;
	eCharacterState CurState = m_pPlayerState->GetPlayerState();

	if (pSkill_2_Anim && CurState != eCharacterState::eSkilling && CurState != eCharacterState::eAttack)
	{
		//GetMesh()->AnimScriptInstance->Montage_Stop(0.0f); /* Stop All Montage Anim */
		PlayAnimMontage_CheckCurrent(pSkill_2_Anim, eCharacterState::eSkilling);
		if(m_pPlayerState)
			m_pPlayerState->SetPlayerState(eCharacterState::eSkilling);

	}
}

void ANP4PlayerBase::StopSkill(UAnimMontage* _pSkillAnim)
{
	StopNP4AnimationMontage(_pSkillAnim);
	//SetSkilling(false);
	m_pPlayerState->SetPlayerState(eCharacterState::eNone);
}

/* 칼 넣기(해제) */
float ANP4PlayerBase::DrawWeapon()
{
	float fDrawAnimDuation = 0.0f;
	/* 끼고 있는 무기가 없으면 의미가 없다. */

	eCharacterState CurState = m_pPlayerState->GetPlayerState();

	if(!m_pCurrentEquipWeapon || CurState == eCharacterState::eSkilling || CurState == eCharacterState::eAttack)
	{
		/* 이미 어떠한 행동 중이다(해제중 포함) */
		/* 주희에게 에러 메세지를 돌려보내줘야 한다(0을 리턴했을 경우, 메세지를 띄우게 하자) */
		/* 지금은 할 수 없습니다. 라는 메시지 같은? */
		return fDrawAnimDuation;
	}
		

	/* 끼고 있는 무기가 있다. */
	eWeaponType iWeaponType = GetCurrentWeapon()->GetWeaponType();
	
	UAnimMontage* pDraw_Anim = NULL;
	pDraw_Anim = (m_ArrAnimMontage)[eCharacterState::eSkilling + eAnimMontage_Skill_Interpol::eDrawWeapon + (int)iWeaponType];;

	if (pDraw_Anim)
	{
		///GetMesh()->AnimScriptInstance->Montage_Stop(0.0f); /* Stop All Montage Anim */
		fDrawAnimDuation = PlayAnimMontage_CheckCurrent(pDraw_Anim, eCharacterState::eSkilling);
		if (m_pPlayerState)
			m_pPlayerState->SetPlayerState(eCharacterState::eSkilling);
	}

	return fDrawAnimDuation;
}

void ANP4PlayerBase::TempSheathWeapon()
{
	if (tempidx >= 1) //무기 개수는 3개.
	{
		tempidx = 0;
	}
	else
		++tempidx;

	SheathWeapon(tempidx); /* 실제로는 주희 UMG에서 선택한 아이템의 번호를 넘겨준다. */
}

/* 칼 빼기 */
void ANP4PlayerBase::SheathWeapon(int32 _InvenIdx)
{
	eCharacterState CurState = m_pPlayerState->GetPlayerState();

	/* 어떠한 행동 중 체크와, 인벤토리 범위 체크를 한다..*/
	if (!CheckIndex_inInventory(_InvenIdx) || CurState == eCharacterState::eSkilling || CurState == eCharacterState::eAttack)
	{
		/* 전해진 번호가 인벤토리 이상이거나 음수이다. */
		/* 이미 어떠한 행동 중이다(착용중 포함) */
		/* 주희에게 에러 메세지를 돌려보내줘야 한다(리턴 값 수정이 필요할 수 있다) */
		/* 지금은 할 수 없습니다. 라는 메시지 같은? */
		return;
	}

	UAnimMontage* pSheath_Anim = NULL;
	eWeaponType iWeaponType = eWeaponType::eType_None;

	//이미 끼고 있는 무기가 있는가?
	if (!GetCurrentWeapon())
	{
		/* 없다. */
		//바로 착용.
		//OnEqipWeapon_byInventoryIndex(_InvenIdx);
		JustSetCurrentWeapon_NotEquip(_InvenIdx);

		//착용 후 착용 된 무기의 타입을 얻어온다.
		eWeaponType iWeaponType = GetCurrentWeapon()->GetWeaponType();
		pSheath_Anim = (m_ArrAnimMontage)[eCharacterState::eSkilling + eAnimMontage_Skill_Interpol::eSheathWeapon + (int)iWeaponType];

		if (pSheath_Anim)
		{
			GetMesh()->AnimScriptInstance->Montage_Stop(0.0f); /* Stop All Montage Anim */
			//SetRunning(false);
			PlayAnimMontage_CheckCurrent(pSheath_Anim, eCharacterState::eSkilling);
			//SetSkilling(true);
			if (m_pPlayerState)
				m_pPlayerState->SetPlayerState(eCharacterState::eSkilling);
		}
	}

	else
	{
		//이미 끼고 있는 무기가 있다. 착용 해제가 먼저 필요하다.
		float fDrawAnimDuration = DrawWeapon();

		if (fDrawAnimDuration == 0.0f)
			return;

		//칼을 넣는 애니메이션이 끝나면 다시 이 함수를 부른다.
		FTimerHandle TimerHandle_ReCallFunction;
		FTimerDelegate RecallFunctionDelegate =
			FTimerDelegate::CreateUObject(this, &ANP4PlayerBase::SheathWeapon, _InvenIdx);
		GetWorldTimerManager().SetTimer(TimerHandle_ReCallFunction,
			RecallFunctionDelegate, fDrawAnimDuration + 0.14f , false);
	}
}


float ANP4PlayerBase::PlayAnimMontage_CheckCurrent(UAnimMontage* _AnimMontage, eCharacterState _eAnimType)
{
	float reuturnVal = 0.0f;
	eWeaponType iWeaponType = GetCurrentWeapon() == NULL ? eWeaponType::eType_None : GetCurrentWeapon()->GetWeaponType();

	USkeletalMeshComponent* mesh = GetMesh();
	UAnimInstance* AnimInstance = mesh->AnimScriptInstance;

	if (AnimInstance == NULL) /* Animation Setting is not correct */
		return Animation_Montage_Failed;

	if (AnimInstance->Montage_IsPlaying(_AnimMontage) == false)
	{
		if (_eAnimType == eCharacterState::eHit)
		{
			float AnimDuration = PlayNP4AnimationMontage(_AnimMontage);
			reuturnVal = AnimDuration - 0.2f - (_AnimMontage->RateScale - 0.8f); //-0.2f부터 없었던 거임

			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, FString::Printf(TEXT("HIT")));

			FTimerHandle TimerHandle_StopHit;
			GetWorldTimerManager().SetTimer(TimerHandle_StopHit, this,
				&ANP4PlayerBase::StopHit, reuturnVal/*AnimDuration - 0.2f - (_AnimMontage->RateScale - 0.8f)*/, false);
		}

		else if (_eAnimType == eCharacterState::eAttack)
		{
			float AnimDuration = PlayNP4AnimationMontage(_AnimMontage);
			reuturnVal = AnimDuration;

			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, FString::Printf(TEXT("ATTACk")));

			/*FTimerHandle TimerHandle_StopAttack;
			GetWorldTimerManager().SetTimer(TimerHandle_StopAttack, this,
				&ANP4PlayerBase::StopAttack, AnimDuration - 0.2f - (_AnimMontage->RateScale - 0.8f), false);*/
		}

		else if (_eAnimType == eCharacterState::eSkilling)
		{
			float SubVal = 1.0f;

			int AnimIdx = (int)eCharacterState::eSkilling + (int)iWeaponType;
			FTimerHandle TimerHandle_StopSkill;
			if (_AnimMontage == (m_ArrAnimMontage)[
				AnimIdx + (int)eAnimMontage_Skill_Interpol::eSkill_1])
			{
				GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, FString::Printf(TEXT("Skill_1")));
				SubVal = 0.8f;
			}

			else if (_AnimMontage == (m_ArrAnimMontage)[
				AnimIdx + (int)eAnimMontage_Skill_Interpol::eSkill_2] )
			{
				GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, FString::Printf(TEXT("Skill_2")));
				SubVal = 0.8f;
			}

			else if (_AnimMontage == (m_ArrAnimMontage)[
				AnimIdx + (int)eAnimMontage_Skill_Interpol::eDrawWeapon] )
			{
				GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, FString::Printf(TEXT("DrawWeapon")));
				SubVal = 0.9;
			}

			else if (_AnimMontage == (m_ArrAnimMontage)[
				AnimIdx + (int)eAnimMontage_Skill_Interpol::eSheathWeapon] )
			{
				GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, FString::Printf(TEXT("SheathWeapon")));
				SubVal = 0.9f;
			}

				float AnimDuration = PlayNP4AnimationMontage(_AnimMontage);
				reuturnVal = AnimDuration - 0.1f - (_AnimMontage->RateScale - SubVal); //- 0.1f부터 없었던 거임.

				FTimerDelegate RespawnDelegate =
					FTimerDelegate::CreateUObject(this, &ANP4PlayerBase::StopSkill, _AnimMontage);
				GetWorldTimerManager().SetTimer(TimerHandle_StopSkill,
					RespawnDelegate, reuturnVal /* AnimDuration  - 0.1f - (_AnimMontage->RateScale - SubVal)*/, false);
		}

		else
		{
			reuturnVal = PlayNP4AnimationMontage(_AnimMontage);
		}
	}

	return reuturnVal;
}

void ANP4PlayerBase::SetbNotifyEnter(bool _bEnter)
{
	m_bComboNotifyEnter = _bEnter;
}

void ANP4PlayerBase::SetbComboOn(bool _bActive)
{
	m_bComboClkOn = _bActive;
}

bool ANP4PlayerBase::GetbNotifyEnter()
{
	return m_bComboNotifyEnter;
}

bool ANP4PlayerBase::GetbComboOn()
{
	return m_bComboClkOn;
}

eCombo_Interpol ANP4PlayerBase::GetCurrentComboStep()
{
	return m_ComboStep;
}

void ANP4PlayerBase::SetCurrentComboStep(eCombo_Interpol _newStep)
{
	m_ComboStep = _newStep;
}
