// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "AIController_Minion.h"
#include "AIAction_Move.h"
#include "Character_Minion.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Building_Castle.h"

AAIController_Minion::AAIController_Minion(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	BehaviorComp = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
	BlackboardComp = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));
	TargetEnemyKeyName = "TargetEnemy";
	TargetCastleKeyName = "EnemyCastle";
	IsDie = "IsDie";
	IsMove = "IsMove";
}

void AAIController_Minion::Possess(class APawn* InPawn)
{
	Super::Possess(InPawn);

	ACharacter_Minion* Minion = Cast<ACharacter_Minion>(InPawn);
	if (Minion)
	{
		if (Minion->BehaviorTree->BlackboardAsset)
			BlackboardComp->InitializeBlackboard(*Minion->BehaviorTree->BlackboardAsset);

		BehaviorComp->StartTree(*Minion->BehaviorTree);
	}
}

void AAIController_Minion::UnPossess()
{
	Super::UnPossess();

	/* Stop any behavior running as we no longer have a pawn to control */
	BehaviorComp->StopTree();
}

void AAIController_Minion::Tick(float DeltaTime)
{
	const ACharacter_Minion* MyChar = Cast<ACharacter_Minion>(GetPawn());

	//if (MyChar != NULL && MyChar->GetHealth() <= 0)
	for (int32 Idx = 0; Idx < AllActions.Num(); Idx++)
	{
		CurrentAction = AllActions[Idx];
		if (CurrentAction != NULL && isMove)
		{
			CurrentAction->Activate();
		}
	}
}

void AAIController_Minion::SetTargetEnemy(AActor* NewTarget)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(TargetEnemyKeyName, NewTarget);
	}
}

void AAIController_Minion::SetEnemyCastle(ABuilding_Castle* EnemyCastle)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(TargetCastleKeyName, EnemyCastle);
	}
}

UObject* AAIController_Minion::GetTargetEnemy()
{
	if (BlackboardComp)
	{
		return BlackboardComp->GetValueAsObject(TargetEnemyKeyName);
	}
	return nullptr;
}

void AAIController_Minion::SetIsDie(bool value)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsBool(IsDie, value);
	}
}

void AAIController_Minion::SetIsMove(bool value)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsBool(IsMove, value);
	}
}
