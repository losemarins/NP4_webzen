// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "Inventory.h"

UInventory::UInventory()
{

}

void UInventory::AddWeapon_ToInven(AItemBase* _pItem)
{
	for (int i = 0; i < m_pItemInven.Num(); ++i)
	{
		if (m_pItemInven[i]->GetItemID() == _pItem->GetItemID())
		{
			return;
		}
	}

	m_pItemInven.Add(_pItem);
}

void UInventory::DeleteWeapon_InInven(int _ItemUniqueNumber)
{
	for (int i = 0; i < m_pItemInven.Num(); ++i)
	{
		if (m_pItemInven[i]->GetDataBaseKey() == _ItemUniqueNumber)
		{
			m_pItemInven.Remove(m_pItemInven[i]);
		}
	}
}

AItemBase* UInventory::GetitemPointer_fromInven(int _ItemUniqueNumber)
{
	for (int i = 0; i < m_pItemInven.Num(); ++i)
	{
		if (m_pItemInven[i]->GetDataBaseKey() == _ItemUniqueNumber)
		{
			return m_pItemInven[i];
		}
	}

	return NULL;
}

void UInventory::LoadInven_fromFile(FName _FileName)
{
	
}

void UInventory::SaveInven_toFile(FName _FileName)
{

}
