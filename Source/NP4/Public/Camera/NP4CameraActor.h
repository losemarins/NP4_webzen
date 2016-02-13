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
	/* �ش� Owner�� ī�޶� ���߰� ��. */
	UPROPERTY(EditAnyWhere) AActor* m_pCameraOwner;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) USceneComponent* m_RootComponent;

	/* Camera Value */
	UPROPERTY(EditAnywhere, BlueprintReadWrite) UCameraComponent* m_OurCamera;

	/* About Camera Value */
	FtActionCameraInfo m_thisCameraInfo;

	/* Action Camera Info */
	float m_fBlendSpeed; /* Blend ���ǵ� */
	float m_fNextCameraTime; /* ���� �׼� ī�޶� �����ÿ� ���� ī�޶�� �ű�� �� �ð� */
	bool m_bActionCameraBlendSpeedByEditor; /* true�Ͻ� �����Ϳ��� ������ ������ �ϰ�, false�Ͻ� �ִϸ��̼��� �ൿ ������ �Ѵ� */

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

	/* �����Ϳ��� ������ ī�޶� ����ü�� ���� Get,Set �Ѵ�. */
	void SetCameraInfo(FtActionCameraInfo _tCameraInfo);
	FtActionCameraInfo GetCameraInfo();

	/* bool Check Function */
	bool IsCameraownerNull();
	bool IsCameraComponentActive();

	/* Active Camera */
	void SetCameraComponentActive(bool _Active);
	void SetCameraComponent_LocationRotation(FVector _vLocation, FRotator _vRotation, FRotator _vCameraRotation);
};
