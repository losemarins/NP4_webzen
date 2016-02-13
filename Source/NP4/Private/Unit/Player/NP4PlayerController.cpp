// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "NP4PlayerBase.h"
#include "NP4CameraManager.h"
#include "NP4PlayerController.h"
#include "Kismet/KismetMathLibrary.h"

ANP4PlayerController::ANP4PlayerController()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerCameraManagerClass = ANP4CameraManager::StaticClass();
	m_bUseCameraAction = false;
	m_bActionCameraActive = false;

	m_bZoomingIn = false;
	m_bMouseRightClk = false;
}

void ANP4PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//이동 관련
	InputComponent->BindAxis(TEXT("MoveForward"), this, &ANP4PlayerController::MoveFoward);
	InputComponent->BindAxis("MoveRight", this, &ANP4PlayerController::MoveRight);

	//마우스 우클릭 관련
	InputComponent->BindAction("MouseRightCLK", IE_Pressed, this, &ANP4PlayerController::MouseRightClk);
	InputComponent->BindAction("MouseRightCLK", IE_Released, this, &ANP4PlayerController::MouseRightRelease);

	//카메라 관련
	InputComponent->BindAxis("Turn", this, &ANP4PlayerController::Turn);
	InputComponent->BindAxis("Lookup", this, &ANP4PlayerController::Lookup);
	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &ANP4PlayerController::ZoomIn);
	InputComponent->BindAction("ZoomOut", IE_Pressed, this, &ANP4PlayerController::ZoomOut);

	//케릭터 액션 관련
	InputComponent->BindAction("Run", IE_Pressed, this, &ANP4PlayerController::StartRunning);
	InputComponent->BindAction("Run", IE_Released, this, &ANP4PlayerController::StopRunning);
	InputComponent->BindAction("Attack", IE_Pressed, this, &ANP4PlayerController::ActionAttack);
	InputComponent->BindAction("Skill_1", IE_Pressed, this, &ANP4PlayerController::ActionSkill_1);
	InputComponent->BindAction("Skill_2", IE_Pressed, this, &ANP4PlayerController::ActionSkill_2);

	InputComponent->BindAction("Test_Hit", IE_Pressed, this, &ANP4PlayerController::TestTestTest);
}

void ANP4PlayerController::BeginPlay()
{
	SetCameraManager(GetPlayerCameraManager());

	//Array초기화
	if (!IsArrayNotNull())
	{
		InitializeActionCameraArray();
	}
}

void ANP4PlayerController::BeginDestroy()
{
	Super::BeginDestroy();

	if (IsArrayNotNull() && !IsEmptyActionCameraArr())
	{
		DeleteActionCameraOnLevel();
	}
	delete m_arr_ActionCamera;
	m_arr_ActionCamera = NULL;
}

void ANP4PlayerController::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	/* ActionCamera가 있으면, 액션카메라를 돌린다. */
	if (IsArrayNotNull() && !IsEmptyActionCameraArr() && IsUseCameraActionNow())
	{
		//Tick마다 들어오면 안되기때문에, DoActionCamera를 여기서 호출하면 안된다.
	}

	else
	{
		m_pPossessCharacter->ZoomTickFunc(_DeltaTime, m_bZoomingIn);
	}
}

void ANP4PlayerController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);
	m_pPossessCharacter = Cast<ANP4PlayerBase>(InPawn);
}

////////////////////////////////////////////////* Initialize */
void ANP4PlayerController::InitializeActionCameraArray()
{
	m_arr_ActionCamera = new TArray<ANP4CameraActor*>();
}

/* 카메라 매니저에게 카메라 생성을 요청한다. */
ANP4CameraActor* ANP4PlayerController::Request_MakeActionCamera(ECameraValue _CameraValue, AActor* _pBaseObject)
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

eErrorType ANP4PlayerController::Request_GetDefaultCameraInfo(ECameraValue _CameraValue, FtCameraLocationInfo& _rInfo)
{
	if (IsCameraMangerNull())
		return eErrorType::eFailed;

	else
	{
		if (m_pCameraManager->Request_GetDefaultCameraInfo(_CameraValue, _rInfo) == eErrorType::eFailed)
		{
			return eErrorType::eFailed;
		}
	}

	return eErrorType::eSuccess;
}

void ANP4PlayerController::Push_ActionCameraArray(ANP4CameraActor* _pCreatedCamera)
{
	m_arr_ActionCamera->Add(_pCreatedCamera);
	m_bUseCameraAction = true;
}


