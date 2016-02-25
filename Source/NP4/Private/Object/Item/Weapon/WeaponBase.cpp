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
	m_pCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollision"));
	m_pCollisionBox->AttachTo(RootComponent, "WeaponCollision");
	//m_pCollisionCapsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	m_pCollisionBox->SetVisibility(true);
	m_pCollisionBox->bHiddenInGame = false;

	//State의 팀에 따라서 채널이 바뀌어야 한다.
	m_pCollisionBox->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	m_pCollisionBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	m_pCollisionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel2, ECollisionResponse::ECR_Ignore);
	m_pCollisionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel3, ECollisionResponse::ECR_Ignore);
	m_pCollisionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel4, ECollisionResponse::ECR_Ignore);
}

void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	m_pItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	m_pCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AWeaponBase::SetOwningPawn(ANP4CharacterBase* NewOwner)
{
	if (m_pWeaponOwner != NewOwner)
	{
		m_pWeaponOwner = NewOwner;
	}
}

void AWeaponBase::AttachMeshToPawn(FName _Name)
{
	if (m_pWeaponOwner)
	{
		USkeletalMeshComponent* PawnMesh = m_pWeaponOwner->GetMesh();
		//FName AttachPoint = m_pWeaponOwner->GetAttachWeaponSocketPoint();

		if(_Name != "")
			m_pItemMesh->AttachTo(PawnMesh, _Name);
	}
}

void AWeaponBase::OnEquip()
{
	AttachMeshToPawn(m_strEquipSocketName);
}

void AWeaponBase::OnUnEquip()
{
	//m_pItemMesh->DetachFromParent();

	AttachMeshToPawn(m_strUnEquipSocketName);
}

void AWeaponBase::SetMeshComponent(USkeletalMesh* _pMeshCom)
{
	m_pItemMesh->SetSkeletalMesh(_pMeshCom);
}

/* Check Collision */
bool AWeaponBase::IsColliderEnabled(void)
{
	return m_pCollisionBox->IsCollisionEnabled();
}

/* Collision Set */
void AWeaponBase::SetColliderEnabled(bool _bActive)
{
	if (_bActive)
	{
		m_pCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, "ActiveCollision");
		m_pCollisionBox->SetVisibility(false);
	}

	else
	{
		m_pCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, "No Collision");

		m_pCollisionBox->SetVisibility(true);
	}
}

/* Check Collision */
void AWeaponBase::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (IsColliderEnabled())
	{
		//TArray<UPrimitiveComponent*> tArr;
		//OtherActor->GetOverlappingComponents(tArr);

		//for (int iIdx = 0; iIdx < tArr.Num(); ++iIdx)
		//{
			//if (m_pCollisionCapsule == tArr[iIdx])
			{
				//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, m_pCollisionCapsule->GetName());
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, OtherActor->GetName());
			}
		//}

		m_pCollisionBox->SetVisibility(true);
	}
}

eWeaponType AWeaponBase::GetWeaponType()
{
	return m_iWeaponType;
}

UBoxComponent* AWeaponBase::GetWeaponCollisionBox()
{
	return m_pCollisionBox;
}