// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Define.h"
#include "Unit/Notify/NP4CollisionNotify.h"
#include "NP4CollisionNotify_Player.generated.h"

/**
 * 
 */
UCLASS()
class NP4_API UNP4CollisionNotify_Player : public UNP4CollisionNotify
{
	GENERATED_BODY()
	
public:
	UNP4CollisionNotify_Player();

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
