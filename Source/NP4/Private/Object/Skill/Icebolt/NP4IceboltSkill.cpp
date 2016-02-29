// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "NP4CharacterBase.h"
#include "NP4GameState.h"
#include "NP4ItemManager.h"
#include "Object/Skill/Icebolt/NP4IceboltSkill.h"

// Sets default values
ANP4IceboltSkill::ANP4IceboltSkill()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_fProjecttileSpeed = 500.0f;
	m_LoopTime = 1.0f;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> lProjectileMesh(
		TEXT("StaticMesh'/Game/InfinityBladeEffects/Effects/FX_Meshes/ICE/SM_IceShard_06.SM_IceShard_06'"));

	mProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshCom"));

	if (lProjectileMesh.Succeeded())
	{
		mProjectileMesh->SetStaticMesh(lProjectileMesh.Object);
		mProjectileMesh->AttachTo(RootComponent);
	}

	mOurParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MovementParticles"));
	mOurParticleSystem->AttachTo(RootComponent);
	mOurParticleSystem->bAutoActivate = true;
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Ability/Defense/P_Shield_Spawn.P_Shield_Spawn'"));
	if (ParticleAsset.Succeeded())
	{
		mOurParticleSystem->SetTemplate(ParticleAsset.Object);
	}
}

// Called when the game starts or when spawned
void ANP4IceboltSkill::BeginPlay()
{
	Super::BeginPlay();

	//이펙트
	GetWorldTimerManager().SetTimer(mTimerHandle_Particle,
		this, &ANP4IceboltSkill::Wave, m_LoopTime, true,-1.0f);

	//삭제
	FTimerHandle DestroyTimer;
	GetWorldTimerManager().SetTimer(DestroyTimer,
		this, &ANP4IceboltSkill::DestroySkillObject, m_LifeTime, false, -1.0f);
}

void ANP4IceboltSkill::BeginDestroy()
{
	Super::BeginDestroy();
}

// Called every frame
void ANP4IceboltSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ANP4IceboltSkill::Shoot(const FVector& pDirection)
{
	mMovement->Velocity = pDirection * m_fProjecttileSpeed;
}

void ANP4IceboltSkill::Wave()
{
	mOurParticleSystem = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),
		mOurParticleSystem->Template,GetActorLocation(),FRotator::ZeroRotator,true);
}

void ANP4IceboltSkill::DestroySkillObject()
{
	Destroy();
	GetWorldTimerManager().ClearTimer(mTimerHandle_Particle);
	mOurParticleSystem->DestroyComponent();
}

void ANP4IceboltSkill::NotifyActorBeginOverlap(AActor* pOtherActor)
{
	Super::NotifyActorBeginOverlap(pOtherActor);

	ANP4CharacterBase* pOtherCharacter = Cast<ANP4CharacterBase>(pOtherActor);

	if (pOtherCharacter)
	{
		if (pOtherCharacter->GetTeamNum() == m_TeamNum)
		{
			//아군
			///DestroySkillObject();
		}

		else
		{
			ANP4GameState* pGameState = Cast<ANP4GameState>(pOtherCharacter->GetWorld()->GetGameState());

			if (pGameState)
			{
				ANP4ItemManager* pMgr = pGameState->GetItemLoadManager();

				if (pMgr)
				{			
					FVector Location = pOtherCharacter->GetActorLocation();

					for (int idx = 0; idx < 2; ++idx)
					{
						ANP4IceboltSkill* pIcebolt = NULL;
						FVector OtherForward = pOtherCharacter->GetActorForwardVector();
						FRotator Rotation = FRotator(0, idx * 60, 0);
						Rotation.RotateVector(OtherForward);
						Location = Location + OtherForward * 50;
						pIcebolt = pOtherCharacter->GetWorld()->SpawnActor<ANP4IceboltSkill>(pMgr->GetSkillByIndex("IceBolt"), Location, Rotation);
						pIcebolt->Shoot(OtherForward);
					}
				}
			}	
		}
	}
}