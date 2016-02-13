// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIAction.h"
#include "AIAction_Move.generated.h"

/**
 * 
 */
UCLASS()
class NP4_API UAIAction_Move : public UAIAction
{
	GENERATED_BODY()
	
protected :
	FVector	Destination;
	float TargetAcceptanceRadius;

public :
	UAIAction_Move(const FObjectInitializer& ObjectInitializer);
	virtual void Activate() override;
	
	
};
