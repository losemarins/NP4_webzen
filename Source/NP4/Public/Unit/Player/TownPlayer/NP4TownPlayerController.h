// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Unit/Player/NP4PlayerController.h"
#include "NP4TownPlayerController.generated.h"

/**
 * 
 */
class UNP4Input;

UCLASS()
class NP4_API ANP4TownPlayerController : public ANP4PlayerController
{
	GENERATED_BODY()

public:
		ANP4TownPlayerController();

		virtual void SetupInputComponent() override;
	
		/** Custom input handler. */
		UPROPERTY()
		class UNP4Input* InputHandler;
	
};
