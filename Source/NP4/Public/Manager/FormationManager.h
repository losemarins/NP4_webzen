// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "define.h"
#include "GameFramework/Actor.h"
#include "FormationManager.generated.h"

UCLASS()
class NP4_API UFormationManager : public UObject
{
	GENERATED_BODY()

public :
	TArray<class ANP4CharacterBase*> UnitList;
	TArray<IndianFile_Info> IndianFileInfoArr;
	uint8 ArraySize;
	uint8 Interval;

public :
	UFormationManager();
	void AddUnitList(ANP4CharacterBase* unit);
	TArray<class ANP4CharacterBase*> GetUnitList();
	TArray<IndianFile_Info> GetIndianFileInfo();
	void LineUp();
	uint8 GetArraySize();
};
