// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object/Item/ItemBase.h"
#include "WeaponBase.generated.h"

//UEnum eWeaponType
//{
//	eType_1 = 0,
//	eType_2 = 21,
//	eType_3 = 41
//};

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class eWeaponType : uint8
{
	eType_1 = 0,
	eType_2 = 21,
	eType_3 = 41
};

class ANP4CharacterBase;

UCLASS()
class NP4_API AWeaponBase : public AItemBase
{
	GENERATED_BODY()

protected:
	class ANP4CharacterBase* m_pWeaponOwner;

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = Item)
	USkeletalMeshComponent* m_pItemMesh;

	/* Collision Value */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCapsuleComponent* m_pCollisionCapsule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		eWeaponType m_iWeaponType;

public:
	AWeaponBase();

	virtual void BeginPlay() override;
	
	void SetOwningPawn(ANP4CharacterBase* NewOwner);

	void AttachMeshToPawn();

	void OnEquip();

	void OnUnEquip();

public:
	void SetMeshComponent(USkeletalMesh* _pMeshCom);
	
	/* Check Collision */
	bool IsColliderEnabled(void);

	/* Collision Set */
	void SetColliderEnabled(bool _bActive);

	/* Collider ! */
	void NotifyActorBeginOverlap(AActor* OtherActor) override;

	eWeaponType GetWeaponType_byInt();
};
