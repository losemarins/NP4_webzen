// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimNotifies/AnimNotify.h"
#include "NP4CollisionNotify.generated.h"

/**
 * 
 */
UCLASS()
class NP4_API UNP4CollisionNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	UNP4CollisionNotify();
	
public :
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	eCollisionType m_CollType;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	bool m_bResetArray;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FName m_sSocketName;
	TArray<int32> m_ArrAlreadyDamageActor;

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	int IsAlreadyActorInArray(int32 _id);
	void PushAlreadyDamageArray(int32 _id);
	
};

