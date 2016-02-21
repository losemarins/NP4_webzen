

#include "NP4.h"
#include "Barrack.h"

void ABarrack::Init()
{
	PrimaryActorTick.bCanEverTick = true;
	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshLoad(TEXT("StaticMesh '/Game/Environment/Meshes/Hero1.Hero1'"));
	if (MeshLoad.Succeeded())
		MeshComp->SetStaticMesh(MeshLoad.Object);

	MeshComp->SetRelativeScale3D(FVector(4.0, 4.0, 4.0));
	RootComponent = MeshComp;
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
