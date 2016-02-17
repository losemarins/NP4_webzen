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
	TArray<AWeaponBase*> m_pItemInven_Temp; //�ӽ�

	/* ���� ���� */
	AWeaponBase* m_pCurrentEquipWeapon;

	/* ���� ���̴� �� */ //���Ŀ� CharacterBase�� �÷����� ���� ����.
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

public: /* �����̰� BP���� ȣ���ϱ� ���ؼ� ���� �ִϸ��̼� ��Ÿ�� �÷��� */
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
