// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "AIAction_Move.h"
#include "AIController_Minion.h"
#include "AIController.h"
#include "Building_Castle.h"
#include "AIDirector.h"

UAIAction_Move::UAIAction_Move(const FObjectInitializer& ObjectInitializer) 
	:Super(ObjectInitializer)
	, TargetAcceptanceRadius(50)
{

}

void UAIAction_Move::Activate()
{
	check(MyAIController.IsValid());
	Super::Activate();
	
	const FPlayerData* TeamData = MyAIController->GetTeamData();

	if (TeamData != NULL && TeamData->Castle != NULL && TeamData->Castle->GetAIDirector() != NULL)
	{
		const AActor* Actor = TeamData->Castle->GetAIDirector()->GetEnemyCastle();
		if (Actor != NULL)
		{
			Destination = Actor->GetActorLocation();
			MyAIController->MoveToLocation(Destination, TargetAcceptanceRadius, true, true, true);
		}
	}
}
