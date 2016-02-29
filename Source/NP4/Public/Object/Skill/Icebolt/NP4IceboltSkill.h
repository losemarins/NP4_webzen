// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object/Skill/NP4SkillBase.h"
#include "NP4IceboltSkill.generated.h"

/**
 * 
 */
UCLASS()
class NP4_API ANP4IceboltSkill : public ANP4SkillBase
{
	GENERATED_BODY()

public:
	FTimerHandle mTimerHandle_Particle;
	UPROPERTY(EditAnyWhere,BluePrintReadWrite,Category = "Skill")
	float m_fProjecttileSpeed;
	UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Skill")
	float m_LoopTime;

public:
	// Sets default values for this actor's properties
	ANP4IceboltSkill();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;
	virtual void Shoot(const FVector& pDirection);
	virtual void DestroySkillObject();
	virtual void NotifyActorBeginOverlap(AActor* pOtherActor) override;

	void Wave();
};
