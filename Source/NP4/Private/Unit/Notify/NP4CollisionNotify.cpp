// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "NP4CollisionNotify.h"
#include "NP4CharacterBase.h"
#include "Runtime/Engine/Classes/Engine/World.h"

UNP4CollisionNotify::UNP4CollisionNotify()
{
	m_bResetArray = false;
	m_CollType = eCollisionType::eCollision_None;
}

void UNP4CollisionNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	
	if (MeshComp && m_CollType != eCollisionType::eCollision_None)
	{
		AActor* pOwnerActor = MeshComp->GetOwner();
		if (pOwnerActor)
		{
			ANP4CharacterBase* pMyCast = Cast<ANP4CharacterBase>(pOwnerActor);
			if (pMyCast)
			{
				USphereComponent* pCollSphere = pMyCast->GetCollisionSphere(m_CollType);

				if (!pCollSphere)
				{
					//Create Error Messsage.
					return;
				}

				TArray<FHitResult> AllResult;
				float Radius = pCollSphere->GetScaledSphereRadius();
				FVector Start = pMyCast->GetMesh()->GetSocketLocation(m_sSocketName); /*- FVector(Radius*2, Radius*2, Radius*2);*/
				FVector End = pMyCast->GetMesh()->GetSocketLocation(m_sSocketName) + pMyCast->GetActorForwardVector() * 40;/* FVector(Radius*2, Radius*2, Radius*2);*/

				FQuat Qut = pCollSphere->GetSocketQuaternion(m_sSocketName);
				FRotator Rot = pCollSphere->GetComponentRotation();

				pMyCast->GetWorld()->DebugDrawTraceTag = "PlzShowme";
				FCollisionQueryParams Param;
				Param.TraceTag = "PlzShowme";

				pMyCast->GetWorld()->SweepMultiByObjectType(AllResult, Start, End, Qut,
					FCollisionObjectQueryParams::AllObjects,
					FCollisionShape::MakeSphere(Radius), Param);

				for (int i = 0; i < AllResult.Num(); i++)
				{
					if (AllResult[i].GetComponent()->GetName() == TEXT("MeleeCollision"))
					{
						ANP4CharacterBase* pCastOther = Cast<ANP4CharacterBase>(AllResult[i].GetActor());
						
						int32 id = pCastOther->GetUniqeID();

						if (pCastOther->GetTeamNum() != pMyCast->GetTeamNum()
							&& IsAlreadyActorInArray(id) == INDEX_NONE/* && pCastOther->IsHit*/)
						{
							FVector HitDir = pCastOther->GetActorLocation() - pMyCast->GetActorLocation();
							HitDir.Normalize();

							float AttVal = pMyCast->GetDefaultAttackValue();
							if (AttVal == 0)
							{
								//Create Error Message(AttackValue is Zero)
							}

							else
							{
								pCastOther->Damaged_Call(AttVal);
							}

							PushAlreadyDamageArray(id);
							pCastOther->ActionHit(HitDir);
							pCastOther->LaunchCharacter(pMyCast->GetActorForwardVector() * 500, true, true);
						}
					}
				}
			}
		}
	}

	if (m_bResetArray)
	{
		m_ArrAlreadyDamageActor.Empty();
	}
}

/* true일 경우 이미 있는 것이다. */
int32 UNP4CollisionNotify::IsAlreadyActorInArray(int32 _iUniqueID)
{
	//return m_ArrAlreadyDamageActor.Find(_iUniqueID);
	int32 returnval = INDEX_NONE;

	for (int i = 0; i < m_ArrAlreadyDamageActor.Num(); ++i)
	{
		if (m_ArrAlreadyDamageActor[i] == _iUniqueID)
		{
			returnval = i;
		}
	}
	return returnval;
}

void UNP4CollisionNotify::PushAlreadyDamageArray(int _iUniqueID)
{
	m_ArrAlreadyDamageActor.AddUnique(_iUniqueID);
}
