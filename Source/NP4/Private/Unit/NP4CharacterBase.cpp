// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "NP4CharacterBase.h"


// Sets default values
ANP4CharacterBase::ANP4CharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->AttachTo(RootComponent);
	Health = 100;
}

// Called when the game starts or when spawned
void ANP4CharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANP4CharacterBase::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ANP4CharacterBase::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void ANP4CharacterBase::SetTeamNum(uint8 NewTeamNum)
{
	MyTeamNum = NewTeamNum;
}

uint8 ANP4CharacterBase::GetTeamNum() const
{
	return MyTeamNum;
}

float ANP4CharacterBase::PlayNP4AnimationMontage(UAnimMontage* _pAnimMontage)
{
	return PlayAnimMontage(_pAnimMontage);
}

void ANP4CharacterBase::StopNP4AnimationMontage(UAnimMontage* _pAnimMontage)
{
	StopAnimMontage(_pAnimMontage);
}

bool ANP4CharacterBase::IsAlive()
{
	return Health > 0;
}