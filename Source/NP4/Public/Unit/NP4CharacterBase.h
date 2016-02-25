// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "WeaponBase.h"
#include "ItemBase.h"
#include "Inventory.h"
#include "WeaponBase.h"
#include "NP4AttackCollisionActiveNotifyState.h"
#include "NP4CharacterBase.generated.h"

UCLASS()
class NP4_API ANP4CharacterBase : public ACharacter
{
	GENERATED_BODY()

protected:
	uint8 m_iUniqueID;
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
	USphereComponent* m_pLeftPunchCapsule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* m_pRightPunchCapsule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* m_pLeftKickCapsule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* m_pRightKickCapsule;

public:
	/* 현재 무기 */
	AWeaponBase* m_pCurrentEquipWeapon;

public:
	// Sets default values for this character's properties
	ANP4CharacterBase();
	
public: /* 구영이가 BP에서 호출하기 위해서 만든 애니메이션 몽타쥬 플레이 */
	UFUNCTION(BlueprintCallable, Category = "NP4Animation")
	float PlayNP4AnimationMontage(UAnimMontage* _pAnimMontage);

	UFUNCTION(BlueprintCallable, Category = "NP4Animation")
	void StopNP4AnimationMontage(UAnimMontage* _pAnimMontage);

public:
	void SetTeamNum(uint8 NewTeamNum);
	uint8 GetTeamNum() const;
	USphereComponent* GetCollisionSphere(eCollisionType _CollType);
	bool IsAlive();

public:
	/* Set,Get WeaponSocket */
	AWeaponBase* GetCurrentWeapon();
	void JustSetCurrentWeapon_NotEquip(AWeaponBase* _pWeaponEquip);

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
	void SetDefaultAttackValue(float _fAttackValue);
	float GetDefaultAttackValue();

	/* Damage! */
	bool Damaged_Call(float _fAttackValue);

	/* ID Get,Set */
	void SetUniqueID(int _id);
	int32 GetUniqeID();
	
	/* Action */
	virtual void ActionHit( FVector _Dir = FVector(0,0,0) );
	virtual void StopHit();
	virtual void ActionDie();
	virtual void StopDie();
};
