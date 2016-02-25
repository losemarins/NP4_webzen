// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Define.h"
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
	class UMyPawnSensingComponent* PawnSensingComp;
	//class AAIController_Minion* MinionController;
	UAnimInstance* AnimInstance;
	FTimerHandle TimerHandle_MeleeAttack;
	float MeleeStrikeCooldown;
	float LastMeleeAttackTime;
	float SenseTimeOut;
	float LastSeenTime;

	//공격시 딜레이를 위한 변수
	float AttackStartTime;
	bool bSensedTarget;
	bool isDie;
protected :
	//UPROPERTY(VisibleAnywhere, Category = "Attacking")
	//UCapsuleComponent* MeleeCollisionComp;

	//UPROPERTY(VisibleAnywhere, Category = "Attacking")
	//UCapsuleComponent* AttackCollisionComp;

	UPROPERTY(EditDefaultsOnly, Category = "Attacking")
	UAnimMontage* MeleeAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Die")
	UAnimMontage* DieAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "React")
	UAnimMontage* ReactAnimMontage;

public :
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, Category = "AI")
	EGameStrategy StrategyType;

public :
	ACharacter_Minion();
	void UpdatePawnData(); // 나중에 base에서 virtual로 할수도있음
	void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UFUNCTION(Reliable, NetMulticast)
	void SimulateMeleeStrike();
	void SimulateMeleeStrike_Implementation();

	UFUNCTION()
	void OnSeeEnemy(APawn* Pawn);
	void SetEnemyCastle(ABuilding_Castle* Castle);
	void SetCollisionChannel(uint8 TeamNum);

	UFUNCTION()
	void OnMeleeCompBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	void OnAttackCompEndOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	void PerformMeleeStrike(AActor* HitActor);
	void OnRetriggerMeleeStrike();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	float AttackSecond;
	void Damaged(float Second, AActor* OtherActor);

	/* Action */
	virtual void ActionHit(FVector _Dir = FVector(0, 0, 0));
	virtual void StopHit();
	virtual void ActionDie();
	virtual void StopDie();
};
