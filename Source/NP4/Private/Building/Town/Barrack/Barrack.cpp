

#include "NP4.h"
#include "Barrack.h"

void ABarrack::Init()
{
	PrimaryActorTick.bCanEverTick = true;
	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshLoad(TEXT("StaticMesh '/Game/Environment/Meshes/CannonTower_StaticElement.CannonTower_StaticElement'"));
	if (MeshLoad.Succeeded())
		MeshComp->SetStaticMesh(MeshLoad.Object);

	MeshComp->SetRelativeScale3D(FVector(2.0, 2.0, 2.0));
	RootComponent = MeshComp;
	m_EBuildingType = EBuilding::Barrack;
	Super::Init();

}

void ABarrack::BeginPlay()
{
	Super::BeginPlay();
}

void ABarrack::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

ABarrack::ABarrack()
{
	Init();
}
