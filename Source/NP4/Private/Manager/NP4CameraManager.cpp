// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "NP4CameraActor.h"
#include "NP4CameraManager.h"

ANP4CameraManager::ANP4CameraManager()
	: Super()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//스켈레톤 매쉬
	m_SetSkeletonMeshCom = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("StructSkeletonMesh"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshLoadAsset(TEXT("/Game/Mannequin/Character/Mesh/hero_body.hero_body"));
	if (MeshLoadAsset.Succeeded())
	{
		m_SetSkeletonMeshCom->SetSkeletalMesh(MeshLoadAsset.Object);
		m_SetSkeletonMeshCom->SetRelativeRotation(FRotator(0, -90, 0));
		m_SetSkeletonMeshCom->SetRelativeLocation(FVector(0, 0, -90));
	}

	//Spring Arm 세팅(부드러운 카메라 연출을 위해 사용)
	m_SetSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("StructSpringArm"));
	m_SetSpringArm->bUsePawnControlRotation = true;
	m_SetSpringArm->AttachTo(RootComponent);

	////카메라 셋팅
	m_SetStructCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("StructCamera"));
	m_SetStructCamera->AttachTo(m_SetSpringArm, USpringArmComponent::SocketName);

	/* 에디터 세팅 관련 변수 */
	m_bInfoSetDone = false;
	bApplySpringArm = false;
	bEditApplyto_Struct = false;
	bEditApplyto_Camera = false;
}

void ANP4CameraManager::BeginPlay()
{
	if (m_SetSpringArm)
	{
		m_SetSpringArm->DestroyComponent();
		m_SetSpringArm = NULL;
	}

	if (m_SetStructCamera)
	{
		m_SetStructCamera->DestroyComponent();
		m_SetStructCamera = NULL;
	}

	if (m_SetSkeletonMeshCom)
	{
		m_SetSkeletonMeshCom->DestroyComponent();
		m_SetSkeletonMeshCom = NULL;
	}
}

void ANP4CameraManager::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	if (bEditApplyto_Camera == true && bEditApplyto_Struct == true)
	{
		/* 둘다 세팅 될 수는 없습니다. */
		bEditApplyto_Camera = false;
	}

	/* 에디터 적용 : 구조체의 값이 테스트용 카메라에게 */
	if (bEditApplyto_Camera && IsCameraValueInsideEnum((ECameraValue)m_iHeightStructIdx))
	{
		ChangeEdit_CameraValue();
	}

	/* 에디터 적용 : 테스트용 카메라 값이 구조체에게 */
	if (bEditApplyto_Struct && IsCameraValueInsideEnum((ECameraValue)m_iHeightStructIdx))
	{
		if (bApplySpringArm)
		{
			ChangeEdit_StructValue(m_SetSpringArm->RelativeLocation, m_SetSpringArm->RelativeRotation, m_SetSpringArm->TargetArmLength);
		}

		else
		{
			ChangeEdit_StructValue(m_SetStructCamera->RelativeLocation, m_SetStructCamera->RelativeRotation, 0.0f);
		}
	}
}

void ANP4CameraManager::ChangeEdit_CameraValue()
{
	if (bApplySpringArm)
	{
		m_SetSpringArm->RelativeLocation = m_tCameraInfo[m_iHeightStructIdx].m_tHeightInfo.Location;
		m_SetSpringArm->RelativeRotation = m_tCameraInfo[m_iHeightStructIdx].m_tHeightInfo.Rotation;
		m_SetSpringArm->TargetArmLength = m_tCameraInfo[m_iHeightStructIdx].m_tHeightInfo.Init_ArmLength;
	}
	else
	{
		m_SetStructCamera->RelativeLocation = m_tCameraInfo[m_iHeightStructIdx].m_tHeightInfo.Location;
		m_SetStructCamera->RelativeRotation = m_tCameraInfo[m_iHeightStructIdx].m_tHeightInfo.Rotation;
	}
}

