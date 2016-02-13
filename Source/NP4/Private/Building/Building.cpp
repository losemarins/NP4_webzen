// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "Building.h"


// Sets default values
ABuilding::ABuilding(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
}

// Called when the game starts or when spawned
void ABuilding::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABuilding::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void ABuilding::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}