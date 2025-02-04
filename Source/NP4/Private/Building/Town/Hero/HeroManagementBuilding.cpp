// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "HeroManagementBuilding.h"




void AHeroManagementBuilding::Init()
{
	PrimaryActorTick.bCanEverTick = true;
	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshLoad(TEXT("StaticMesh '/Game/Environment/Meshes/Hero1.Hero1'"));
	if(MeshLoad.Succeeded())
		MeshComp->SetStaticMesh(MeshLoad.Object);

	MeshComp->SetRelativeScale3D(FVector(4.0, 4.0, 4.0));
	RootComponent = MeshComp;
	Super::Init();
	
}

void AHeroManagementBuilding::BeginPlay()
{
	Super::BeginPlay();
}

void AHeroManagementBuilding::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

AHeroManagementBuilding::AHeroManagementBuilding()
{
	Init();
}
