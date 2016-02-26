// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "FormationManager.h"
#include "NP4CharacterBase.h"

UFormationManager::UFormationManager()
{
	FVector Pos;
	Pos = FVector::ZeroVector;
	Indian_FilePos.Add(Pos);

	for (int i = 0; i < 10; i++)
	{
		if (i % 2 == 1)
		{
			Pos = FVector::ZeroVector;
			Pos.X += 200 * (i / 2 + 1);
			Indian_FilePos.Add(Pos);
		}

		else
		{
			Pos = FVector::ZeroVector;
			Pos.X -= 200 * (i / 2 + 1);
			Indian_FilePos.Add(Pos);
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

TArray<FVector> UFormationManager::GetIndianFilePos()
{
	return Indian_FilePos;
}