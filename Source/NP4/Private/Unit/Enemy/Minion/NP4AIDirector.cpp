// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "NP4AIDirector.h"


// Sets default values for this component's properties
UNP4AIDirector::UNP4AIDirector()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UNP4AIDirector::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UNP4AIDirector::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

