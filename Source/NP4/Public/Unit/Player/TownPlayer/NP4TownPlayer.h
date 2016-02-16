// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "NP4TownPlayer.generated.h"

class ANP4TownPlayerController;
UCLASS()
class NP4_API ANP4TownPlayer : public APawn
{
	GENERATED_BODY()
	
public:		
	// Sets default values for this actor's properties
	ANP4TownPlayer();

	/* Spring Arm */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USpringArmComponent* m_OurCameraSpringArm;
	ANP4TownPlayerController* m_pTownController;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "PlayerController")
	ANP4TownPlayerController* m_pPlayerController;


	/* Camera Value */
	float m_MinSpringArmLength;
	float m_MaxSpringArmLength;

public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void PossessedBy(AController* _pContoller) override;


	void SetSpringArm(FtCameraLocationInfo _Info);
	void SetCameraRotaion(FRotator _Rot);
	void SetSpringArmCameraRotation(FRotator _Rot);

	UCameraComponent* GetCamera();
	USpringArmComponent* GetSpringArm();
	bool IsPlayerControllerNull();

	/* Camera Value  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* m_OurCamera;


};
