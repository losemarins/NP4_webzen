// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "AIAction.h"

UAIAction::UAIAction(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UAIAction::SetController(AAIController_Base* InOwner)
{
	MyAIController = InOwner;
}

void UAIAction::Activate()
{

}
