// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "WeaponBase.h"
#include "NP4CharacterBase.h"

AWeaponBase::AWeaponBase()
{
	//Mesh 세팅
	m_pItemMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	//m_pItemMesh->CastShadow = true;
	//m_pItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = m_pItemMesh;

	//Collision 셋팅
	m_pCollisionCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("WeaponCollision"));
	m_pCollisionCapsule->AttachTo(RootComponent, "WeaponCollision");
	//m_pCollisionCapsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//m_pCollisionCapsule->SetVisibility(false);
	m_pCollisionCapsule->bHiddenInGame = false;
	

	//State의 팀에 따라서 채널이 바뀌어야 한다.
	m_pCollisionCapsule->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel2);
}

void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	m_pItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	m_pCollisionCapsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	m_pCollisionCapsule->SetVisibility(false);
}


void AWeaponBase::SetOwningPawn(ANP4CharacterBase* NewOwner)
{
	if (m_pWeaponOwner != NewOwner)
	{
		m_pWeaponOwner = NewOwner;
	}
}

void AWeaponBase::AttachMeshToPawn()
{
	if (m_pWeaponOwner)
	{
		USkeletalMeshComponent* PawnMesh = m_pWeaponOwner->GetMesh();
		FName AttachPoint = m_pWeaponOwner->GetAttachWeaponSocketPoint();

		if(AttachPoint != "")
			m_pItemMesh->AttachTo(PawnMesh, AttachPoint);
	}
}

void AWeaponBase::OnEquip()
{
	AttachMeshToPawn();
}

void AWeaponBase::OnUnEquip()
{
	m_pItemMesh->DetachFromParent();
}

void AWeaponBase::SetMeshComponent(USkeletalMesh* _pMeshCom)
{
	m_pItemMesh->SetSkeletalMesh(_pMeshCom);
}

/* Check Collision */
bool AWeaponBase::IsColliderEnabled(void)
{
	return m_pCollisionCapsule->IsCollisionEnabled();
}

/* Collision Set */
void AWeaponBase::SetColliderEnabled(bool _bActive)
{
	if (_bActive)
	{
		m_pCollisionCapsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, "ActiveCollision");

		m_pCollisionCapsule->SetVisibility(false);
	}
	else
	{
		m_pCollisionCapsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, "No Collision");

		m_pCollisionCapsule->SetVisibility(true);
	}
}

/* Check Collision */
void AWeaponBase::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (IsColliderEnabled())
	{
		TArray<UPrimitiveComponent*> tArr;
		OtherActor->GetOverlappingComponents(tArr);

		for (int iIdx = 0; iIdx < tArr.Num(); ++iIdx)
		{
			if (m_pCollisionCapsule == tArr[iIdx])
			{
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, m_pCollisionCapsule->GetName());
			}
		}

		m_pCollisionCapsule->SetVisibility(true);
	}
}