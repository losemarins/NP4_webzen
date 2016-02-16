// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "Character_Minion.h"
#include "AIController_Minion.h"
#include "Perception/PawnSensingComponent.h"

ACharacter_Minion::ACharacter_Minion()
{
	PrimaryActorTick.bCanEverTick = true;
	
	GetMesh()->BodyInstance.SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AIControllerClass = AAIController_Minion::StaticClass();
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	PawnSensingComp->SetPeripheralVisionAngle(50);
	PawnSensingComp->SightRadius = 100;
	PawnSensingComp->bOnlySensePlayers = 0;
	PawnSensingComp->SensingInterval = 0.1f;
	GetCharacterMovement()->MaxWalkSpeed = 150;
	
	/*USkeletalMeshComponent* pMesh = GetMesh();
	pMesh->SetWorldRotation(GetControlRotation());
	pMesh->SetRelativeRotation(FRotator(0, 90, 0));*/
	//GetController()->SetActorRotation(FQuat(0, 1, 0, 90));
	FRotator Rot = GetActorRotation();
	Rot.Yaw += 90;
	SetActorRotation(Rot);
}

void ACharacter_Minion::BeginPlay()
{
	Super::BeginPlay();

	if (PawnSensingComp)
	{
		PawnSensingComp->OnSeePawn.AddDynamic(this, &ACharacter_Minion::OnSeeEnemy);
		//PawnSensingComp->OnHearNoise.AddDynamic(this, &ACharacter_Minion::OnHearNoise);
	}
	UpdatePawnData();
}

void ACharacter_Minion::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ACharacter_Minion::UpdatePawnData()
{

}

//시야에 적이 보이면 호출되는 함수
void ACharacter_Minion::OnSeeEnemy(APawn* Pawn)
{
	if (!IsAlive())
		return;

	//사운드설정
	/*if (!bSensedTarget)
	{
		BroadcastUpdateAudioLoop(true);
	}*/

	/*LastSeenTime = GetWorld()->GetTimeSeconds();
	bSensedTarget = true;*/

	AAIController_Minion* MinionController = Cast<AAIController_Minion>(GetController());
	ANP4CharacterBase* SensedPawn = Cast<ANP4CharacterBase>(Pawn);
	if (MinionController && SensedPawn->IsAlive())
	{
		MinionController->SetTargetEnemy(SensedPawn);
		MinionController->StopMovement();
	}
}
