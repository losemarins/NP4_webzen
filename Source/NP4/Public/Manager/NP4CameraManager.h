// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Define.h"
#include "Camera/PlayerCameraManager.h"
#include "NP4CameraManager.generated.h"

class ANP4CameraActor;

/* Camera Struct Height Info */
USTRUCT(BlueprintType)
struct FtCameraLocationInfo
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector Location;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FRotator Rotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Init_ArmLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Min_ArmLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Max_ArmLength;
};

/* Camera Struct Create CameraInfo */
USTRUCT(BlueprintType)
struct FtActionCameraInfo
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FtCameraLocationInfo m_tHeightInfo;

	/* Blend ���ǵ� */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float m_fBlendSpeed;

	/* ���� �׼� ī�޶� �����ÿ� ���� ī�޶�� �ű�� �� �ð� */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float m_fNextCameraValue;

	/* true�Ͻ� �����Ϳ��� ������ ������ �ϰ�, false�Ͻ� �ִϸ��̼��� �ൿ ������ �Ѵ� */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool m_bActionCameraBlendSpeedByEditor;
};

UCLASS()
class NP4_API ANP4CameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

	ANP4CameraManager();

public:
	/* �����Ϳ��� ���ÿ� ī�޶� */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* m_SetStructCamera;

	/* �����Ϳ��� ���ÿ� ������ �� */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USpringArmComponent* m_SetSpringArm;

	/* �����Ϳ��� ���ÿ� �Ž� */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* m_SetSkeletonMeshCom;

	/* Camera Setting Struct */
	UPROPERTY(EditAnywhere)
	FtActionCameraInfo m_tCameraInfo[(int)CAMERA_ARR_MAX]; /* CAMERA_ARR_MAX ���� WorldHeader�� ����. */

															   /* �����Ϳ��� �ʱ� �� ���� üũ */
	bool m_bInfoSetDone;

	/* ������ ���� : ����ü�� ���� �׽�Ʈ�� ī�޶󿡰� */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEditApplyto_Camera;

	/* ������ ���� : �׽�Ʈ�� ī�޶� ���� ����ü���� */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEditApplyto_Struct;

	/* ����Ʈ ī�޶� ���ÿ�, üũ �� �������Ͽ� ����ȴ�. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bApplySpringArm;

	/* Change Camera Struct Index Value (int Editor) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 m_iHeightStructIdx;

public:
	virtual void BeginPlay() override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void Tick(float _DeltaTime) override;

public:
	/* Request Create Camera */
	ANP4CameraActor* Request_MakeActionCamera(ECameraValue _CameraValue, AActor* _pBaseObject);
	eErrorType        Request_GetDefaultCameraInfo(ECameraValue _CameraValue, FtCameraLocationInfo& _rInfo);

	/* Struct Changed */
	void ChangeEdit_CameraValue();
	void ChangeEdit_StructValue(FVector _ReltaiveLocationVec, FRotator _ReltaiveRocationVec, float _SpringArmMaxDistance);

	/* �ش� ī�޶� ���� �迭 �ȿ� �ִ��� üũ */
	bool IsCameraValueInsideEnum(ECameraValue _CameraValue);

	/* �����Ϳ��� �ʱ� �� ���� */
	void SetCameraInfoArrayFromBP();
};
