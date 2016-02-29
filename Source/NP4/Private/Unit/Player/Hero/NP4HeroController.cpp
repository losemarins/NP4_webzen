// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "NP4HeroController.h"
#include "NP4PlayerBase.h"
#include "NP4CameraManager.h"
#include "NP4HeroController.h"
#include "Kismet/KismetMathLibrary.h"
#include "NP4GameState.h"
#include "AIDirector.h"
#include "Building_Castle.h"
#include "FormationManager.h"
#include "Character_Minion.h"
#include "AIController_Minion.h"
ANP4HeroController::ANP4HeroController()
{
	//ANP4PlayerController::ANP4PlayerController();
	
	PlayerCameraManagerClass = ANP4CameraManager::StaticClass();
	//GetWorld()->SpawnActor<ANP4CharacterBase>(Owner->CharClass, Loc, Owner->GetActorRotation(), SpawnInfo);
	

	m_bZoomingIn = false;
	m_bMouseRightClk = false;

	m_bUseCameraAction = false;
	m_bActionCameraActive = false;
	TargetActor = NULL;

}

void ANP4HeroController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//몬스터 스폰 임시로
	InputComponent->BindAction("Spawn_1", IE_Pressed, this, &ANP4HeroController::PlayerSpawn);
	InputComponent->BindAction("Spawn_2", IE_Pressed, this, &ANP4HeroController::EnemySpawn);

	//부대 전술관련 임시로
	InputComponent->BindAction("Formation1", IE_Pressed, this, &ANP4HeroController::Formation1);
	InputComponent->BindAction("Formation2", IE_Pressed, this, &ANP4HeroController::Formation2);
	InputComponent->BindAction("Formation3", IE_Pressed, this, &ANP4HeroController::Formation3);

	//이동 관련
	InputComponent->BindAxis(TEXT("MoveForward"), this, &ANP4HeroController::MoveFoward);
	InputComponent->BindAxis("MoveRight", this, &ANP4HeroController::MoveRight);

	//마우스 우클릭 관련
	InputComponent->BindAction("MouseRightCLK", IE_Pressed, this, &ANP4HeroController::MouseRightClk);
	InputComponent->BindAction("MouseRightCLK", IE_Released, this, &ANP4HeroController::MouseRightRelease);

	//카메라 관련
	InputComponent->BindAxis("Turn", this, &ANP4HeroController::Turn);
	InputComponent->BindAxis("Lookup", this, &ANP4HeroController::Lookup);
	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &ANP4HeroController::ZoomIn);
	InputComponent->BindAction("ZoomOut", IE_Pressed, this, &ANP4HeroController::ZoomOut);

	//케릭터 액션 관련
	InputComponent->BindAction("Run", IE_Pressed, this, &ANP4HeroController::StartRunning);
	InputComponent->BindAction("Run", IE_Released, this, &ANP4HeroController::StopRunning);
	InputComponent->BindAction("Attack", IE_Pressed, this, &ANP4HeroController::ActionAttack);
	InputComponent->BindAction("Skill_1", IE_Pressed, this, &ANP4HeroController::ActionSkill_1);
	InputComponent->BindAction("Skill_2", IE_Pressed, this, &ANP4HeroController::ActionSkill_2);
	//InputComponent->BindAction("DrawWeapon", IE_Pressed, this, &ANP4HeroController::DrawWeapon);
	//InputComponent->BindAction("SheathWeapon", IE_Pressed, this, &ANP4HeroController::SheathWeapon);

	InputComponent->BindAction("Test_Hit", IE_Pressed, this, &ANP4HeroController::TestTestTest);
}

void ANP4HeroController::BeginPlay()
{
	Super::BeginPlay();

	//Array초기화
	if (!IsArrayNotNull())
	{
		InitializeActionCameraArray();
	}
	
	Formation = Cast<ANP4GameState>(GetWorld()->GetGameState())->FormationManager;
	/*PlayerSpawn();
	EnemySpawn();*/
}

void ANP4HeroController::BeginDestroy()
{
	Super::BeginDestroy();

	if (IsArrayNotNull() && !IsEmptyActionCameraArr())
	{
		DeleteActionCameraOnLevel();
	}
	delete m_arr_ActionCamera;
	m_arr_ActionCamera = NULL;
}

void ANP4HeroController::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	/* ActionCamera가 있으면, 액션카메라를 돌린다. */
	if (IsArrayNotNull() && !IsEmptyActionCameraArr() && IsUseCameraActionNow())
	{
		//Tick마다 들어오면 안되기때문에, DoActionCamera를 여기서 호출하면 안된다.
	}

	else
	{
		if (m_pPossessCharacter)
			ZoomTickFunc(_DeltaTime, m_bZoomingIn);
	}
	
	//임시로
	if (true)
	{
		FVector2D MousePos = GetMousePos();
		FHitResult HitResult = GetSelectActor(MousePos);

		if (HitResult.GetActor())
		{
			TargetActor = HitResult.GetActor();
		}
	}
}

void ANP4HeroController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);
	m_pPossessCharacter = Cast<ANP4PlayerBase>(m_pPossessPawn);
}

