// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Define.h"
#include "NP4CameraManager.h"
#include "NP4CameraActor.h"
#include "NP4PlayerController.h"
#include "NP4HeroController.generated.h"

class ANP4PlayerBase;
class ANP4CameraManager;

UCLASS()
class NP4_API ANP4HeroController : public ANP4PlayerController
{
public:
	GENERATED_BODY()

public:
	ANP4HeroController();
	
	/* Possess Character Class */
	UPROPERTY()
	ANP4PlayerBase* m_pPossessCharacter;

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

	/* Init */
	void InitializeActionCameraArray();

	/* Set */
	void SetCameraActionActive(bool _bActive);
	void DeleteActionCameraOnLevel();

	/* Request Create Camera Function */
	ANP4CameraActor* Request_MakeActionCamera(ECameraValue _CameraValue, AActor* _pBaseObject);
	void Push_ActionCameraArray(ANP4CameraActor* _pCreatedCamera);

	/* Get */
	ANP4PlayerBase* GetPossessCharacter();

	/* bool Check */
	bool IsEmptyActionCameraArr();
	bool IsArrayNotNull();
	bool IsUseCameraActionNow(); //���� �׼� ī�޶� ���� ���ΰ�?
	bool IsCameraActionActive(); //�׼� ī�޶� Ȱ��ȭ�����ΰ�?

								 /* Do Action Camera */
	void DoActionCamera();
	void Delete_Camera();

	/* State and Action Start,Stop(Key binding) */
	void StartRunning();
	void StopRunning();
	void ActionAttack();
	void ActionHit();
	void ActionSkill_1();
	void ActionSkill_2();

	//////////////////////�׽�Ʈ��
	void FORCEINLINE TestTestTest()
	{
		ActionHit();
	}

	//���� ���� �ӽ÷�
	void PlayerSpawn();
	void EnemySpawn();
};
