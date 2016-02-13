// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Define.h"
#include "AIAction.generated.h"

/**
 * 
 */

class AAIController_Base;
UCLASS()
class NP4_API UAIAction : public UObject
{
	GENERATED_BODY()
	
protected :
	TWeakObjectPtr<AAIController_Base>	MyAIController;

public :
	UAIAction(const FObjectInitializer& ObjectInitializer);
	void SetController(AAIController_Base* InOwner);
	virtual void Activate();
};
