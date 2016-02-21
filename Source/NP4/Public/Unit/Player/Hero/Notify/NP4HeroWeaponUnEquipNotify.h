// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimNotifies/AnimNotify.h"
#include "NP4HeroWeaponUnEquipNotify.generated.h"

/**
 * 
 */
UCLASS()
class NP4_API UNP4HeroWeaponUnEquipNotify : public UAnimNotify
{
	GENERATED_BODY()
	
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
	
};
