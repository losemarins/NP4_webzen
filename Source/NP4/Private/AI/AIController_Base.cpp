// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "AIController_Base.h"
#include "NP4CharacterBase.h"
#include "NP4GameState.h"
#include "AIAction_Move.h"
AAIController_Base::AAIController_Base(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	AllowedActions.Add(UAIAction_Move::StaticClass());
}

uint8 AAIController_Base::GetTeamNum() const
{
	ANP4CharacterBase* const MyChar = Cast<ANP4CharacterBase>(GetPawn());
	return (MyChar != NULL) ? MyChar->GetTeamNum() : EGameTeam::Unknown;
}

struct FPlayerData* AAIController_Base::GetTeamData() const
{
	return GetWorld()->GetGameState<ANP4GameState>()->GetPlayerData(GetTeamNum());
	
}

void AAIController_Base::Possess(APawn* inPawn)
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
