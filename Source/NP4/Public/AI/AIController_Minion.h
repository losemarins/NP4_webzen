// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController_Base.h"
#include "AIController_Minion.generated.h"

/**
 * 
 */
UCLASS()
class NP4_API AAIController_Minion : public AAIController_Base
{
	GENERATED_BODY()
	
public :
	AAIController_Minion(const FObjectInitializer& ObjectInitializer);
	virtual void Possess(APawn* inPawn) override;
	
	
};
