// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "NP4PlayerBase.h"
#include "NP4CharacterBase.h"
#include "NP4AttackCollisionActiveNotifyState.h"

UNP4AttackCollisionActiveNotifyState::UNP4AttackCollisionActiveNotifyState()
{
	
}

void UNP4AttackCollisionActiveNotifyState::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	if (MeshComp)
	{
		AActor* pOwnerActor = MeshComp->GetOwner();
		if (pOwnerActor)
		{
			ANP4PlayerBase* pPlayerCast = Cast<ANP4PlayerBase>(pOwnerActor);

			if (pPlayerCast)
			{
				pPlayerCast->SetColliderEnabled(true, m_eActiveCollisionType);
			}
		}

	}
}

void UNP4AttackCollisionActiveNotifyState::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);


	if (MeshComp)
	{
		AActor* pOwnerActor = MeshComp->GetOwner();
		if (pOwnerActor)
		{
			ANP4PlayerBase* pPlayerCast = Cast<ANP4PlayerBase>(pOwnerActor);

			if (pPlayerCast)
			{
				pPlayerCast->SetColliderEnabled(false, m_eActiveCollisionType);
			}
		}

	}
}