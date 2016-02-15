// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "Character_Minion.h"

ACharacter_Minion::ACharacter_Minion()
{
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->BodyInstance.SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AIControllerClass = AAIController_Minion::StaticClass();
}

void ACharacter_Minion::BeginPlay()
{
	Super::BeginPlay();
	UpdatePawnData();
}

void ACharacter_Minion::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ACharacter_Minion::UpdatePawnData()
{

}
