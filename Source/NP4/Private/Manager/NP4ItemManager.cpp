// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "NP4ItemManager.h"


// Sets default values
ANP4ItemManager::ANP4ItemManager()
{
}

void ANP4ItemManager::InitItemManager()
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

TSubclassOf<class AWeaponBase> ANP4ItemManager::GetItemByName(FName _ItemName)
{
	for (int i = 0; i < m_ArrDefaultItem.Num(); ++i)
	{
		if ( m_ArrDefaultItem[i].GetDefaultObject()->GetItemName() == _ItemName)
		{
			return m_ArrDefaultItem[i];
		}
	}

	return NULL;
}

AWeaponBase* ANP4ItemManager::Spawn_NewWeaponItem(eItemID _ItemID)
{
	AWeaponBase* pNewItem = NULL;
	for (int i = 0; i < m_ArrDefaultItem.Num(); ++i)
	{
		if (m_ArrDefaultItem[i].GetDefaultObject()->GetItemID() == _ItemID)
		{
			FActorSpawnParameters SpawnInfo;
			pNewItem = (AWeaponBase*)GetWorld()->SpawnActor<AWeaponBase>(m_ArrDefaultItem[i], SpawnInfo);

			if (pNewItem)
			{
				return pNewItem;
			}
		}
	}

	return NULL;
}