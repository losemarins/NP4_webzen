// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "NP4ItemManager.h"


// Sets default values
ANP4ItemManager::ANP4ItemManager()
{
}

int ANP4ItemManager::GetItemArrNum()
{
	return m_ArrDefaultItem.Num();
}

TSubclassOf<class AWeaponBase> ANP4ItemManager::GetItemByIndex(int _idx)
{
	if (_idx >= m_ArrDefaultItem.Num())
	{
		return NULL;
	}
	return m_ArrDefaultItem[_idx];
}