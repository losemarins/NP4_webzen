// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "NP4CameraActor.h"


// Sets default values
ANP4CameraActor::ANP4CameraActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANP4CameraActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANP4CameraActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