////////////////////////////////////////////////* About Move Function */
void ANP4PlayerController::MoveFoward(float _AxisValue)
{
	if (m_pPossessCharacter && !m_pPossessCharacter->IsSomeAction() && _AxisValue != 0.f)
	{
		const FRotator& lControllerRotation = GetControlRotation();
		FRotator rTmp = FRotator(0.0f, lControllerRotation.Yaw, 0.0f);
		FVector vTmp = UKismetMathLibrary::GetForwardVector(rTmp);
		m_pPossessCharacter->AddMovementInput(vTmp, _AxisValue);
	}
}

void ANP4PlayerController::MoveRight(float _AxisValue)
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
void ANP4PlayerController::Turn(float _AxisValue)
{
	if (m_pPossessCharacter && !m_pPossessCharacter->IsSomeAction() && m_bMouseRightClk)
	{
		m_pPossessCharacter->AddControllerYawInput(_AxisValue);
	}
}

void ANP4PlayerController::Lookup(float _AxisValue)
{
	if (m_pPossessCharacter && !m_pPossessCharacter->IsSomeAction() && m_bMouseRightClk)
	{
		m_pPossessCharacter->AddControllerPitchInput(_AxisValue);
	}
}

void ANP4PlayerController::ZoomIn()
{
	m_bZoomingIn = true;
}

void ANP4PlayerController::ZoomOut()
{
	m_bZoomingIn = false;
}

/////////////////////////////////////////////////* Mouse Right Clk Function */
void ANP4PlayerController::MouseRightClk()
{
	m_bMouseRightClk = true;
}

void ANP4PlayerController::MouseRightRelease()
{
	m_bMouseRightClk = false;
}

////////////////////////////////////////////////* Set */
void ANP4PlayerController::SetCameraManager(ANP4CameraManager* _CameraManager)
{
	if (IsCameraMangerNull())
	{
		m_pCameraManager = _CameraManager;
	}
}

void ANP4PlayerController::SetCameraActionActive(bool _bActive)
{
	m_bActionCameraActive = _bActive;
}

void ANP4PlayerController::DeleteActionCameraOnLevel()
{
	/* 카메라 배열 지우기 */
	//AFrameWorkCamera* pDelete
}

ANP4PlayerBase* ANP4PlayerController::GetPossessCharacter()
{
	return m_pPossessCharacter;
}

////////////////////////////////////////////////* bool */
bool ANP4PlayerController::IsCameraMangerNull()
{
	return m_pCameraManager == NULL ? true : false;
}

bool ANP4PlayerController::IsEmptyActionCameraArr()
{
	return m_arr_ActionCamera->Num() <= 0 ? true : false;
}

bool ANP4PlayerController::IsArrayNotNull()
{
	return m_arr_ActionCamera != NULL ? true : false;
}

bool ANP4PlayerController::IsUseCameraActionNow()
{
	return m_bUseCameraAction;
}

bool ANP4PlayerController::IsCameraActionActive()
{
	return m_bActionCameraActive;
}


////////////////////////////////////////////////* State and Action Start,Stop(Key binding) */
void ANP4PlayerController::ActionAttack()
{
	if (m_pPossessCharacter != NULL)
		m_pPossessCharacter->ActionAttack();
}

void ANP4PlayerController::StartRunning()
{
	if (m_pPossessCharacter != NULL)
	{
		m_pPossessCharacter->StartRunning();
	}
}

void ANP4PlayerController::StopRunning()
{
	if (m_pPossessCharacter != NULL)
	{
		m_pPossessCharacter->StopRunning();
	}
}

void ANP4PlayerController::ActionHit()
{
	if (m_pPossessCharacter != NULL)
	{
		m_pPossessCharacter->ActionHit();
	}
}

void ANP4PlayerController::ActionSkill_1()
{
	if (m_pPossessCharacter != NULL)
	{
		m_pPossessCharacter->ActionSkill_1();
	}
}

void ANP4PlayerController::ActionSkill_2()
{
	if (m_pPossessCharacter != NULL)
	{
		m_pPossessCharacter->ActionSkill_2();
	}
}


void ANP4PlayerController::DoActionCamera()
{
	SetViewTargetWithBlend((*m_arr_ActionCamera)[0], (*m_arr_ActionCamera)[0]->GetActionCameraBlendSpeed());

	FTimerHandle Test_End;
	GetWorldTimerManager().SetTimer(Test_End, this,
		&ANP4PlayerController::Delete_Camera, (*m_arr_ActionCamera)[0]->GetActionCameraNextCameraTime(), false);

	m_bUseCameraAction = true;
}

void ANP4PlayerController::Delete_Camera()
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