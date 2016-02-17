// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "WeaponBase.h"
#include "ItemBase.h"
#include "NP4CharacterBase.generated.h"

UCLASS()
class NP4_API ANP4CharacterBase : public ACharacter
{
	GENERATED_BODY()

protected :
	uint8 MyTeamNum;
	float Health;

public:
	TArray<AWeaponBase*> m_pItemInven_Temp; //임시

	/* 현재 무기 */
	AWeaponBase* m_pCurrentEquipWeapon;

	/* 무기 붙이는 곳 */ //추후에 CharacterBase로 올려야할 수도 있음.
	FName WeaponAttachPoint;
	
public:
	// Sets default values for this character's properties
	ANP4CharacterBase();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

public: /* 구영이가 BP에서 호출하기 위해서 만든 애니메이션 몽타쥬 플레이 */
	UFUNCTION(BlueprintCallable,Category = "NP4Animation")
	float PlayNP4AnimationMontage(UAnimMontage* _pAnimMontage);
	UFUNCTION(BlueprintCallable, Category = "NP4Animation")
	void StopNP4AnimationMontage(UAnimMontage* _pAnimMontage);

public :
	void SetTeamNum(uint8 NewTeamNum);
	uint8 GetTeamNum() const;
	bool IsAlive();

public:
	/* Init */
	void InitWeapon_TempFunction();

	/* Set,Get WeaponSocket */
	void SetAttachWeaponSocketPoint();
	FName GetAttachWeaponSocketPoint();

public:
	void OnUnEquipWeapon();
	void OnEqipWeapon(AWeaponBase* _pWeapon);

public:
	/* Collision */
	void SetColliderEnabled(bool _bActive);
};
