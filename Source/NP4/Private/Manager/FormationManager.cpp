// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "FormationManager.h"
#include "NP4CharacterBase.h"

UFormationManager::UFormationManager()
{
	ArraySize = 10;
	Interval = 100;
	IndianFile_Info Info;

	for (int j = 0; j < ArraySize / 2; j++)
	{
		Info.Pos = FVector::ZeroVector;
		Info.Character = nullptr;
		Info.Pos.X -= Interval * j;
		IndianFileInfoArr.Add(Info); 

		for (int i = 0; i < ArraySize; i++)
		{
			if (i % 2 == 1)
			{
				Info.Pos = FVector::ZeroVector;
				Info.Character = nullptr;
				Info.Pos.Y += Interval * (i / 2 + 1);
				Info.Pos.X -= Interval * j;
				IndianFileInfoArr.Add(Info);
			}

			else
			{
				Info.Pos = FVector::ZeroVector;
				Info.Character = nullptr;
				Info.Pos.Y -= Interval * (i / 2 + 1);
				Info.Pos.X -= Interval * j;
				IndianFileInfoArr.Add(Info);
			}
		}
	}
}

void UFormationManager::AddUnitList(ANP4CharacterBase* unit)
{
	UnitList.Add(unit);
}

TArray<class ANP4CharacterBase*> UFormationManager::GetUnitList()
{
	return UnitList;
}

TArray<IndianFile_Info> UFormationManager::GetIndianFileInfo()
{
	return IndianFileInfoArr;
}

void UFormationManager::LineUp()
{

}

uint8 UFormationManager::GetArraySize()
{
	return ArraySize * (ArraySize / 2);
}
