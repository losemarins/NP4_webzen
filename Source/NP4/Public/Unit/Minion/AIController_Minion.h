// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Define.h"
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
	FName IsDie;
	FName IsMove;
	FName Strategy;
	FName MoveLoc;

	virtual void Possess(class APawn* InPawn);
	virtual void UnPossess() override;

public:
	void SetTargetEnemy(AActor* NewTarget);
	void SetEnemyCastle(ABuilding_Castle* EnemyCastle);
	void SetIsDie(bool value);
	void SetIsMove(bool value);
	void SetStrategyType(uint8 type);
	void SetMoveLoc(FVector Loc);
	UObject* GetTargetEnemy();
	uint8 GetStrategyType();

public :
	AAIController_Minion(const FObjectInitializer& ObjectInitializer);
	void Tick(float DeltaTime);
	
};
