// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "NP4TownPlayer.h"
#include "NP4TownPlayerController.h"
#include "Define.h"

// Sets default values
ANP4TownPlayer::ANP4TownPlayer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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


}

// Called when the game starts or when spawned
void ANP4TownPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	// 컨트롤러 셋팅
	//if (IsPlayerControllerNull())
	{
		m_pTownController = Cast<ANP4TownPlayerController>(GetNP4PlayerController());
	}
	/* 스프링암을 세팅된 값으로 기본 세팅한다. */
	FtCameraLocationInfo LocationInfo;
	if (!IsPlayerControllerNull())
	{
		eErrorType eType = m_pTownController->Request_GetDefaultCameraInfo(ECameraValue::eTownCamera, LocationInfo);

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
	
	if(m_pTownController)
		m_pTownController->SetViewTarget(m_OurCameraSpringArm->GetOwner());
}

// Called every frame
void ANP4TownPlayer::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ANP4TownPlayer::SetSpringArm(FtCameraLocationInfo _Info)
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

void ANP4TownPlayer::SetSpringArmCameraRotation(FRotator _Rot)
{
	m_OurCameraSpringArm->SetRelativeRotation(_Rot);
}

void ANP4TownPlayer::SetCameraRotaion(FRotator _Rot)
{
	m_OurCamera->SetRelativeRotation(_Rot);
}


bool ANP4TownPlayer::IsPlayerControllerNull()
{
	return m_pTownController == NULL ? true : false;
}
