// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "NP4HeroAnmationMoveNotifyState.h"

void UNP4HeroAnmationMoveNotifyState::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
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
				
			}
		}
	}
}

void UNP4HeroAnmationMoveNotifyState::NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime)
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
				pPlayerCast->AddMovementInput(pPlayerCast->GetCapsuleComponent()->GetForwardVector(), FrameDeltaTime * m_fMoveSpeed,false);
			}
		}
	}

}