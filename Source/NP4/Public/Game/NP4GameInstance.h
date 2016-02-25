// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "Define.h"
#include "NP4GameInstance.generated.h"

/**
 *  Data 저장용
    멤버 변수를 통해 우리가 레벨 전환시 필요한 데이터를 저장한다.
	사용법은 
	UNP4GameInstance* SGI = Cast<UNP4GameInstance>(GetGameInstance());
	if(SGI)
	{
	SGI->맴버 변수, 함수 로 접근하도록 
	}
	by 정훈
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
	//인벤 
	UInventory* m_Inven;
	//미니언 
	EMinion::Type m_EMinionType;
	EMinionUpgrade::Type m_EminonUpgrade;
	//플레이어 
	float m_fPlayerHealthMax;
	float m_fPlayerAttackValue;
	//스테이지 
	int32 m_iStageInfo;
	EGameDifficulty::Type m_EGameDifficulty;	
};
