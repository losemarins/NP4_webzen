// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "NP4PlayerBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "NP4HeroSlowNotifyState.h"

void UNP4HeroSlowNotifyState::NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

	if (m_OnlySlowMe)
	{
		if (MeshComp)
		{
			AActor* pOwnerActor = MeshComp->GetOwner();
			if (pOwnerActor)
			{
				ANP4PlayerBase* pPlayerCast = Cast<ANP4PlayerBase>(pOwnerActor);

				if (pPlayerCast)
				{
					//pPlayerCast->
					UGameplayStatics::SetGlobalTimeDilation(pPlayerCast, 0.2f);
				}
			}
		}
	}

	else
	{
		if (MeshComp)
		{
			AActor* pOwnerActor = MeshComp->GetOwner();
			if (pOwnerActor)
			{
				ANP4PlayerBase* pPlayerCast = Cast<ANP4PlayerBase>(pOwnerActor);

				if (pPlayerCast)
				{
					pPlayerCast->GetWorld()->GetWorldSettings()->TimeDilation = 0.2f;
				}
			}
		}
	}	
}

void UNP4HeroSlowNotifyState::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	if (m_OnlySlowMe)
	{
		if (MeshComp)
		{
			AActor* pOwnerActor = MeshComp->GetOwner();
			if (pOwnerActor)
			{
				ANP4PlayerBase* pPlayerCast = Cast<ANP4PlayerBase>(pOwnerActor);

				if (pPlayerCast)
				{
					//pPlayerCast->
					UGameplayStatics::SetGlobalTimeDilation(pPlayerCast, 1.0f);
					//UGameplayStatics::SetGlobalTimeDilation(pPlayerCast, MeshComp->GetAnimInstance()->GetCurrentActiveMontage()->RateScale);
				}
			}
		}
	}

	else
	{
		if (MeshComp)
		{
			AActor* pOwnerActor = MeshComp->GetOwner();
			if (pOwnerActor)
			{
				ANP4PlayerBase* pPlayerCast = Cast<ANP4PlayerBase>(pOwnerActor);

				if (pPlayerCast)
				{
					pPlayerCast->GetWorld()->GetWorldSettings()->TimeDilation = 1.0f;
				}
			}
		}
	}
}



