// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimNotifies/AnimNotify.h"
#include "Define.h"
#include "NP4ItemManager.h"
#include "NP4CreateSkillNotify.generated.h"

/**
 * 
 */
UCLASS()
class NP4_API UNP4CreateSkillNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Skill")
	eSkillID m_eSkillID;

	UPROPERTY(EditAnyWhere,BluePrintReadWrite,Category = "SKill")
	TArray<FName> m_CreateBoneName;
	
	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
	
	void CreateSkill(ANP4ItemManager* pMgr, ANP4PlayerBase* _playercast);
	void CreateSkill_Actor(ANP4ItemManager* pMgr, ANP4PlayerBase* _playercast);
	void CreateSkill_BoneArray(ANP4ItemManager* pMgr, ANP4PlayerBase* _playercast);
};
