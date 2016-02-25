// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NP4CharacterBase.h"
#include "NP4PlayerState.h"
#include "NP4CameraManager.h"
#include "WeaponBase.h"
#include "Inventory.h"
#include "NP4PlayerBase.generated.h"

class ANP4HeroController;
class ANP4CameraActor;

enum eAnimMontage_Skill_Interpol
{
	eSkill_1 = 0,
	eSkill_2 = 1,
	eSkill_3 = 2,

	eDrawWeapon = 7,
	eSheathWeapon = 8 //스킬은 9개씩이므로 8번이 마지막
};

enum eCombo_Interpol
{
	Combo_None = 0,
	Combo_One = 1,
	Combo_Two = 2
};

UCLASS()
class NP4_API ANP4PlayerBase : public ANP4CharacterBase
{
	GENERATED_BODY()
public:
	ANP4PlayerBase();

public:
	/* Mesh Setting Value */
	static const FRotator msBaseRotation;
	static const FVector msBaseLocation;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "PlayerController")
	ANP4HeroController* m_pPlayerController;

	UPROPERTY()
	ANP4PlayerState* m_pPlayerState;
	UInventory* m_pPlayerInventory;

	/* Camera Value  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* m_OurCamera;

	/* Spring Arm */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USpringArmComponent* m_OurCameraSpringArm;

	/* Anim Montage */
	TArray<UAnimMontage*> m_ArrAnimMontage;

	/* Camera Value */
	float m_ZoomFactor;
	float m_MinSpringArmLength;
	float m_MaxSpringArmLength;

	/* Notify Combo */
	bool m_bComboNotifyEnter;
	bool m_bComboClkOn;
	eCombo_Interpol m_ComboStep;

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void PossessedBy(AController* _pContoller) override;

	/* Init */
	void InitAnimationMontage();

	/* Set, Get */
	void SetPlayerController(ANP4HeroController* _pPlayerController);
	void SetSpringArm(FtCameraLocationInfo _Info);
	void SetCameraRotaion(FRotator _Rot);
	void SetSpringArmCameraRotation(FRotator _Rot);
	UAnimMontage* GetAnimationMontage_fromArrMontage(eCharacterState _eState, eAnimMontage_Skill_Interpol _eSkill_Interpolation = eAnimMontage_Skill_Interpol::eSkill_1);
	UAnimMontage* GetAnimationMontage_fromArrMontage(int _idex);

	/* Bool Check */
	bool IsPlayerControllerNull();
	UFUNCTION(BlueprintCallable, Category = "PlayerCheckState")
	bool IsWalking();
	UFUNCTION(BlueprintCallable, Category = "PlayerCheckState")
	bool IsSomeAction(); //만약 공격이나 스킬이나 히트나 어떠한 행동패턴의 애니메이션 중인가?

	/* Find */
	UAnimMontage* FindAnimationMontage_byPath(const TCHAR* _ObjectToFindPath);
	
	/* Camera */
	void SetDefaultCameraActive();
	void ZoomTickFunc(float _DeltaTime, bool _bZoomIn);
	void Request_MakeActionCamera(ECameraValue _CameraValue, AActor* _pBaseObject, float _AnimDurationVal);

	/* check StateMachine */
	UFUNCTION()
	void CheckState(float _Deltatime);

	/* Play AnimMontage */
	float PlayAnimMontage_CheckCurrent(UAnimMontage* _AnimMontage, eCharacterState _eAnimType);

	/* Character Action */
	void StartRunning();
	void StopRunning();
	void ActionAttack();
	void StopAttack();
	virtual void ActionHit(FVector _Dir = FVector(0, 0, 0));
	virtual void StopHit();
	void ActionSkill_1();
	void ActionSkill_2();
	void StopSkill(UAnimMontage* _pSkillAnim);
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	float DrawWeapon();
	UFUNCTION(BlueprintCallable,Category = "Inventory")
	void SheathWeapon(int32 _UniqueItemID);
	virtual void ActionDie();
	virtual void StopDie();

	/* Notify Combo */
	void SetbNotifyEnter(bool _bEnter);
	void SetbComboOn(bool _bActive);
	bool GetbNotifyEnter();
	bool GetbComboOn();
	eCombo_Interpol GetCurrentComboStep();
	void SetCurrentComboStep(eCombo_Interpol _newStep);

	/* 무기 착용을 위한 임시 변수 */
	int tempidx;

	/* 아이템 인벤 */
	void OnEqipWeapon_byInventoryIndex(int _UniqueItemID);
	void InitWeapon_TempFunction(); //임시
};
