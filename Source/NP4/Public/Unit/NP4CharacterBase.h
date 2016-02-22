// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "WeaponBase.h"
#include "ItemBase.h"
#include "NP4AttackCollisionActiveNotifyState.h"
#include "NP4CharacterBase.generated.h"

UCLASS()
class NP4_API ANP4CharacterBase : public ACharacter
{
	GENERATED_BODY()

protected:
	uint8 MyTeamNum;

	//Juhe UI Add 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PlayerHPBar")
	float Health;

	UPROPERTY(BlueprintReadOnly, Category = "PlayerHPBar")
	float HealthMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerAttack")
	float m_AttackValue;

	/* Hit Capsule Component */
	UPROPERTY(VisibleAnywhere, Category = "Hit")
	UCapsuleComponent* MeleeCollisionComp;

	/* Attack Capsule Component */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCapsuleComponent* m_pLeftPunchCapsule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCapsuleComponent* m_pRightPunchCapsule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCapsuleComponent* m_pLeftKickCapsule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCapsuleComponent* m_pRightKickCapsule;

public:
	TArray<AWeaponBase*> m_pItemInven_Temp; //임시
	int m_iCurrentEquip_InvenIndex; //임시

											/* 현재 무기 */
	AWeaponBase* m_pCurrentEquipWeapon;

public:
	// Sets default values for this character's properties
	ANP4CharacterBase();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

public: /* 구영이가 BP에서 호출하기 위해서 만든 애니메이션 몽타쥬 플레이 */
	UFUNCTION(BlueprintCallable, Category = "NP4Animation")
		float PlayNP4AnimationMontage(UAnimMontage* _pAnimMontage);

	UFUNCTION(BlueprintCallable, Category = "NP4Animation")
		void StopNP4AnimationMontage(UAnimMontage* _pAnimMontage);

public:
	void SetTeamNum(uint8 NewTeamNum);
	uint8 GetTeamNum() const;
	bool IsAlive();

public:
	/* Init */
	void InitWeapon_TempFunction();

	/* Set,Get WeaponSocket */
	AWeaponBase* GetCurrentWeapon();
	void JustSetCurrentWeapon_NotEquip(int _InvenIdx);

public:
	void OnUnEquipWeapon();
	void OnEqipWeapon(AWeaponBase* _pWeapon);
	void OnEqipWeapon_byInventoryIndex(int _InvenIdx);
	bool CheckIndex_inInventory(int _idx);

public:
	/* Collision */
	void SetWeaponColliderEnabled(bool _bActive);
	/* Active Collision */
	void SetColliderEnabled(bool _bActive, eCollisionType _eColl);

	/* Attack Value Set,Get */
	void SetWeaponAttackValue(float _fAttackValue);
	float GetWeaponAttackValue();

	/* Damage! */
	bool Damaged_Call(float _fAttackValue);
};
