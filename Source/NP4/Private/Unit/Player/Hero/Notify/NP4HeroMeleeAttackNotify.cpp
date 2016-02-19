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
				pPlayerCast->SetbNotifyEnter(true);
			}
		}
	}
}

void UNP4HeroMeleeAttackNotify::NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
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
			UAnimInstance* AnimInstance = MeshComp->AnimScriptInstance;

			if (pPlayerCast && AnimInstance)
			{
				if(pPlayerCast->GetbComboOn() && pPlayerCast->GetCurrentComboStep() != eCombo_Interpol::Combo_Two)
				{
					if (pPlayerCast->GetCurrentComboStep() == eCombo_Interpol::Combo_None)
					{
						pPlayerCast->SetCurrentComboStep(eCombo_Interpol::Combo_One);
						UAnimMontage* pAnimMon = pPlayerCast->GetAnimationMontage_fromArrMontage( 
							eCharacterState::eAttack + (int)pPlayerCast->GetCurrentWeapon()->GetWeaponType() + (int)eCombo_Interpol::Combo_One);
						pPlayerCast->PlayAnimMontage_CheckCurrent(pAnimMon, eCharacterState::eAttack);
					}

					else if (pPlayerCast->GetCurrentComboStep() == eCombo_Interpol::Combo_One)
					{
						pPlayerCast->SetCurrentComboStep(eCombo_Interpol::Combo_Two);
						UAnimMontage* pAnimMon = pPlayerCast->GetAnimationMontage_fromArrMontage(
							eCharacterState::eAttack + (int)pPlayerCast->GetCurrentWeapon()->GetWeaponType() + (int)eCombo_Interpol::Combo_Two);
						pPlayerCast->PlayAnimMontage_CheckCurrent(pAnimMon, eCharacterState::eAttack);
					}
					pPlayerCast->SetbComboOn(false);		
				}

				else
				{
					pPlayerCast->StopAttack();
				}

				pPlayerCast->SetbNotifyEnter(false);				
			}

		}
	}
	
}


