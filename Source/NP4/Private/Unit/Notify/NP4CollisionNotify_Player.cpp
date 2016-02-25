// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "NP4CollisionNotify_Player.h"
#include "WeaponBase.h"
#include "NP4CharacterBase.h"

UNP4CollisionNotify_Player::UNP4CollisionNotify_Player()
{
	m_sSocketName = "RightHand";
}

void UNP4CollisionNotify_Player::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp)
	{
		AActor* pOwnerActor = MeshComp->GetOwner();
		if (pOwnerActor)
		{
			ANP4CharacterBase* pMyCast = Cast<ANP4CharacterBase>(pOwnerActor);
			if (pMyCast)
			{
				AWeaponBase* pWeapon = pMyCast->GetCurrentWeapon();
				
				if (pWeapon != NULL)
				{
					TArray<FHitResult> AllResult;
					FVector BoxExtent = pWeapon->GetWeaponCollisionBox()->GetScaledBoxExtent();
					FVector Start = pWeapon->GetWeaponCollisionBox()->GetComponentLocation(); 
					FVector End = pWeapon->GetWeaponCollisionBox()->GetComponentLocation() + pMyCast->GetActorForwardVector() * 40;/* FVector(Radius*2, Radius*2, Radius*2);*/

					FQuat Qut = pWeapon->GetWeaponCollisionBox()->GetComponentQuat();
					//FRotator Rot = pMyCast->GetRightPunchCapsule()->GetComponentRotation();

					pMyCast->GetWorld()->DebugDrawTraceTag = "PlzShowme";
					FCollisionQueryParams Param;
					Param.TraceTag = "PlzShowme";

					pMyCast->GetWorld()->SweepMultiByObjectType(AllResult, Start, End, Qut,
						FCollisionObjectQueryParams::AllObjects,
						FCollisionShape::MakeBox(BoxExtent/2), Param);

					//for (int i = 0; i < AllResult.Num(); i++)
					//{
					//	if (AllResult[i].GetComponent()->GetName() == TEXT("MeleeCollision"))
					//	{
					//		ANP4CharacterBase* pCastOther = Cast<ANP4CharacterBase>(AllResult[i].GetActor());

					//		int32 id = pCastOther->GetUniqeID();

					//		if (pCastOther->GetTeamNum() != pMyCast->GetTeamNum()
					//			&& IsAlreadyActorInArray(id) == INDEX_NONE/* && pCastOther->IsHit*/)
					//		{
					//			FVector HitDir = pCastOther->GetActorLocation() - pMyCast->GetActorLocation();
					//			HitDir.Normalize();

					//			pCastOther->Damaged_Call(5);
					//			PushAlreadyDamageArray(id);
					//			pCastOther->ActionHit(HitDir);
					//		}
					//	}
					//}
				}

				else
				{
					Super::Notify(MeshComp, Animation);
				}
			}
		}
	}

	if (m_bResetArray)
	{
		m_ArrAlreadyDamageActor.Empty();
	}
}
