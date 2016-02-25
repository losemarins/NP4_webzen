// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "NP4PlayerBase.h"
#include "Character_Minion.h"
#include "NP4CollisionNotify_Minion.h"

UNP4CollisionNotify_Minion::UNP4CollisionNotify_Minion()
{
	m_sSocketName = "RightHand";
}

void UNP4CollisionNotify_Minion::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (MeshComp)
	{
		AActor* pOwnerActor = MeshComp->GetOwner();
		if (pOwnerActor)
		{
			ANP4CharacterBase* pMyCast = Cast<ANP4CharacterBase>(pOwnerActor);
			if (!pMyCast)
			{
				//ACharacter_Minion* pMyCast = Cast<ACharacter_Minion>(pOwnerActor);
			}
		}
	}
}
