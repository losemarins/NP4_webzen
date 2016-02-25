// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "ItemBase.h"
#include "Inventory.generated.h"

/**
 * 
 */
UCLASS()
class NP4_API UInventory : public UObject
{
	GENERATED_BODY()

	UInventory();
	
public:
	// Juhee : UI 연동 변수. Inven Array 다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ItemInven)
	TArray<AItemBase*> m_pItemInven; //임시
	
public:
	void AddWeapon_ToInven(AItemBase* _pItem);
	void DeleteWeapon_InInven(int _ItemUniqueNumber);
	AItemBase* GetitemPointer_fromInven(int _ItemUniqueNumber);

	void LoadInven_fromFile(FName _FileName = "");
	void SaveInven_toFile(FName _FileName = "");
};
