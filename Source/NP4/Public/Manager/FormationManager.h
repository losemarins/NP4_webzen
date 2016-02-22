// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "FormationManager.generated.h"

UCLASS()
class NP4_API UFormationManager : public UObject
{
	GENERATED_BODY()

public :
	TArray<class ANP4CharacterBase*> UnitList;
	
public :
	void AddUnitList(ANP4CharacterBase* unit);
	TArray<class ANP4CharacterBase*> GetUnitList();
};
