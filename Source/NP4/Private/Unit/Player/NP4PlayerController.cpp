// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "NP4PlayerBase.h"
#include "NP4CameraManager.h"
#include "NP4PlayerController.h"
#include "Kismet/KismetMathLibrary.h"
#include "NP4GameState.h"


ANP4PlayerController::ANP4PlayerController()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerCameraManagerClass = ANP4CameraManager::StaticClass();
}

void ANP4PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}

void ANP4PlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetCameraManager(GetPlayerCameraManager());
}

void ANP4PlayerController::BeginDestroy()
{
	Super::BeginDestroy();
}

void ANP4PlayerController::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ANP4PlayerController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);
	m_pPossessPawn = Cast<ANP4PlayerBase>(InPawn);
}


APawn* ANP4PlayerController::GetPossessPawn()
{
	return m_pPossessPawn;
}

void ANP4PlayerController::SetCameraManager(ANP4CameraManager* _CameraManager)
{
	if (IsCameraMangerNull())
	{
		m_pCameraManager = _CameraManager;
	}
}

bool ANP4PlayerController::IsCameraMangerNull()
{
	return m_pCameraManager == NULL ? true : false;
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