////////////////////////////////////////////////* Initialize */
void ANP4HeroController::InitializeActionCameraArray()
{
	m_arr_ActionCamera = new TArray<ANP4CameraActor*>();
}

/* 카메라 매니저에게 카메라 생성을 요청한다. */
ANP4CameraActor* ANP4HeroController::Request_MakeActionCamera(ECameraValue _CameraValue, AActor* _pBaseObject)
{
	ANP4CameraActor* pSpawnActor = NULL;

	if (IsCameraMangerNull())
		return NULL;

	else
	{
		pSpawnActor = m_pCameraManager->Request_MakeActionCamera(_CameraValue, _pBaseObject);

		if (!pSpawnActor)
			return NULL;
	}

	return pSpawnActor;
}

void ANP4HeroController::Push_ActionCameraArray(ANP4CameraActor* _pCreatedCamera)
{
	m_arr_ActionCamera->Add(_pCreatedCamera);
	m_bUseCameraAction = true;
}

void ANP4HeroController::DeleteActionCameraOnLevel()
{
	/* 카메라 배열 지우기 */
	//AFrameWorkCamera* pDelete
}

////////////////////////////////////////////////* Set */
void ANP4HeroController::SetCameraActionActive(bool _bActive)
{
	m_bActionCameraActive = _bActive;
}

////////////////////////////////////////////////* bool */
bool ANP4HeroController::IsEmptyActionCameraArr()
{
	return m_arr_ActionCamera->Num() <= 0 ? true : false;
}

bool ANP4HeroController::IsArrayNotNull()
{
	return m_arr_ActionCamera != NULL ? true : false;
}

bool ANP4HeroController::IsUseCameraActionNow()
{
	return m_bUseCameraAction;
}

bool ANP4HeroController::IsCameraActionActive()
{
	return m_bActionCameraActive;
}

void ANP4HeroController::DoActionCamera()
{
	SetViewTargetWithBlend((*m_arr_ActionCamera)[0], (*m_arr_ActionCamera)[0]->GetActionCameraBlendSpeed());

	FTimerHandle Test_End;
	GetWorldTimerManager().SetTimer(Test_End, this,
		&ANP4HeroController::Delete_Camera, (*m_arr_ActionCamera)[0]->GetActionCameraNextCameraTime(), false);

	m_bUseCameraAction = true;
}

void ANP4HeroController::Delete_Camera()
{
	if (!IsArrayNotNull())
	{
		return;
	}

	if (!IsEmptyActionCameraArr())
	{
		ANP4CameraActor* DeleteCam = (*m_arr_ActionCamera)[0];
		m_arr_ActionCamera->Remove(DeleteCam);
		DeleteCam->Destroy();
	}

	//위에서 지우고 나서 검사(else)하면 안됨.
	if (IsEmptyActionCameraArr())
	{
		GetWorld()->ForceGarbageCollection(true);

		//다시 디폴트 카메라로 설정한다.
		m_pPossessCharacter->SetDefaultCameraActive();
		m_bUseCameraAction = false;
	}

	else
	{
		DoActionCamera();
	}
}

////////////////////////////////////////////////* About Move Function */
void ANP4HeroController::MoveFoward(float _AxisValue)
{
	if (m_pPossessCharacter && !m_pPossessCharacter->IsSomeAction() && _AxisValue != 0.f)
	{
		const FRotator& lControllerRotation = GetControlRotation();
		FRotator rTmp = FRotator(0.0f, lControllerRotation.Yaw, 0.0f);
		FVector vTmp = UKismetMathLibrary::GetForwardVector(rTmp);
		m_pPossessCharacter->AddMovementInput(vTmp, _AxisValue);
	}
}

void ANP4HeroController::MoveRight(float _AxisValue)
{
	if (m_pPossessCharacter && !m_pPossessCharacter->IsSomeAction() && _AxisValue != 0.f)
	{
		const FRotator& lControllerRotation = GetControlRotation();
		FRotator rTmp = FRotator(0.0f, lControllerRotation.Yaw, 0.0f);
		FVector vTmp = UKismetMathLibrary::GetRightVector(rTmp);
		m_pPossessCharacter->AddMovementInput(vTmp, _AxisValue);
	}
}

////////////////////////////////////////////////* About Camera Function */
void ANP4HeroController::Turn(float _AxisValue)
{
	if (m_pPossessCharacter && !m_pPossessCharacter->IsSomeAction() && m_bMouseRightClk)
	{
		m_pPossessCharacter->AddControllerYawInput(_AxisValue);
	}
}

void ANP4HeroController::Lookup(float _AxisValue)
{
	if (m_pPossessCharacter && !m_pPossessCharacter->IsSomeAction() && m_bMouseRightClk)
	{
		m_pPossessCharacter->AddControllerPitchInput(_AxisValue);
	}
}

