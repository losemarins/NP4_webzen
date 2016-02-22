// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "FormationManager.h"
#include "NP4CharacterBase.h"

void UFormationManager::AddUnitList(ANP4CharacterBase* unit)
{
	UnitList.Add(unit);
}

TArray<class ANP4CharacterBase*> UFormationManager::GetUnitList()
{
	return UnitList;
}

