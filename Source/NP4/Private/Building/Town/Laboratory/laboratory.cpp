
#include "NP4.h"
#include "laboratory.h"

void Alaboratory::Init()
{
	PrimaryActorTick.bCanEverTick = true;
	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshLoad(TEXT("StaticMesh '/Game/Environment/Meshes/Hero1.Hero1'"));
	if (MeshLoad.Succeeded())
		MeshComp->SetStaticMesh(MeshLoad.Object);

	MeshComp->SetRelativeScale3D(FVector(4.0, 4.0, 4.0));
	RootComponent = MeshComp;

}

void Alaboratory::BeginPlay()
{
	Super::BeginPlay();
}

void Alaboratory::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

Alaboratory::Alaboratory()
{
	Init();
}
