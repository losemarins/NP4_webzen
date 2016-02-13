// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "NP4CharacterBase.generated.h"

UCLASS()
class NP4_API ANP4CharacterBase : public ACharacter
{
	GENERATED_BODY()

protected :
	uint8 MyTeamNum;

public:
	// Sets default values for this character's properties
	ANP4CharacterBase();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

public :
	void SetTeamNum(uint8 NewTeamNum);
	uint8 GetTeamNum() const;
};
