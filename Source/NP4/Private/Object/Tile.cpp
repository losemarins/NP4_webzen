// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "Tile.h"


// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_bIsBuild = false;

	// static mesh component를 만든다
	TileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TileMesh"));
	RootComponent = TileMesh;
	ConstructorHelpers::FObjectFinder<UMaterial> OriginalMaterial(TEXT("/Game/StarterContent/Materials/M_Metal_Brushed_Nickel"));
	ConstructorHelpers::FObjectFinder<UMaterial> RedMaterial(TEXT("/Game/Material/Red"));
	ConstructorHelpers::FObjectFinder<UMaterial> GreenMaterial(TEXT("/Game/Material/Green"));
	
	if (RedMaterial.Succeeded())
		m_RadMaterial = RedMaterial.Object;

	if (GreenMaterial.Succeeded())
		m_GreenMaterial = GreenMaterial.Object;

	if (OriginalMaterial.Succeeded())
		m_OriginalMaterial = OriginalMaterial.Object;
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

void ATile::SetMeshMetarial(EColor::Type EColor)
{
	//
	UMaterialInstance* MaterialInstance;
		
	switch (EColor)
	{
	case EColor::Green: 
		MaterialInstance = UMaterialInstanceDynamic::Create(m_GreenMaterial, this);
		TileMesh->SetMaterial(0, MaterialInstance);
		break;
	case EColor::Red:
		MaterialInstance = UMaterialInstanceDynamic::Create(m_RadMaterial, this);
		TileMesh->SetMaterial(0, MaterialInstance);
		break;
	case EColor::Original:
		MaterialInstance = UMaterialInstanceDynamic::Create(m_OriginalMaterial, this);
		TileMesh->SetMaterial(0, MaterialInstance);
		break;
	}

}