void ANP4CameraManager::ChangeEdit_StructValue(
	FVector _ReltaiveLocationVec, FRotator _ReltaiveRocationVec,
	float _SpringArmMaxDistance)
{
	m_tCameraInfo[m_iHeightStructIdx].m_tHeightInfo.Location = _ReltaiveLocationVec;
	m_tCameraInfo[m_iHeightStructIdx].m_tHeightInfo.Rotation = _ReltaiveRocationVec;
	m_tCameraInfo[m_iHeightStructIdx].m_tHeightInfo.Init_ArmLength = _SpringArmMaxDistance;

	if (m_tCameraInfo[m_iHeightStructIdx].m_tHeightInfo.Max_ArmLength < _SpringArmMaxDistance)
	{
		m_tCameraInfo[m_iHeightStructIdx].m_tHeightInfo.Max_ArmLength = _SpringArmMaxDistance;
	}

}

void ANP4CameraManager::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

/* 요청한 카메라를 만들어서 리턴한다. */
ANP4CameraActor* ANP4CameraManager::Request_MakeActionCamera(ECameraValue _CameraValue, AActor* _pBaseObject)
{
	/* 요청한 카메라의 Value 값이 잘못되었는지 체크 */
	if (!IsCameraValueInsideEnum(_CameraValue))
	{
		return NULL;
	}

	if (m_bInfoSetDone == false)
	{
		SetCameraInfoArrayFromBP();
	}

	FVector CameraLocation = m_tCameraInfo[(int)_CameraValue].m_tHeightInfo.Location;
	FRotator CameraRotation = m_tCameraInfo[(int)_CameraValue].m_tHeightInfo.Rotation;

	FVector ActorLocation = _pBaseObject->GetActorLocation();
	FRotator ActionRotation = _pBaseObject->GetActorRotation();

	FRotator ResultRotation = FRotator(ActionRotation.Pitch, ActionRotation.Yaw, ActionRotation.Roll);

	//Plus백터를 돌려야한다.
	CameraLocation = ResultRotation.RotateVector(CameraLocation);

	FVector ResultLocation = FVector(
		ActorLocation.X + CameraLocation.X,
		ActorLocation.Y + CameraLocation.Y,
		ActorLocation.Z + CameraLocation.Z);

	ANP4CameraActor* pSpawnActor = (ANP4CameraActor*)GetWorld()->SpawnActor(ANP4CameraActor::StaticClass(), &ResultLocation, &ResultRotation);
	if (!pSpawnActor)
	{
		return NULL;
	}

	pSpawnActor->SetCameraInfo(m_tCameraInfo[(int)_CameraValue]);
	pSpawnActor->SetCameraOwner(_pBaseObject);
	pSpawnActor->SetCameraComponent_LocationRotation(ResultLocation, ResultRotation, CameraRotation);
	return pSpawnActor;
}

eErrorType ANP4CameraManager::Request_GetDefaultCameraInfo(ECameraValue _CameraValue, FtCameraLocationInfo& _rInfo)
{
	/* 요청한 카메라의 Value 값이 잘못되었는지 체크 */
	if (!IsCameraValueInsideEnum(_CameraValue))
	{
		return eErrorType::eFailed;
	}

	if (m_bInfoSetDone == false)
	{
		SetCameraInfoArrayFromBP();
	}

	_rInfo = m_tCameraInfo[(int)_CameraValue].m_tHeightInfo;

	return eErrorType::eSuccess;
}

bool ANP4CameraManager::IsCameraValueInsideEnum(ECameraValue _CameraValue)
{
	if (_CameraValue <= ECameraValue::eStartCamera && _CameraValue >= ECameraValue::eEndCamera)
		return false;

	return true;
}

void ANP4CameraManager::SetCameraInfoArrayFromBP()
{
	UObject* ClassPackage = ANY_PACKAGE;
	ANP4CameraManager* pBP_CameraManager = NULL;
	UClass* BPClass = StaticLoadClass(UObject::StaticClass(), NULL, TEXT("/Game/Blueprint/CameraManager.CameraManager_C"), NULL, LOAD_None, NULL);

	if (BPClass)
	{
		pBP_CameraManager = Cast<ANP4CameraManager>(BPClass->GetDefaultObject());

		for (int idx = 0; idx < (int)CAMERA_ARR_MAX; ++idx)
		{
			m_tCameraInfo[idx] = pBP_CameraManager->m_tCameraInfo[idx];
		}

		m_bInfoSetDone = true;
	}

	else
	{
		//UE_LOG(CSLog, Log, TEXT("CameraManager Find Failed"));
	}
}