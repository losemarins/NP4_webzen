// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "Define.h"
#include "NP4GameInstance.generated.h"

/**
 *  Data �����
    ��� ������ ���� �츮�� ���� ��ȯ�� �ʿ��� �����͸� �����Ѵ�.
	������ 
	UNP4GameInstance* SGI = Cast<UNP4GameInstance>(GetGameInstance());
	if(SGI)
	{
	SGI->�ɹ� ����, �Լ� �� �����ϵ��� 
	}
	by ����
 */

class UInventory;
UCLASS()
class NP4_API UNP4GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	//Get
	FORCEINLINE UInventory* GetInventory() const { return m_Inven; }
	FORCEINLINE EMinion::Type GetMinionType() const { return m_EMinionType; }
	FORCEINLINE EMinionUpgrade::Type GetMinionLevel() const { return m_EminonUpgrade; }
	FORCEINLINE int32 GetStageInfo() const { return m_iStageInfo; }
	FORCEINLINE EGameDifficulty::Type GetGameDifficulty() const { return m_EGameDifficulty; }

	//Set
	FORCEINLINE void SetInventory(UInventory* _inven) { m_Inven = _inven; }
	FORCEINLINE void SetMinionType(EMinion::Type _eminiontype) { m_EMinionType = _eminiontype; }
	FORCEINLINE void SetMinionLevel(EMinionUpgrade::Type _eminionupgrade) { m_EminonUpgrade = _eminionupgrade; }
	FORCEINLINE void SetStageInfo(int32 _istageinfo) { m_iStageInfo = _istageinfo; }
	FORCEINLINE void SetGameDifficulty(EGameDifficulty::Type _egamedifficulty) { m_EGameDifficulty = _egamedifficulty; }

	

private:
	//�κ� 
	UInventory* m_Inven;
	//�̴Ͼ� 
	EMinion::Type m_EMinionType;
	EMinionUpgrade::Type m_EminonUpgrade;
	//�÷��̾� 
	float m_fPlayerHealthMax;
	float m_fPlayerAttackValue;
	//�������� 
	int32 m_iStageInfo;
	EGameDifficulty::Type m_EGameDifficulty;	
};
