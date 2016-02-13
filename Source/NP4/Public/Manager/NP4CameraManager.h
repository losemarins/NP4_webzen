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

	/* Blend 스피드 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float m_fBlendSpeed;

	/* 다음 액션 카메라가 있을시에 다음 카메라로 옮기게 될 시간 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float m_fNextCameraValue;

	/* true일시 에디터에서 세팅한 값으로 하고, false일시 애니메이션의 행동 값으로 한다 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool m_bActionCameraBlendSpeedByEditor;
};

UCLASS()
class NP4_API ANP4CameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

	ANP4CameraManager();

public:
	/* 에디터에서 세팅용 카메라 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* m_SetStructCamera;

	/* 에디터에서 세팅용 스프링 암 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USpringArmComponent* m_SetSpringArm;

	/* 에디터에서 세팅용 매쉬 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* m_SetSkeletonMeshCom;

	/* Camera Setting Struct */
	UPROPERTY(EditAnywhere)
	FtActionCameraInfo m_tCameraInfo[(int)CAMERA_ARR_MAX]; /* CAMERA_ARR_MAX 값은 WorldHeader에 있음. */

															   /* 에디터에서 초기 값 세팅 체크 */
	bool m_bInfoSetDone;

	/* 에디터 적용 : 구조체의 값이 테스트용 카메라에게 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEditApplyto_Camera;

	/* 에디터 적용 : 테스트용 카메라 값이 구조체에게 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEditApplyto_Struct;

	/* 디폴트 카메라 세팅용, 체크 시 스프링암에 적용된다. */
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

	/* 해당 카메라 값이 배열 안에 있는지 체크 */
	bool IsCameraValueInsideEnum(ECameraValue _CameraValue);

	/* 에디터에서 초기 값 세팅 */
	void SetCameraInfoArrayFromBP();
};
