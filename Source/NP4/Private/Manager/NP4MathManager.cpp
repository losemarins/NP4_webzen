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

	//영역 검사를 한다.
	AllResult.Empty();

	EndPosition = MyLocation + (vRightVec * (_vBoxExtent.Y)) + (vForwardVec * (_vBoxExtent.X + _fDist));
	StartPosition = MyLocation - (vRightVec * (_vBoxExtent.Y)) + (vForwardVec * (_vBoxExtent.X + _fDist));

	pWorld->SweepMultiByObjectType(AllResult, StartPosition, EndPosition, FQut,
		FCollisionObjectQueryParams::AllObjects,
		FCollisionShape::MakeBox(_vBoxExtent), Param);

	//제외 할 것은 제외 한다.
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

	//영역에 아무 것도 없다는 뜻이다.
	if (AllResult.Num() <= 0)
	{
		_pTarget = NULL;
		return false;
	}

	int iMostCloseObjectIdx = -1;
	float fMostCloseDist = 9999.f;


	//걸린 애들 중에 가장 가까운 애를 얻어온다 & 제외 할 것은 제외 하면서,
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
	
	////가장 가까운 애의 로케이션이다.
	FVector MostCloseEnemyLocation = AllResult[iMostCloseObjectIdx].GetActor()->GetActorLocation();

	////적에게서 나를 빼서 방향백터를 만든다.
	FVector VecDir = MostCloseEnemyLocation - MyLocation;

	////내적 하기 전에 노말라이즈 한다.
	VecDir.Normalize();

	VecDir.Z = 0;
	_rResultRot = FRotationMatrix::MakeFromX(VecDir).Rotator();
	
	//타겟을 갱신한다.
	_pTarget = Cast<ANP4CharacterBase>(AllResult[iMostCloseObjectIdx].GetActor());
	return true;
}
