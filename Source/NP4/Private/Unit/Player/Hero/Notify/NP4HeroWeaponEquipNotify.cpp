// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "NP4PlayerBase.h"
#include "NP4HeroWeaponEquipNotify.h"

void UNP4HeroWeaponEquipNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp)
	{
		AActor* pOwnerActor = MeshComp->GetOwner();
		if (pOwnerActor)
		{
			ANP4PlayerBase* pPlayerCast = Cast<ANP4PlayerBase>(pOwnerActor);

			if (pPlayerCast)
			{
				pPlayerCast->OnEqipWeapon(pPlayerCast->GetCurrentWeapon());
			}
		}
	}
}


