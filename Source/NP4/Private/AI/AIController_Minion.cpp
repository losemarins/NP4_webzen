// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "AIController_Minion.h"
#include "AIAction_Move.h"
AAIController_Minion::AAIController_Minion(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	AllowedActions.Add(UAIAction_Move::StaticClass());
}

void AAIController_Minion::Possess(APawn* inPawn)
{
	Super::Possess(inPawn);
	AllActions.Reset();
	for (int32 Idx = 0; Idx < AllowedActions.Num(); Idx++)
	{
		UAIAction* Action = NewObject<UAIAction>(this, AllowedActions[Idx]);
		check(Action);
		Action->SetController(this);
		AllActions.Add(Action);
	}
}

