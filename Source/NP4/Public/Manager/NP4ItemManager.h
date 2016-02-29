// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "WeaponBase.h"
#include "NP4SkillBase.h"
#include "NP4ItemManager.generated.h"

UCLASS()
class NP4_API ANP4ItemManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANP4ItemManager();

public:
	UPROPERTY(EditDefaultsOnly, Category = Inventory)
	TArray<TSubclassOf<class AWeaponBase>> m_ArrDefaultItem;

	UPROPERTY(EditDefaultsOnly, Category = Skill)
	TArray<TSubclassOf<class ANP4SkillBase>> m_ArrDefaultSkill;

public:
	void InitItemManager();
	int GetItemArrNum();
	TSubclassOf<class AWeaponBase> GetItemByIndex(int _idx);
	TSubclassOf<class AWeaponBase> GetItemByName(FName ItemName);
	AWeaponBase* Spawn_NewWeaponItem(UWorld* pWorld, eItemID _ItemID);
	
	TSubclassOf<class ANP4SkillBase> GetSkillByIndex(FName _ItemName);
};
