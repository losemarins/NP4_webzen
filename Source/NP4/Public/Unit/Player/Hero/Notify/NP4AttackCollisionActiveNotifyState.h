// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "NP4AttackCollisionActiveNotifyState.generated.h"

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class eCollisionType : uint8
{
	eCollision_None = 0,
	eCollision_LeftPunch = 1,
	eCollision_RightPunch = 2,
	eCollision_LeftKick = 3,
	eCollision_RightKick = 4,
	eCollision_Weapon = 5
};

UCLASS()
class NP4_API UNP4AttackCollisionActiveNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	UNP4AttackCollisionActiveNotifyState();

public:
	UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Collision")
	eCollisionType m_eActiveCollisionType;

public:
	virtual void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration) override;
	virtual void NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation) override;
};
