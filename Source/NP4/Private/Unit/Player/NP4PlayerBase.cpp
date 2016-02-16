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
	if (m_pPlayerState)
	{
		m_pPlayerState = (Cast<ANP4PlayerState>(PlayerState));
		m_pPlayerState->SetStateOwner(this);

		//hp setting
		m_pPlayerState->setPlayerHealth(100.f);
		m_pPlayerState->setPlayerMaxHealth(100.f);
	}
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
	m_fAnimationMoveSpeed.Init(0.f, 100); /* 애니메이션 MoveSpeed Init */

	////Idle
	m_ArrAnimMontage.Insert(FindAnimationMontage_byPath(TEXT(MainPlayer_Mon_TwoHand_Idle1_PATH)), (int)eCharacterState::eIdle);
	
	////Walk
	m_ArrAnimMontage.Insert(FindAnimationMontage_byPath(TEXT(MainPlayer_Mon_TwoHand_Walk_PATH)), (int)eCharacterState::eWalk);

	////Run
	m_ArrAnimMontage.Insert(FindAnimationMontage_byPath(TEXT(MainPlayer_Mon_TwoHand_Run_PATH)), (int)eCharacterState::eRun);

	////Attack
	m_ArrAnimMontage.Insert(FindAnimationMontage_byPath(TEXT(MainPlayer_Mon_TwoHand_Attack_PATH)), (int)eCharacterState::eAttack);
	m_fAnimationMoveSpeed.Insert(150.f, (int)eCharacterState::eAttack);

	////HIT
	m_ArrAnimMontage.Insert(FindAnimationMontage_byPath(TEXT(MainPlayer_Mon_TwoHand_Hit_PATH)), (int)eCharacterState::eHit);

	////Skill_1
	m_ArrAnimMontage.Insert(FindAnimationMontage_byPath(TEXT(MainPlayer_Mon_TwoHand_CastingEarthQuake_PATH)), (int)eCharacterState::eSkilling + (int)eAnimMontage_Skill_Interpol::eSkill_1);

	////Skill_2
	m_ArrAnimMontage.Insert(FindAnimationMontage_byPath(TEXT(MainPlayer_Mon_TwoHand_TurnAttack_PATH)), (int)eCharacterState::eSkilling + (int)eAnimMontage_Skill_Interpol::eSkill_2);
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
	if (m_ArrAnimMontage.Num() <= (int)_eState)
	{
		return NULL;
	}

	return (m_ArrAnimMontage)[(int)_eState + (int)_eSkill_Interpolation];
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

	if (IsSomeAction())
	{
		return;
	}

	else if (IsWalking())
	{
		if (IsRunning())
		{
			ExeAnimMontage = (m_ArrAnimMontage)[eCharacterState::eRun];
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

			ExeAnimMontage = (m_ArrAnimMontage)[eCharacterState::eWalk];
			ExeAnimMontage_Type = eCharacterState::eWalk;
		}
	}

	else if (IsRunning())
	{
		ExeAnimMontage = (m_ArrAnimMontage)[eCharacterState::eRun];
		ExeAnimMontage_Type = eCharacterState::eRun;
	}

	/* Execution Montage Anim */
	if (ExeAnimMontage && ExeAnimMontage_Type != eCharacterState::eEnd)
		ReturnValue = PlayAnimMontage_CheckCurrent(ExeAnimMontage, ExeAnimMontage_Type);

	/* Is Succees change Montage Anim ? */
	if (ReturnValue != Animation_Montage_Failed)
		return;

	/* EntryPoint */
	else if (PlayAnimMontage_CheckCurrent((m_ArrAnimMontage)[eCharacterState::eIdle], eCharacterState::eIdle) != Animation_Montage_Failed)
	{
		if(m_pPlayerState)
			m_pPlayerState->SetPlayerState(eCharacterState::eIdle);
		return;
	}
}


/////////////////////////////////////////////////* Set StateMachine */
void ANP4PlayerBase::SetRunning(bool _bRunning)
{
	m_bRunning = _bRunning;
}

void ANP4PlayerBase::SetAttack(bool _bAttack)
{
	m_bAttack = _bAttack;
}

