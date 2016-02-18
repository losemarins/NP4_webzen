// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "Tile.h"


// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_bIsBuild = true;

	// static mesh component를 만든다
	TileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TileMesh"));
	RootComponent = TileMesh;

}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	TileMesh->SetRelativeRotation(FRotator(0, 0, 90));
	//TileMesh->SetMaterial()
}

// Called every frame
void ATile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

bool ATile::GetBuilding()
{
	return m_bIsBuild;
}

void ATile::SetBuilding(bool NewBuildState)
{
	m_bIsBuild = NewBuildState;
}