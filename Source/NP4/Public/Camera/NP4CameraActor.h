// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Define.h"
#include "NP4CameraManager.h"
#include "NP4CameraActor.generated.h"

class ANP4PlayerBase;
class ANP4PlayerController;


UCLASS()
class NP4_API ANP4CameraActor : public AActor
{
	GENERATED_BODY()
	ANP4CameraActor();
	
public:
	/* 해당 Owner를 카메라가 비추게 됨. */
	UPROPERTY(EditAnyWhere) AActor* m_pCameraOwner;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) USceneComponent* m_RootComponent;

	/* Camera Value */
	UPROPERTY(EditAnywhere, BlueprintReadWrite) UCameraComponent* m_OurCamera;

	/* About Camera Value */
	FtActionCameraInfo m_thisCameraInfo;

	/* Action Camera Info */
	float m_fBlendSpeed; /* Blend 스피드 */
	float m_fNextCameraTime; /* 다음 액션 카메라가 있을시에 다음 카메라로 옮기게 될 시간 */
	bool m_bActionCameraBlendSpeedByEditor; /* true일시 에디터에서 세팅한 값으로 하고, false일시 애니메이션의 행동 값으로 한다 */

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
public:
	/* Set/Get Camera Owner */
	void SetCameraOwner(AActor* _pActor);
	void SetCameraBleendSpeed(float _fSpeed);
	void SetCameraNextCamSpeed(float _fSpeed);
	AActor* GetCameraOnwer();
	float GetActionCameraBlendSpeed();
	float GetActionCameraNextCameraTime();
	bool GetActionCameraBlendSpeedByEditor();

	/* 에디터에서 세팅한 카메라 구조체의 값을 Get,Set 한다. */
	void SetCameraInfo(FtActionCameraInfo _tCameraInfo);
	FtActionCameraInfo GetCameraInfo();

	/* bool Check Function */
	bool IsCameraownerNull();
	bool IsCameraComponentActive();

	/* Active Camera */
	void SetCameraComponentActive(bool _Active);
	void SetCameraComponent_LocationRotation(FVector _vLocation, FRotator _vRotation, FRotator _vCameraRotation);
};
