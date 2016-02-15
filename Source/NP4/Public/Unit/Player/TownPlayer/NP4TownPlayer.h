// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "NP4TownPlayer.generated.h"

class ANP4TownPlayerController;
UCLASS()
class NP4_API ANP4TownPlayer : public AActor
{
	GENERATED_BODY()
	
public:		
	// Sets default values for this actor's properties
	ANP4TownPlayer();

public:
	/* Spring Arm */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USpringArmComponent* m_OurCameraSpringArm;



	ANP4TownPlayerController* m_pTownController;

	/* Camera Value */
	float m_ZoomFactor;
	float m_MinSpringArmLength;
	float m_MaxSpringArmLength;

public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void SetSpringArm(FtCameraLocationInfo _Info);
	void SetCameraRotaion(FRotator _Rot);

	bool IsPlayerControllerNull();

	/* Camera Value  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCameraComponent* m_OurCamera;
};
