// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "define.h"
#include "AIDirector.generated.h"


class ABuilding_Castle;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NP4_API UAIDirector : public UActorComponent
{
	GENERATED_BODY()

private :
	uint8 MyTeamNum;
	TWeakObjectPtr<ABuilding_Castle> EnemyBrewery;
	uint8 ProductNum;
	float CustomScale;

public:	
	// Sets default values for this component's properties
	UAIDirector();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

public :
	void OnGameplayStateChange(EGameplayState::Type NewState);
	void SpawnMinions();
	uint8 GetTeamNum() const;
};
