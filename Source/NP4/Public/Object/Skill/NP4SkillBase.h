// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "NP4SkillBase.generated.h"

UCLASS()
class NP4_API ANP4SkillBase : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnyWhere, Category = "Skill")
	UParticleSystemComponent* mOurParticleSystem;

	UPROPERTY(EditAnyWhere, Category = "Skill")
	class USphereComponent* mCollision;
	
	UPROPERTY(EditAnyWhere, Category = "Skill")
	class UProjectileMovementComponent* mMovement;
	
	UPROPERTY(EditAnyWhere,Category = "Skill")
	UStaticMeshComponent* mProjectileMesh;

	UPROPERTY(EditAnyWhere, Category = "Skill")
	float m_LifeTime;

	uint8 m_TeamNum;

	UPROPERTY(EditAnyWhere,BluePrintReadWrite, Category = "Skill")
	FName m_SkillName;

public:	
	// Sets default values for this actor's properties
	ANP4SkillBase();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	virtual void Shoot(const FVector& pDirection);
	virtual void DestroySkillObject();

	virtual void NotifyActorBeginOverlap(AActor* pOtherActor) override;

	FName FORCEINLINE GetSkillName() { return m_SkillName; }
};
