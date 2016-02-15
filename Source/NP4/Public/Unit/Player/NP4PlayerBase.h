// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NP4CharacterBase.h"
#include "NP4PlayerState.h"
#include "NP4CameraManager.h"
#include "NP4PlayerBase.generated.h"

class ANP4HeroController;
class ANP4CameraActor;

enum eAnimMontage_Skill_Interpol
{
	eSkill_1 = 0,
	eSkill_2 = 1,
	eSkill_3 = 2,
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

	/* Camera Value  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCameraComponent* m_OurCamera;

	/* Spring Arm */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USpringArmComponent* m_OurCameraSpringArm;

	/* Anim Montage */
	//TArray<UAnimMontage*> m_ArrAnimMontage[100];

	TArray<UAnimMontage*> m_ArrAnimMontage;

	/* Camera Value */
	float m_ZoomFactor;
	float m_MinSpringArmLength;
	float m_MaxSpringArmLength;

	/* StateMachine Value */
	bool m_bRunning;
	bool m_bAttack;
	bool m_bIsHit;
	bool m_bIsSkilling;

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

	/* Bool Check */
	bool IsPlayerControllerNull();
	UFUNCTION(BlueprintCallable, Category = "PlayerCheckState")
		bool IsWalking();
	UFUNCTION(BlueprintCallable, Category = "PlayerCheckState")
		bool IsRunning();
	UFUNCTION(BlueprintCallable, Category = "PlayerCheckState")
		bool IsAttack();
	UFUNCTION(BlueprintCallable, Category = "PlayerCheckState")
		bool IsHit();
	UFUNCTION(BlueprintCallable, Category = "PlayerCheckState")
		bool IsSkilling();
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

	/* Set StateMachine */
	void SetRunning(bool _bRunning);
	void SetAttack(bool _bAttack);
	void SetHit(bool _bHit);
	void SetSkilling(bool _bSkill);

	/* Play AnimMontage */
	float PlayAnimMontage_CheckCurrent(UAnimMontage* _AnimMontage, eCharacterState _eAnimType);

	/* Character Action */
	void StartRunning();
	void StopRunning();
	void ActionAttack();
	void StopAttack();
	void ActionHit();
	void StopHit();
	void ActionSkill_1();
	void ActionSkill_2();
	void StopSkill(UAnimMontage* _pSkillAnim);
};
