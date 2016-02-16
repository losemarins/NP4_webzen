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
	UBehaviorTreeComponent* BehaviorComp;
	UBlackboardComponent* BlackboardComp;
	FName TargetEnemyKeyName;
	bool isMove;

public:
	void SetTargetEnemy(APawn* NewTarget);

public :
	AAIController_Minion(const FObjectInitializer& ObjectInitializer);
	void Tick(float DeltaTime);
	
};
