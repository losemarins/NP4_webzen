// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "AIController_Minion.h"
#include "AIAction_Move.h"
#include "Character_Minion.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AAIController_Minion::AAIController_Minion(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	
}

void AAIController_Minion::Tick(float DeltaTime)
{
	const ACharacter_Minion* MyChar = Cast<ACharacter_Minion>(GetPawn());

	//if (MyChar != NULL && MyChar->GetHealth() <= 0)
	for (int32 Idx = 0; Idx < AllActions.Num(); Idx++)
	{
		CurrentAction = AllActions[Idx];
		if (CurrentAction != NULL)
		{
			CurrentAction->Activate();
		}
	}
}

void AAIController_Minion::SetTargetEnemy(APawn* NewTarget)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(TargetEnemyKeyName, NewTarget);
	}
}