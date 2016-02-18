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

	UPROPERTY(VisibleAnywhere, Category = "AI")
	class UPawnSensingComponent* PawnSensingComp;
	FTimerHandle TimerHandle_MeleeAttack;
	float MeleeStrikeCooldown;
	float LastMeleeAttackTime;
	float SenseTimeOut;
	float LastSeenTime;
	bool bSensedTarget;
	
protected :
	UCapsuleComponent* MeleeCollisionComp;
	UPROPERTY(EditDefaultsOnly, Category = "Attacking")
	UAnimMontage* MeleeAnimMontage;

public :
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	class UBehaviorTree* BehaviorTree;

public :
	ACharacter_Minion();
	void UpdatePawnData(); // 나중에 base에서 virtual로 할수도있음

	UFUNCTION(Reliable, NetMulticast)
	void SimulateMeleeStrike();
	void SimulateMeleeStrike_Implementation();
	UFUNCTION()
	void OnSeeEnemy(APawn* Pawn);
	void SetEnemyCastle(ABuilding_Castle* Castle);
	UFUNCTION()
	void OnMeleeCompBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	void PerformMeleeStrike(AActor* HitActor);
	void OnRetriggerMeleeStrike();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
};
