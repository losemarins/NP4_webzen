// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "Define.h"
#include "AIController_Base.generated.h"

/**
 * 
 */

class UAIAction;
UCLASS()
class NP4_API AAIController_Base : public AAIController
{
	GENERATED_BODY()
	
public :
	TArray<TSubclassOf<UAIAction> > AllowedActions;
	TArray<UAIAction*> AllActions;
	UAIAction* CurrentAction;

protected :


public :
	AAIController_Base(const FObjectInitializer& ObjectInitializer);

	uint8 GetTeamNum() const;
	struct FPlayerData* GetTeamData() const;
};