void ANP4HeroController::ZoomTickFunc(float _DeltaTime, bool _bZoomIn)
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

	float Min = 0.f;
	float Max = 0.f;
	m_pPossessCharacter->GetSpringArmLength(Max, Min);

	m_ZoomFactor = FMath::Clamp<float>(m_ZoomFactor, 0.0f, 1.0f);
	m_pPossessCharacter->GetCameraComponent()->FieldOfView = FMath::Lerp<float>(90.0f, 60.0f, m_ZoomFactor);
	m_pPossessCharacter->GetSpringArmCompoennt()->TargetArmLength = FMath::Lerp<float>(Max, Min, m_ZoomFactor);
}


void ANP4HeroController::ZoomIn()
{
	m_bZoomingIn = true;
}

void ANP4HeroController::ZoomOut()
{
	m_bZoomingIn = false;
}

/////////////////////////////////////////////////* Mouse Right Clk Function */
void ANP4HeroController::MouseRightClk()
{
	m_bMouseRightClk = true;
}

void ANP4HeroController::MouseRightRelease()
{
	m_bMouseRightClk = false;
}

ANP4PlayerBase* ANP4HeroController::GetPossessCharacter()
{
	return m_pPossessCharacter;
}

////////////////////////////////////////////////* State and Action Start,Stop(Key binding) */
void ANP4HeroController::ActionAttack()
{
	if (m_pPossessCharacter != NULL)
		m_pPossessCharacter->ActionAttack();
}

void ANP4HeroController::StartRunning()
{
	if (m_pPossessCharacter != NULL)
	{
		m_pPossessCharacter->StartRunning();
	}
}

void ANP4HeroController::StopRunning()
{
	if (m_pPossessCharacter != NULL)
	{
		m_pPossessCharacter->StopRunning();
	}
}

void ANP4HeroController::ActionHit()
{
	if (m_pPossessCharacter != NULL)
	{
		m_pPossessCharacter->ActionHit();
	}
}

void ANP4HeroController::ActionSkill_1()
{
	if (m_pPossessCharacter != NULL)
	{
		m_pPossessCharacter->ActionSkill_1();
	}
}

void ANP4HeroController::ActionSkill_2()
{
	if (m_pPossessCharacter != NULL)
	{
		m_pPossessCharacter->ActionSkill_2();
	}
}

void ANP4HeroController::DrawWeapon()
{
	if (m_pPossessCharacter != NULL)
	{
		m_pPossessCharacter->DrawWeapon();
	}
}

void ANP4HeroController::SheathWeapon(int _ItemUniqueID)
{
	if (m_pPossessCharacter != NULL)
	{
		m_pPossessCharacter->SheathWeapon(_ItemUniqueID);
	}
}

void ANP4HeroController::PlayerSpawn()
{
	const FPlayerData* const PlayerTeamData = GetWorld()->GetGameState<ANP4GameState>()->GetPlayerData(EGameTeam::Player);
	{
		PlayerTeamData->Castle->GetAIDirector()->RequestSpawn();
	}
}

void ANP4HeroController::EnemySpawn()
{
	const FPlayerData* const EnemyTeamData = GetWorld()->GetGameState<ANP4GameState>()->GetPlayerData(EGameTeam::Enemy);
	{
		EnemyTeamData->Castle->GetAIDirector()->RequestSpawn();
	}
}

void ANP4HeroController::Formation1()
{
	Formation = Cast<ANP4GameState>(GetWorld()->GetGameState())->FormationManager;
	TArray<class ANP4CharacterBase*> list = Formation->GetUnitList();

	for (int32 i = 0; i < list.Num(); i++)
	{
		Cast<AAIController_Minion>(list[i]->GetController())->SetStrategyType((uint8)EGameStrategy::Defualt);
		Cast<AAIController_Minion>(list[i]->GetController())->SetTargetEnemy(nullptr);
	}
}

void ANP4HeroController::Formation2()
{
	Formation = Cast<ANP4GameState>(GetWorld()->GetGameState())->FormationManager;
	TArray<class ANP4CharacterBase*> list = Formation->GetUnitList();

	for (int32 i = 0; i < list.Num(); i++)
	{
		Cast<AAIController_Minion>(list[i]->GetController())->SetStrategyType((uint8)EGameStrategy::Converging_Attack);
		Cast<AAIController_Minion>(list[i]->GetController())->SetTargetEnemy(TargetActor);
	}
}

void ANP4HeroController::Formation3()
{
	Formation = Cast<ANP4GameState>(GetWorld()->GetGameState())->FormationManager;
	//FVector_NetQuantize pos = GetSelectActor(MousePos).ImpactPoint;
	TArray<class ANP4CharacterBase*> list = Formation->GetUnitList();
	TArray<IndianFile_Info> Info = Formation->GetIndianFileInfo();

	for (int32 i = 0; i < list.Num(); i++)
	{
		Cast<AAIController_Minion>(list[i]->GetController())->SetStrategyType((uint8)EGameStrategy::Indian_File);
		Info[i].Pos += m_pPossessCharacter->GetActorLocation();
		Info[i].Pos.Z = 0;
		Cast<AAIController_Minion>(list[i]->GetController())->SetMoveLoc(Info[i].Pos);
	}
}
