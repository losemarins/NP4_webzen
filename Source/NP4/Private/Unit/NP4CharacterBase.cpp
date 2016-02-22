// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "NP4CharacterBase.h"
#include "WeaponBase.h"
#include "NP4ItemManager.h"

// Sets default values
ANP4CharacterBase::ANP4CharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->AttachTo(RootComponent);
	Health = 100;
	HealthMax = 100;
	m_AttackValue = 0.0f;

	m_pCurrentEquipWeapon = NULL;
	m_iCurrentEquip_InvenIndex = 0;
}

// Called when the game starts or when spawned
void ANP4CharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANP4CharacterBase::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ANP4CharacterBase::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void ANP4CharacterBase::SetTeamNum(uint8 NewTeamNum)
{
	MyTeamNum = NewTeamNum;
}

uint8 ANP4CharacterBase::GetTeamNum() const
{
	return MyTeamNum;
}

float ANP4CharacterBase::PlayNP4AnimationMontage(UAnimMontage* _pAnimMontage)
{
	return PlayAnimMontage(_pAnimMontage);
}

void ANP4CharacterBase::StopNP4AnimationMontage(UAnimMontage* _pAnimMontage)
{
	StopAnimMontage(_pAnimMontage);
}

bool ANP4CharacterBase::IsAlive()
{
	return Health > 0;
}

void ANP4CharacterBase::OnUnEquipWeapon()
{
	m_pCurrentEquipWeapon->OnUnEquip();
	m_pCurrentEquipWeapon = NULL;
}

void ANP4CharacterBase::OnEqipWeapon(AWeaponBase* _pWeapon)
{
	//¹«±â¸¦ ÀåÂø]
	if (_pWeapon)
	{
		m_pCurrentEquipWeapon = _pWeapon;
		_pWeapon->SetOwningPawn(this);
		_pWeapon->OnEquip();
	}
}

void ANP4CharacterBase::OnEqipWeapon_byInventoryIndex(int _InvenIdx)
{
	if (_InvenIdx >= m_pItemInven_Temp.Num())
		return;

	else
	{
		OnEqipWeapon(m_pItemInven_Temp[_InvenIdx]);
	}
}

void ANP4CharacterBase::InitWeapon_TempFunction()
{
	UObject* ClassPackage = ANY_PACKAGE;
	ANP4ItemManager* pItemLoadManager = NULL;
	UClass* BPClass = StaticLoadClass(UObject::StaticClass(), NULL, TEXT("/Game/Blueprint/NP4ItemLoadManager.NP4ItemLoadManager_C"), NULL, LOAD_None, NULL);

	if (BPClass)
	{
		pItemLoadManager = Cast<ANP4ItemManager>(BPClass->GetDefaultObject());

		if (pItemLoadManager)
		{
			FActorSpawnParameters SpawnInfo;
			for (int i = 0; i < pItemLoadManager->GetItemArrNum(); ++i)
			{
				AWeaponBase* pItem = (AWeaponBase*)GetWorld()->SpawnActor<AWeaponBase>(pItemLoadManager->GetItemByIndex(i),SpawnInfo);
				m_pItemInven_Temp.AddUnique(pItem);
			}

			/*if (m_pItemInven_Temp.Num() > 0)
			{
				OnEqipWeapon(m_pItemInven_Temp[0]);
			}*/
		}
	}
}

void ANP4CharacterBase::SetWeaponColliderEnabled(bool _bActive)
{
	if (m_pCurrentEquipWeapon)
	{
		m_pCurrentEquipWeapon->SetColliderEnabled(_bActive);
	}
}

void ANP4CharacterBase::JustSetCurrentWeapon_NotEquip(int _InvenIdx)
{
	if (_InvenIdx >= m_pItemInven_Temp.Num())
		return;

	else
	{
		//OnEqipWeapon(m_pItemInven_Temp[_InvenIdx]);
		m_pCurrentEquipWeapon = m_pItemInven_Temp[_InvenIdx];
	}
}

AWeaponBase* ANP4CharacterBase::GetCurrentWeapon()
{
	return m_pCurrentEquipWeapon;
}

bool ANP4CharacterBase::CheckIndex_inInventory(int _idx)
{
	if (m_pItemInven_Temp.Num() <= _idx || _idx < 0)
	{
		return false;
	}

	return true;
}

void ANP4CharacterBase::SetWeaponAttackValue(float _fAttackValue)
{
	m_AttackValue = _fAttackValue;
}

float ANP4CharacterBase::GetWeaponAttackValue()
{
	return m_AttackValue;
}

bool ANP4CharacterBase::Damaged_Call(float _fAttackValue)
{
	if (IsAlive() == false)
	{
		return false;
	}

	else
	{
		Health -= _fAttackValue;
		if (Health < 0)
		{
			Health = 0;
		}
		return true;
	}
}

/* Collision */
void ANP4CharacterBase::SetColliderEnabled(bool _bActive, eCollisionType _eColl)
{
	if (_bActive)
	{
		if (_eColl == eCollisionType::eCollision_LeftPunch)
		{
			//Left
			m_pLeftPunchCapsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, "LEFT_PUNCH_ActiveCollision");
			m_pLeftPunchCapsule->SetVisibility(false);
		}

		else if (_eColl == eCollisionType::eCollision_RightPunch)
		{
			//Right
			m_pRightPunchCapsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, "RIGHT_PUNCH_ActiveCollision");
			m_pRightPunchCapsule->SetVisibility(false);
		}

		else if (_eColl == eCollisionType::eCollision_LeftKick)
		{
			//Left
			m_pLeftKickCapsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, "LEFT_KICK_ActiveCollision");
			m_pLeftKickCapsule->SetVisibility(false);
		}

		else if (_eColl == eCollisionType::eCollision_RightKick)
		{
			//Right
			m_pRightKickCapsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, "RIGHT_KICK_ActiveCollision");
			m_pRightKickCapsule->SetVisibility(false);
		}

		else if (_eColl == eCollisionType::eCollision_Weapon)
		{
			SetWeaponColliderEnabled(_bActive);
		}
	}

	else
	{
		if (_eColl == eCollisionType::eCollision_LeftPunch)
		{
			//Left
			m_pLeftPunchCapsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, "LEFT_PUNCH_No Collision");
			m_pLeftPunchCapsule->SetVisibility(true);
		}

		else if (_eColl == eCollisionType::eCollision_RightPunch)
		{
			//Right
			m_pRightPunchCapsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, "RIGHT_PUNCH_No Collision");
			m_pRightPunchCapsule->SetVisibility(true);
		}

		else if (_eColl == eCollisionType::eCollision_LeftKick)
		{
			//Left
			m_pLeftKickCapsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, "LEFT_KICK_No Collision");
			m_pLeftKickCapsule->SetVisibility(true);
		}

		else if (_eColl == eCollisionType::eCollision_RightKick)
		{
			//Right
			m_pRightKickCapsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, "RIGHT_KICK_No Collision");
			m_pRightKickCapsule->SetVisibility(true);
		}

		else if (_eColl == eCollisionType::eCollision_Weapon)
		{
			SetWeaponColliderEnabled(_bActive);
		}
	}
}
