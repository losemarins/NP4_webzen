// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "NP4PlayerBase.h"
#include "NP4HeroSlowNotifyState.h"

void UNP4HeroSlowNotifyState::NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

	if (MeshComp)
	{
		AActor* pOwnerActor = MeshComp->GetOwner();
		if (pOwnerActor)
		{
			ANP4PlayerBase* pPlayerCast = Cast<ANP4PlayerBase>(pOwnerActor);

			if (pPlayerCast)
			{
				//pPlayerCast->
			}
		}
	}

}


