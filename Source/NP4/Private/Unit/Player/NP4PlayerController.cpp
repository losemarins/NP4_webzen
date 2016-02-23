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

FVector2D ANP4PlayerController::GetMousePos()
{
	const ULocalPlayer* LP = Cast<ULocalPlayer>(Player);
	//FVector2D MousePos = LP->ViewportClient->GetMousePosition();
	FVector2D MousePos;
	if (LP->ViewportClient->GetMousePosition(MousePos) == true)
	{
		/* 윈도우 내부에 마우스 포지션이 있음. */
	}

	return MousePos;
}

FHitResult ANP4PlayerController::GetSelectActor(FVector2D MousePos)
{
	FVector WorldOrigin, WorldDirection, TraceEnd; // 마우스 커서의 월드 위치, 가리키는 방향, 트레이스 끝지점
	FVector MouseWorldPosition_3D;
	FHitResult TraceHitResult;
	FCollisionObjectQueryParams TraceObjectParam; // 충돌이 어떤 유형의 오브젝트에 유효할것인지
	FCollisionQueryParams TraceParam;
	TraceObjectParam.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);
	TraceObjectParam.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldDynamic);
	TraceObjectParam.AddObjectTypesToQuery(ECollisionChannel::ECC_Pawn);

	TraceParam.bTraceComplex = true;
	TraceParam.bTraceAsyncScene = true;
	TraceParam.bReturnPhysicalMaterial = false;
	DeprojectScreenPositionToWorld(MousePos.X, MousePos.Y, WorldOrigin, WorldDirection);

	TraceEnd = WorldOrigin + WorldDirection * 65536.0f;
	//GetWorld()->LineTraceSingle(TraceHitResult, WorldOrigin, TraceEnd, TraceParam, TraceObjectParam);
	GetWorld()->LineTraceSingleByObjectType(TraceHitResult, WorldOrigin, TraceEnd, TraceObjectParam, TraceParam);
	return TraceHitResult;
}