void ANP4PlayerBase::SetSkilling(bool _bSkill)
{
	m_bIsSkilling = _bSkill;
}

void ANP4PlayerBase::SetHit(bool _bHit)
{
	m_bIsHit = _bHit;
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

bool ANP4PlayerBase::IsRunning()
{
	if (!GetCharacterMovement())
		return false;

	return IsWalking() && m_bRunning;
}

bool ANP4PlayerBase::IsAttack()
{
	return m_bAttack;
}

bool ANP4PlayerBase::IsSkilling()
{
	return m_bIsSkilling;
}

bool ANP4PlayerBase::IsHit()
{
	return m_bIsHit;
}

bool ANP4PlayerBase::IsSomeAction()
{
	if (IsAttack() || IsHit() || IsSkilling())
		return true;

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
	SetRunning(true);
	
	/* Change State */
	if(m_pPlayerState)
		m_pPlayerState->SetPlayerState(eCharacterState::eRun);

	/* Change Speed */
	if (GetCharacterMovement())
		GetCharacterMovement()->MaxWalkSpeed = 600;
}

void ANP4PlayerBase::StopRunning()
{
	SetRunning(false);
}


void ANP4PlayerBase::ActionAttack()
{
	if (!IsHit() && !IsSkilling() && IsAttack() == false)
	{
		float fAnimDuationVal = 0.0f;
		SetRunning(false);

		UAnimMontage* pAttackAnim = NULL;
		pAttackAnim = (m_ArrAnimMontage)[eCharacterState::eAttack];

		if (pAttackAnim)
		{
			fAnimDuationVal = PlayAnimMontage_CheckCurrent(pAttackAnim, eCharacterState::eAttack);
			SetAttack(true);
			if(m_pPlayerState)
				m_pPlayerState->SetPlayerState(eCharacterState::eAttack);

			//Request_MakeActionCamera(ECameraValue::eAction_1, this, fAnimDuationVal);

			///* Collision Active */
			//SetColliderEnabled(true);
		}

		else
		{
			//Hit Motion Animation is not vaild
		}
	}
}

void ANP4PlayerBase::StopAttack()
{
	UAnimMontage* pAttackAnim = NULL;
	pAttackAnim = pAttackAnim = (m_ArrAnimMontage)[eCharacterState::eAttack];

	if (pAttackAnim)
	{
		StopNP4AnimationMontage(pAttackAnim);
		SetAttack(false);

		/* Collision no Active */
		//SetColliderEnabled(false);
	}

	else
	{
		//Hit Motion Animation is not vaild
	}
}


void ANP4PlayerBase::ActionHit()
{
	if (!IsSkilling() && IsHit() == false)
	{
		SetRunning(false);

		UAnimMontage* pHitAnim = NULL;
		pHitAnim = (m_ArrAnimMontage)[eCharacterState::eHit];

		if (pHitAnim)
		{
			PlayAnimMontage_CheckCurrent(pHitAnim, eCharacterState::eHit);
			SetHit(true);
			if(m_pPlayerState)
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
	UAnimMontage* pHitAnim = NULL;
	pHitAnim = (m_ArrAnimMontage)[eCharacterState::eHit];

	if (pHitAnim)
	{
		StopNP4AnimationMontage(pHitAnim);
		SetHit(false);
	}

	else
	{
		//Hit Motion Animation is not vaild
	}
}

void ANP4PlayerBase::ActionSkill_1()
{
	UAnimMontage* pSkill_1_Anim = NULL;
	pSkill_1_Anim = (m_ArrAnimMontage)[eCharacterState::eSkilling + eAnimMontage_Skill_Interpol::eSkill_1];

	if (pSkill_1_Anim && IsSkilling() == false)
	{
		float fAnimDuationVal = 0.0f;
		GetMesh()->AnimScriptInstance->Montage_Stop(0.0f); /* Stop All Montage Anim */
		SetRunning(false);
		fAnimDuationVal = PlayAnimMontage_CheckCurrent(pSkill_1_Anim, eCharacterState::eSkilling);
		SetSkilling(true);
		if(m_pPlayerState)
			m_pPlayerState->SetPlayerState(eCharacterState::eSkilling);
	}
}

void ANP4PlayerBase::ActionSkill_2()
{
	UAnimMontage* pSkill_2_Anim = NULL;
	pSkill_2_Anim = (m_ArrAnimMontage)[eCharacterState::eSkilling + eAnimMontage_Skill_Interpol::eSkill_2];


	if (pSkill_2_Anim && IsSkilling() == false)
	{
		GetMesh()->AnimScriptInstance->Montage_Stop(0.0f); /* Stop All Montage Anim */
		SetRunning(false);
		PlayAnimMontage_CheckCurrent(pSkill_2_Anim, eCharacterState::eSkilling);
		SetSkilling(true);
		if(m_pPlayerState)
			m_pPlayerState->SetPlayerState(eCharacterState::eSkilling);
	}
}

void ANP4PlayerBase::StopSkill(UAnimMontage* _pSkillAnim)
{
	StopNP4AnimationMontage(_pSkillAnim);
	SetSkilling(false);
}


float ANP4PlayerBase::PlayAnimMontage_CheckCurrent(UAnimMontage* _AnimMontage, eCharacterState _eAnimType)
{
	float reuturnVal = 0.0f;

	USkeletalMeshComponent* mesh = GetMesh();
	UAnimInstance* AnimInstance = mesh->AnimScriptInstance;

	if (AnimInstance == NULL) /* Animation Setting is not correct */
		return Animation_Montage_Failed;

	if (AnimInstance->Montage_IsPlaying(_AnimMontage) == false)
	{
		if (_eAnimType == eCharacterState::eHit)
		{
			float AnimDuration = PlayNP4AnimationMontage(_AnimMontage);
			reuturnVal = AnimDuration;

			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, FString::Printf(TEXT("HIT")));

			FTimerHandle TimerHandle_StopHit;
			GetWorldTimerManager().SetTimer(TimerHandle_StopHit, this,
				&ANP4PlayerBase::StopHit, AnimDuration - 0.2f, false);
		}

		else if (_eAnimType == eCharacterState::eAttack)
		{
			float AnimDuration = PlayNP4AnimationMontage(_AnimMontage);
			reuturnVal = AnimDuration;

			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, FString::Printf(TEXT("ATTACk")));

			FTimerHandle TimerHandle_StopAttack;
			GetWorldTimerManager().SetTimer(TimerHandle_StopAttack, this,
				&ANP4PlayerBase::StopAttack, AnimDuration - 0.2f, false);
		}

		else if (_eAnimType == eCharacterState::eSkilling)
		{
			FTimerHandle TimerHandle_StopSkill;
			if (_AnimMontage == (m_ArrAnimMontage)[
				(int)eCharacterState::eSkilling + (int)eAnimMontage_Skill_Interpol::eSkill_1])
			{
				GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, FString::Printf(TEXT("Skill_1")));
			}

			else if (_AnimMontage == (m_ArrAnimMontage)[
				(int)eCharacterState::eSkilling + (int)eAnimMontage_Skill_Interpol::eSkill_2])
			{
				GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, FString::Printf(TEXT("Skill_2")));
			}

				float AnimDuration = PlayNP4AnimationMontage(_AnimMontage);
				reuturnVal = AnimDuration;

				FTimerDelegate RespawnDelegate =
					FTimerDelegate::CreateUObject(this, &ANP4PlayerBase::StopSkill, _AnimMontage);
				GetWorldTimerManager().SetTimer(TimerHandle_StopSkill,
					RespawnDelegate, AnimDuration - 0.1f, false);
		}

		else
		{
			reuturnVal = PlayNP4AnimationMontage(_AnimMontage);
		}
	}

	return reuturnVal;
}

void ANP4PlayerBase::CheckMovingAnimation()
{
	if (m_pPlayerState)
	{
		int CurState = (int)m_pPlayerState->GetPlayerState();

		if (m_ArrAnimMontage[CurState] && m_fAnimationMoveSpeed[CurState] != 0.0f)
		{
			WhileAnimationMoveCharacter(CurState);
		}
	}
}

void ANP4PlayerBase::WhileAnimationMoveCharacter(int _CurState)
{
	//FRotator ActorRotation = 
}