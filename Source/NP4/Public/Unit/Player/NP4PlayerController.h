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
	ANP4PlayerBase* m_pPossessCharacter;

	/* CameraManager Class*/
	UPROPERTY()
	ANP4CameraManager* m_pCameraManager;

public:	/* ��Ʈ�ѷ��� ī�޶� ������ �ִ´� */

	/* �׼� ī�޶� */
	TArray<ANP4CameraActor*>* m_arr_ActionCamera;
	bool m_bUseCameraAction; /* ī�޶� �׼� ���� ��� �⺻ ī�޶� off �Ѵ�. */
	UPROPERTY(EditAnywhere, Category = "ActionCamera")
	bool m_bActionCameraActive; /* �׼� ī�޶� ��� �����̴�. ž�信���� �� ���� false�� ���̴�. */

public:
	/* About Camera Check Value */
	bool m_bMouseRightClk;
	bool m_bZoomingIn;

public:
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
	virtual void SetupInputComponent() override;
	virtual void Tick(float _Deltatime) override;
	virtual void Possess(APawn* InPawn) override; /* Possess at DefaultPawnClass */

public:
	/* Init */
	void InitializeActionCameraArray();

	/* Request Create Camera Function */
	ANP4CameraActor* Request_MakeActionCamera(ECameraValue _CameraValue, AActor* _pBaseObject);
	eErrorType        Request_GetDefaultCameraInfo(ECameraValue _CameraValue, FtCameraLocationInfo& _rInfo);
	void Push_ActionCameraArray(ANP4CameraActor* _pCreatedCamera);

	/* About Move Function */
	void MoveFoward(float _AxisValue);
	void MoveRight(float _AxisValue);
	void Turn(float AxisValue);
	void Lookup(float AxisValue);
	void ZoomIn();
	void ZoomOut();

	/* About Mouse Right Clk Function */
	void MouseRightClk();
	void MouseRightRelease();

	/* Set */
	void SetCameraManager(ANP4CameraManager* _CameraManager);
	void SetCameraActionActive(bool _bActive);
	void DeleteActionCameraOnLevel();

	/* Get */
	ANP4PlayerBase* GetPossessCharacter();

	/* bool Check */
	bool IsEmptyActionCameraArr();
	bool IsArrayNotNull();
	bool IsCameraMangerNull();
	bool IsUseCameraActionNow(); //���� �׼� ī�޶� ���� ���ΰ�?
	bool IsCameraActionActive(); //�׼� ī�޶� Ȱ��ȭ�����ΰ�?

								 /* State and Action Start,Stop(Key binding) */
	void StartRunning();
	void StopRunning();
	void ActionAttack();
	void ActionHit();
	void ActionSkill_1();
	void ActionSkill_2();

	/* Do Action Camera */
	void DoActionCamera();
	void Delete_Camera();

	//////////////////////�׽�Ʈ��
	void FORCEINLINE TestTestTest()
	{
		ActionHit();
	}
	
	//���� ���� �ӽ÷�
	void PlayerSpawn();
	void EnemySpawn();

};
