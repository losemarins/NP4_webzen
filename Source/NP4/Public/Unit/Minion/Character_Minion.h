// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Unit/NP4CharacterBase.h"
#include "Character_Minion.generated.h"

/**
 * 
 */
UCLASS()
class NP4_API ACharacter_Minion : public ANP4CharacterBase
{
	GENERATED_BODY()
	class UPawnSensingComponent* PawnSensingComp;

public :
	ACharacter_Minion();
	void UpdatePawnData(); // 나중에 base에서 virtual로 할수도있음
	UFUNCTION()
	void OnSeeEnemy(APawn* Pawn);
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
};
