// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "Character_Minion.h"
#include "AIController_Minion.h"
#include "MyPawnSensingComponent.h"

ACharacter_Minion::ACharacter_Minion()
{
	PrimaryActorTick.bCanEverTick = true;	
	//
	AIControllerClass = AAIController_Minion::StaticClass();
	
	MeleeCollisionComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MeleeCollision"));
	MeleeCollisionComp->AttachTo(RootComponent);
	MeleeCollisionComp->SetRelativeLocation(FVector(50, 0, 20));
	MeleeCollisionComp->SetCapsuleHalfHeight(60);
	MeleeCollisionComp->SetCapsuleRadius(80, false);
	MeleeCollisionComp->bHiddenInGame = false;
	MeleeCollisionComp->SetVisibility(true);

	m_pRightPunchCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("RightPunchCollision"));
	m_pRightPunchCapsule->AttachTo(GetMesh(), "RightHand");
	m_pRightPunchCapsule->bHiddenInGame = false;
	m_pRightPunchCapsule->SetVisibility(true);

	PawnSensingComp = CreateDefaultSubobject<UMyPawnSensingComponent>(TEXT("PawnSensingComp"));
	PawnSensingComp->SetPeripheralVisionAngle(70);
	PawnSensingComp->SightRadius = 300;
	PawnSensingComp->bOnlySensePlayers = 0;
	PawnSensingComp->SensingInterval = 0.1f;
	
	MeleeStrikeCooldown = 1.f;
	SenseTimeOut = 2.f;
	bSensedTarget = false;	
}

void ACharacter_Minion::BeginPlay()
{
	Super::BeginPlay();

	if (PawnSensingComp)
	{
		PawnSensingComp->OnSeePawn.AddDynamic(this, &ACharacter_Minion::OnSeeEnemy);
		//PawnSensingComp->OnHearNoise.AddDynamic(this, &ACharacter_Minion::OnHearNoise);
	}

	if (MeleeCollisionComp)
	{
		MeleeCollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ACharacter_Minion::OnMeleeCompBeginOverlap);
	}

	//if (m_pRightPunchCapsule)
	//{
	//	//m_pRightPunchCapsule->OnComponentBeginOverlap.AddDynamic(this, &ACharacter_Minion::OnAttackCompEndOverlap);
	//	//OnComponentEndOverlap.AddDynamic(this, &ACharacter_Minion::OnAttackCompEndOverlap);
	//}

	//MinionController = Cast<AAIController_Minion>(GetController());
	UpdatePawnData();

	GetCharacterMovement()->MaxWalkSpeed = 100;
	FRotator Rot = GetActorRotation();
	
	Rot.Yaw += 90;
	SetActorRotation(Rot);
	m_AttackValue = 5;
	AnimInstance = GetMesh()->AnimScriptInstance;
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
}

void ACharacter_Minion::NotifyActorBeginOverlap(AActor* OtherActor)
{
	/*Super::NotifyActorBeginOverlap(OtherActor);
	if (OtherActor != this)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, "BeginOverlap");
		if (m_pRightPunchCapsule->IsCollisionEnabled() && isAttack)
		{
			isAttack = false;
			Damaged(AttackSecond, OtherActor);
		}
	}*/
}

void ACharacter_Minion::OnAttackCompEndOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor != this/* && isAttack*/)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, "BeginOverlap");
		Damaged(AttackSecond, OtherActor);
	}
}

void ACharacter_Minion::SetCollisionChannel(uint8 TeamNum)
{
	if (TeamNum == EGameTeam::Player)
	{
		//m_pRightPunchCapsule->SetCollisionObjectType(ECollisionChannel::ECC_EngineTraceChannel1);
		MeleeCollisionComp->SetCollisionObjectType(ECollisionChannel::ECC_EngineTraceChannel2);
		MeleeCollisionComp->SetCollisionResponseToAllChannels(ECR_Ignore);
		//m_pRightPunchCapsule->SetCollisionResponseToAllChannels(ECR_Ignore);
		
		//m_pRightPunchCapsule->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel2, ECollisionResponse::ECR_Ignore);
		///m_pRightPunchCapsule->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel3, ECollisionResponse::ECR_Overlap);
		//m_pRightPunchCapsule->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel4, ECollisionResponse::ECR_Overlap);

		MeleeCollisionComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel1, ECollisionResponse::ECR_Ignore);
		MeleeCollisionComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel3, ECollisionResponse::ECR_Ignore);
		MeleeCollisionComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel4, ECollisionResponse::ECR_Overlap);
	}

	else
	{
		//m_pRightPunchCapsule->SetCollisionObjectType(ECollisionChannel::ECC_EngineTraceChannel3);
		MeleeCollisionComp->SetCollisionObjectType(ECollisionChannel::ECC_EngineTraceChannel4);

		MeleeCollisionComp->SetCollisionResponseToAllChannels(ECR_Ignore);
		//m_pRightPunchCapsule->SetCollisionResponseToAllChannels(ECR_Ignore);

		//m_pRightPunchCapsule->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
		//m_pRightPunchCapsule->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel1, ECollisionResponse::ECR_Overlap);
		//m_pRightPunchCapsule->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel2, ECollisionResponse::ECR_Overlap);
		//m_pRightPunchCapsule->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel4, ECollisionResponse::ECR_Ignore);
		
		MeleeCollisionComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel1, ECollisionResponse::ECR_Ignore);
		MeleeCollisionComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel2, ECollisionResponse::ECR_Overlap);
		MeleeCollisionComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel3, ECollisionResponse::ECR_Ignore);
		MeleeCollisionComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel6, ECollisionResponse::ECR_Ignore);
	}
}

