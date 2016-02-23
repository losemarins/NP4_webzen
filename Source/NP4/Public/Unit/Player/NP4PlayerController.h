// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Define.h"
#include "NP4CameraManager.h"
#include "NP4CameraActor.h"
#include "GameFramework/PlayerController.h"
#include "NP4PlayerController.generated.h"

class ANP4PlayerBase;
class ANP4CameraManager;

UCLASS()
class NP4_API ANP4PlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ANP4PlayerController();
	
public:
	/* Possess Character Class */
	UPROPERTY()
	APawn* m_pPossessPawn;
	
	/* CameraManager Class*/
	UPROPERTY()
	ANP4CameraManager* m_pCameraManager;

public:
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
	virtual void SetupInputComponent() override;
	virtual void Tick(float _Deltatime) override;
	virtual void Possess(APawn* InPawn) override; /* Possess at DefaultPawnClass */

public:
	/* Set */
	void SetCameraManager(ANP4CameraManager* _CameraManager);
	eErrorType Request_GetDefaultCameraInfo(ECameraValue _CameraValue, FtCameraLocationInfo& _rInfo);
	
	/* Get */
	APawn* GetPossessPawn();

	/* bool Check */
	bool IsCameraMangerNull();

	//마우스 관련 함수
public : 
	FHitResult GetSelectActor(FVector2D MousePos);
	FVector2D GetMousePos();
};
