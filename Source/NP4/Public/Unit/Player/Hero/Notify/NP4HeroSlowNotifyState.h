// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "NP4HeroSlowNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class NP4_API UNP4HeroSlowNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "MySlow")
	float m_fSlowRatio;

	UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "MySlow")
	bool m_OnlySlowMe;


	void NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime) override;
	void NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation) override;
	
};
