// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "NP4PlayerBase.h"
#include "NP4GameState.h"
#include "Object/Skill/NP4SkillBase.h"
#include "Object/Skill/Icebolt/NP4IceboltSkill.h"
#include "NP4CreateSkillNotify.h"

void UNP4CreateSkillNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && m_eSkillID != eSkillID::eNone)
	{
		AActor* pOwnerActor = MeshComp->GetOwner();
		if (pOwnerActor)
		{
			ANP4PlayerBase* pPlayerCast = Cast<ANP4PlayerBase>(pOwnerActor);

			if (pPlayerCast)
			{
				ANP4GameState* pGameState = Cast<ANP4GameState>(pPlayerCast->GetWorld()->GetGameState());

				if (pGameState)
				{
					ANP4ItemManager* pMgr = pGameState->GetItemLoadManager();

					if (pMgr)
					{
						CreateSkill(pMgr, pPlayerCast);
					}
				}
			}
		}
	}	
}

void UNP4CreateSkillNotify::CreateSkill(ANP4ItemManager* pMgr, ANP4PlayerBase* _playercast)
{
	if (m_CreateBoneName.Num() <= 0)
	{
		CreateSkill_Actor(pMgr,_playercast);
	}
	else
	{
		CreateSkill_BoneArray(pMgr,_playercast);
	}
}

void UNP4CreateSkillNotify::CreateSkill_Actor(ANP4ItemManager* pMgr, ANP4PlayerBase* _playercast)
{
	ANP4IceboltSkill* pIcebolt = NULL;

	////BP를 체크한다.
	if (m_eSkillID == eSkillID::eIcebolt)
	{
		if (pMgr)
		{	
			FVector Location = _playercast->GetActorLocation();
			FRotator Rotation = _playercast->GetActorRotation();
			FVector FowardVec = _playercast->GetActorForwardVector();

			pIcebolt = (ANP4IceboltSkill*)_playercast->GetWorld()->SpawnActor<ANP4IceboltSkill>(pMgr->GetSkillByIndex("IceBolt"), Location, Rotation);
			pIcebolt->Shoot(FowardVec);
		}
	}

	else if (m_eSkillID == eSkillID::eFirebolt)
	{

	}
}

void UNP4CreateSkillNotify::CreateSkill_BoneArray(ANP4ItemManager* pMgr, ANP4PlayerBase* _playercast)
{
	if (m_eSkillID == eSkillID::eIcebolt)
	{
		if (pMgr)
		{
			for (int i = 0; i < m_CreateBoneName.Num(); ++i)
			{
				ANP4IceboltSkill* pIcebolt = NULL;
				FVector Location = _playercast->GetMesh()->GetSocketLocation(m_CreateBoneName[i]);
				FRotator Rotation = _playercast->GetActorRotation();
				FVector FowardVec = _playercast->GetActorForwardVector();

				pIcebolt = _playercast->GetWorld()->SpawnActor<ANP4IceboltSkill>(pMgr->GetSkillByIndex("IceBolt"), Location, Rotation);
				pIcebolt->Shoot(FowardVec);
			}
		}
	}

	else if (m_eSkillID == eSkillID::eFirebolt)
	{

	}
}