// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Building/Dungeon_Building.h"
#include "Define.h"
#include "Building_Castle.generated.h"

/**
 * 
 */

class ANP4CharacterBase;
class UAIDirector;
UCLASS()
class NP4_API ABuilding_Castle : public ADungeon_Building
{
	GENERATED_BODY()
	
private :
	UAIDirector* AIDirector;

public :
	TSubclassOf<ANP4CharacterBase> CharClass;
	
public :
	virtual void PostInitializeComponents() override;

public:
	ABuilding_Castle(const FObjectInitializer& ObjectInitializer);
	void OnGameplayStateChange(EGameplayState::Type NewState);
	UAIDirector* GetAIDirector() const { return AIDirector; }
	//void SpawnMinions();
	
};
