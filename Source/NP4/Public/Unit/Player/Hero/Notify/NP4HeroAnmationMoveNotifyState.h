// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "NP4PlayerBase.h"
#include "NP4HeroAnmationMoveNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class NP4_API UNP4HeroAnmationMoveNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnyWhere,BluePrintReadWrite, Category = "MyMove")
	float m_fMoveSpeed;

public:
	virtual void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration) override;
	virtual void NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime) override;
	
};
