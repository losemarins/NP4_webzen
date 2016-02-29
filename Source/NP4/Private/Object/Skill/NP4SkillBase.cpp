// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "NP4CharacterBase.h"
#include "Define.h"
#include "Object/Skill/NP4SkillBase.h"


// Sets default values
ANP4SkillBase::ANP4SkillBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	//mCollision->AttachTo(RootComponent);
	RootComponent = mCollision;

	mMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	mMovement->SetUpdatedComponent(mCollision);
	mMovement->ProjectileGravityScale = 0.0f;

	m_LifeTime = 1.0f;
	m_TeamNum = EGameTeam::Player;

}

// Called when the game starts or when spawned
void ANP4SkillBase::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void ANP4SkillBase::BeginDestroy()
{
	Super::BeginDestroy();
}


// Called every frame
void ANP4SkillBase::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );


}

void ANP4SkillBase::Shoot(const FVector& pDirection)
{

}

void ANP4SkillBase::DestroySkillObject()
{

}

void ANP4SkillBase::NotifyActorBeginOverlap(AActor* pOtherActor)
{
	Super::NotifyActorBeginOverlap(pOtherActor);

	
}