// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "NP4MathManager.h"
#include "Kismet/KismetMathLibrary.h"

UNP4MathManager::UNP4MathManager()
{
}

bool UNP4MathManager::TraceNearEnemyObject_ByBox(
	ANP4CharacterBase* _pMyObject, ANP4CharacterBase*& _pTarget, float _fDist, FVector _vBoxExtent, FRotator& _rResultRot)
{
	if (_pTarget && !_pTarget->IsAlive())
	{
		_pTarget = NULL;
	}

	TArray<FHitResult> AllResult;

	UWorld* pWorld = _pMyObject->GetWorld();
	FVector MyLocation = _pMyObject->GetActorLocation();
	FVector vRightVec = _pMyObject->GetActorRightVector();
	FVector vForwardVec = _pMyObject->GetActorForwardVector();
	FQuat FQut = _pMyObject->GetActorQuat();

	if (!pWorld) return false;

	pWorld->DebugDrawTraceTag = "PlzShowme";
	FCollisionQueryParams Param;
	Param.TraceTag = "PlzShowme";

	FVector EndPosition;
	FVector StartPosition;

	//���� �˻縦 �Ѵ�.
	AllResult.Empty();

	EndPosition = MyLocation + (vRightVec * (_vBoxExtent.Y)) + (vForwardVec * (_vBoxExtent.X + _fDist));
	StartPosition = MyLocation - (vRightVec * (_vBoxExtent.Y)) + (vForwardVec * (_vBoxExtent.X + _fDist));

	pWorld->SweepMultiByObjectType(AllResult, StartPosition, EndPosition, FQut,
		FCollisionObjectQueryParams::AllObjects,
		FCollisionShape::MakeBox(_vBoxExtent), Param);

	//���� �� ���� ���� �Ѵ�.
	for (int i = 0; i < AllResult.Num();)
	{
		if (AllResult[i].GetActor() == _pMyObject ||
			AllResult[i].GetComponent()->GetName() != TEXT("MeleeCollision"))
		{
			AllResult.RemoveAt(i);
		}

		else
			++i;
	}

	//������ �ƹ� �͵� ���ٴ� ���̴�.
	if (AllResult.Num() <= 0)
	{
		_pTarget = NULL;
		return false;
	}

	int iMostCloseObjectIdx = -1;
	float fMostCloseDist = 9999.f;


	//�ɸ� �ֵ� �߿� ���� ����� �ָ� ���´� & ���� �� ���� ���� �ϸ鼭,
	for (int i = 0; i < AllResult.Num(); ++i)
	{
		float fDist = AllResult[i].Distance;

		if (_pTarget && AllResult[i].GetActor() == _pTarget)
		{
			iMostCloseObjectIdx = i;
			break;
		}

		else if (!_pTarget && fDist < fMostCloseDist)
		{
			iMostCloseObjectIdx = i;
		}
	}

	if (iMostCloseObjectIdx < 0)
		return false;
	
	////���� ����� ���� �����̼��̴�.
	FVector MostCloseEnemyLocation = AllResult[iMostCloseObjectIdx].GetActor()->GetActorLocation();

	////�����Լ� ���� ���� ������͸� �����.
	FVector VecDir = MostCloseEnemyLocation - MyLocation;

	////���� �ϱ� ���� �븻������ �Ѵ�.
	VecDir.Normalize();

	VecDir.Z = 0;
	_rResultRot = FRotationMatrix::MakeFromX(VecDir).Rotator();
	
	//Ÿ���� �����Ѵ�.
	_pTarget = Cast<ANP4CharacterBase>(AllResult[iMostCloseObjectIdx].GetActor());
	return true;
}