void ACharacter_Minion::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (bSensedTarget && (GetWorld()->TimeSeconds - LastSeenTime) > SenseTimeOut)
	{
		AAIController_Minion* MinionController = Cast<AAIController_Minion>(GetController());
		if (MinionController)
		{
			MinionController->SetTargetEnemy(nullptr);
			//if (!AnimInstance->Montage_IsPlaying(MeleeAnimMontage))
				//MinionController->SetIsClose(false);

			if (AnimInstance->Montage_GetIsStopped(MeleeAnimMontage)
				&& AnimInstance->Montage_GetIsStopped(ReactAnimMontage))
			{
				MinionController->SetIsMove(false);
			}
		}
	}
}

void ACharacter_Minion::UpdatePawnData()
{

}

//시야에 적이 보이면 호출되는 함수
void ACharacter_Minion::OnSeeEnemy(APawn* Pawn)
{
	AAIController_Minion* MinionController = Cast<AAIController_Minion>(GetController());

	if (!IsAlive() || MinionController->GetTargetEnemy())
		return;

	//사운드설정
	/*if (!bSensedTarget)
	{
		BroadcastUpdateAudioLoop(true);
	}*/

	LastSeenTime = GetWorld()->GetTimeSeconds();
	bSensedTarget = true;
	ANP4CharacterBase* SensedPawn = Cast<ANP4CharacterBase>(Pawn);

	if (MinionController && SensedPawn->IsAlive() && MyTeamNum != SensedPawn->GetTeamNum())
	{
		MinionController->SetTargetEnemy(SensedPawn);
	}
}

void ACharacter_Minion::OnMeleeCompBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	TimerHandle_MeleeAttack.Invalidate();
	PerformMeleeStrike(OtherActor);
	GetWorldTimerManager().SetTimer(TimerHandle_MeleeAttack, this, &ACharacter_Minion::OnRetriggerMeleeStrike, MeleeStrikeCooldown, true);
}

void ACharacter_Minion::OnRetriggerMeleeStrike()
{
	/* Apply damage to a single random pawn in range. */
	TArray<AActor*> Overlaps;
	MeleeCollisionComp->GetOverlappingActors(Overlaps, ANP4CharacterBase::StaticClass());
	
	for (int32 i = 0; i < Overlaps.Num(); i++)
	{
		ANP4CharacterBase* OverlappingPawn = Cast<ANP4CharacterBase>(Overlaps[i]);
		if (OverlappingPawn)
		{
			PerformMeleeStrike(OverlappingPawn);
			//break; /* Uncomment to only attack one pawn maximum */
		}
	}

	/* No pawns in range, cancel the retrigger timer */
	if (Overlaps.Num() == 0)
	{
		TimerHandle_MeleeAttack.Invalidate();
	}
}

void ACharacter_Minion::PerformMeleeStrike(AActor* HitActor)
{
	if (LastMeleeAttackTime > GetWorld()->GetTimeSeconds() - MeleeStrikeCooldown)
	{
		/* Set timer to start attacking as soon as the cooldown elapses. */
		if (!TimerHandle_MeleeAttack.IsValid())
		{
			// TODO: Set Timer
		}

		/* Attacked before cooldown expired */
		return;
	}

	if (HitActor && HitActor != this && IsAlive())
	{
		ACharacter* OtherPawn = Cast<ACharacter>(HitActor);
		if (OtherPawn)
		{
			/*ASPlayerState* MyPS = Cast<ASPlayerState>(PlayerState);
			ASPlayerState* OtherPS = Cast<ASPlayerState>(OtherPawn->PlayerState);

			if (MyPS && OtherPS)
			{*/
			if (MyTeamNum == Cast<ANP4CharacterBase>(OtherPawn)->GetTeamNum())
				{
					/* Do not attack other zombies. */
					return;
				}

				/* Set to prevent a zombie to attack multiple times in a very short time */
				LastMeleeAttackTime = GetWorld()->GetTimeSeconds();

				//FPointDamageEvent DmgEvent;
				//DmgEvent.DamageTypeClass = PunchDamageType;
				//DmgEvent.Damage = MeleeDamage;

				//HitActor->TakeDamage(DmgEvent.Damage, DmgEvent, GetController(), this);
		
				//AAIController_Minion* MinionController = Cast<AAIController_Minion>(GetController());
				//MinionController->StopMovement();
				SimulateMeleeStrike();
		//	}
		}
	}
}

void ACharacter_Minion::SetEnemyCastle(ABuilding_Castle* Castle)
{
	Cast<AAIController_Minion>(GetController())->SetEnemyCastle(Castle);
}

void ACharacter_Minion::SimulateMeleeStrike_Implementation()
{
	if (!AnimInstance->Montage_IsPlaying(MeleeAnimMontage))
	{
		PlayAnimMontage(MeleeAnimMontage);

		AAIController_Minion* MinionController = Cast<AAIController_Minion>(GetController());
		if (MinionController)
		{
			MinionController->SetIsMove(true);
			//MinionController->SetIsClose(true);
		}
	}
}

void ACharacter_Minion::Damaged(float Second, AActor* OtherActor)
{
	if (AnimInstance->Montage_IsPlaying(MeleeAnimMontage))
	{
		Cast<ANP4CharacterBase>(OtherActor)->Damaged_Call(m_AttackValue);
	}
}

void ACharacter_Minion::ActionHit(FVector _Dir)
{
	if (!AnimInstance->Montage_IsPlaying(ReactAnimMontage))
	{
		PlayAnimMontage(ReactAnimMontage);
		AAIController_Minion* MinionController = Cast<AAIController_Minion>(GetController());
		if (MinionController)
			MinionController->SetIsMove(true);
	}
}

void ACharacter_Minion::StopHit()
{

}
