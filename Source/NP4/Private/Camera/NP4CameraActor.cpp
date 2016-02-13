// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "NP4PlayerBase.h"
#include "NP4PlayerController.h"
#include "NP4CameraActor.h"


// Sets default values
ANP4CameraActor::ANP4CameraActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bFindCameraComponentWhenViewTarget = true;

	///Root Setting
	m_RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(m_RootComponent);

	////朝五虞 実特
	m_OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	SetRootComponent(m_RootComponent);
	m_OurCamera->Deactivate();
}

void ANP4CameraActor::BeginPlay()
{
	Super::BeginPlay();
}

void ANP4CameraActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

////////////////////////////////////////////////* Set, Get */
void ANP4CameraActor::SetCameraOwner(AActor* _pActor)
{
	m_pCameraOwner = _pActor;
}

void ANP4CameraActor::SetCameraInfo(FtActionCameraInfo _tCameraInfo)
{
	m_thisCameraInfo = _tCameraInfo;
}

void ANP4CameraActor::SetCameraComponentActive(bool _Active)
{
	m_OurCamera->SetActive(_Active);
}

void ANP4CameraActor::SetCameraBleendSpeed(float _fSpeed)
{
	m_fBlendSpeed = _fSpeed;
}

void ANP4CameraActor::SetCameraNextCamSpeed(float _fSpeed)
{
	m_fNextCameraTime = _fSpeed;
}

void ANP4CameraActor::SetCameraComponent_LocationRotation(FVector _vLocation, FRotator _vRotation, FRotator _vCameraRotation)
{
	m_OurCamera->SetRelativeLocation(_vLocation);
	m_OurCamera->SetRelativeRotation(_vRotation);
	m_OurCamera->AddLocalRotation(_vCameraRotation);
}

AActor* ANP4CameraActor::GetCameraOnwer()
{
	return m_pCameraOwner;
}

FtActionCameraInfo ANP4CameraActor::GetCameraInfo()
{
	return m_thisCameraInfo;
}

float ANP4CameraActor::GetActionCameraBlendSpeed()
{
	return m_fBlendSpeed;
}

float ANP4CameraActor::GetActionCameraNextCameraTime()
{
	return m_fNextCameraTime;
}

bool ANP4CameraActor::GetActionCameraBlendSpeedByEditor()
{
	return m_bActionCameraBlendSpeedByEditor;
}

////////////////////////////////////////////////* bool check */
bool ANP4CameraActor::IsCameraownerNull()
{
	return m_pCameraOwner == NULL ? true : false;
}

bool ANP4CameraActor::IsCameraComponentActive()
{
	return m_OurCamera->IsActive() == true ? true : false;
}

