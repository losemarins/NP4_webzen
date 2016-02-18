// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "NP4PlayerBase.h"
#include "NP4HeroMeleeAttackNotify.generated.h"

/**
 * 
 */
UCLASS()
class NP4_API UNP4HeroMeleeAttackNotify : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	eCombo_Interpol m_eCurrentComboNum;
	bool m_bNextSectionReady;

public:
	virtual void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration) override;
	virtual void NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime) override;
	virtual void NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation) override;
	
	

};
