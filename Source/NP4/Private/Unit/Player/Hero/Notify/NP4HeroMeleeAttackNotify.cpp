// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "NP4HeroMeleeAttackNotify.h"


void UNP4HeroMeleeAttackNotify::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
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
				m_eCurrentComboNum = pPlayerCast->GetCurrentComboStep();
				m_bNextSectionReady = false;

				pPlayerCast->SetbNotifyEnter(true);
			}
		}
	}
}

void UNP4HeroMeleeAttackNotify::NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime)
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
				if (pPlayerCast->GetbNotifyEnter()  && pPlayerCast->GetbComboOn())
				{
					m_bNextSectionReady = true;
				}
			}
		}
	}

}

void UNP4HeroMeleeAttackNotify::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
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
				if (m_bNextSectionReady == true)
				{
					if (m_eCurrentComboNum == eCombo_Interpol::Combo_None)
					{
						pPlayerCast->SetCurrentComboStep(eCombo_Interpol::Combo_DownAttack);
						MeshComp->GetAnimInstance()->Montage_JumpToSection(TEXT("Combo_DownAttack"), pPlayerCast->GetCurrentMontage());

					}

					else if (m_eCurrentComboNum == eCombo_Interpol::Combo_DownAttack)
					{
						pPlayerCast->SetCurrentComboStep(eCombo_Interpol::Combo_Kick);
						MeshComp->GetAnimInstance()->Montage_JumpToSection(TEXT("Combo_Kick"), pPlayerCast->GetCurrentMontage());
					}


					else if (m_eCurrentComboNum == eCombo_Interpol::Combo_Kick)
					{

					}

					m_bNextSectionReady = false;
				}
				else
				{
					//pPlayerCast->StopAttack();
				}

				pPlayerCast->SetbComboOn(false);
				pPlayerCast->SetbNotifyEnter(false);
			}
		}
	}
	
}


