// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_CloseEnough.generated.h"

/**
 * 
 */
UCLASS()
class NP4_API UBTDecorator_CloseEnough : public UBTDecorator
{
	GENERATED_BODY()
	
public :
	UPROPERTY(Category = Distance, EditAnywhere, meta = (DisplayName = "Key Value"))
	float FloatValue;

public :
	//bool CalculateRawConditionValue(UBehaviorTreeComponent * ownerComponent, uint8 * nodeMemory)const override;
	
};
