// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController_Base.h"
#include "AIController_Minion.generated.h"

/**
 * 
 */
class ABuilding_Castle;
UCLASS()
class NP4_API AAIController_Minion : public AAIController_Base
{
	GENERATED_BODY()
	UBehaviorTreeComponent* BehaviorComp;
	UBlackboardComponent* BlackboardComp;
	bool isMove;

	FName TargetEnemyKeyName;
	FName TargetCastleKeyName;

	virtual void Possess(class APawn* InPawn);
	virtual void UnPossess() override;

public:
	void SetTargetEnemy(APawn* NewTarget);
	void SetEnemyCastle(ABuilding_Castle* EnemyCastle);
	UObject* GetTargetEnemy();

public :
	AAIController_Minion(const FObjectInitializer& ObjectInitializer);
	void Tick(float DeltaTime);
	
};
