// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "NP4CharacterBase.h"
#include "NP4MathManager.generated.h"

/**
 * 
 */
UCLASS()
class NP4_API UNP4MathManager : public UObject
{
	GENERATED_BODY()

public:
	UNP4MathManager();

	/* x가 박스의 세로 값, y가 가로 값 */
	/*   -------- 
	    ／│   ／│
	    -------- │
	Z  ││    ││
	   │／--- ││
	    --------／  Y
	       X	
	*/

	/* 함수 설명 */
	/* 필요한값 : MyLocation, FowardVector, RightVector, Extent, TeamNum, 각도(f) = 래퍼런스*/

	/* Chapter 1. */
	/* 1. Target이 NULL이면 바로 Chapter2로 간다. */
	/* 2. Taget이 있을 경우 Target과의 각도를 잰다(ForwardVector와 타겟을 바라보는 백터와의 내적) */
	/* 3. 그 각도가 주어진 _fTargetAngle보다 클 경우 Chapter2로 간다. */
	/* 4. 그 각도가 주어진 _fTargetAngle보다 그 각도를 _rResultRot에 넣어 갱신하고 return true를 반납한다. */

	/* Chapter 2. */
	/* 만약 정면에 적이 없을 경우  */
	/* 1. (RightVector * (_vBoxExtent.x / 2) ) + (ForwardVector * (_vBoxExtent.z / 2)  = EndPosition */
	/* 2. (-RightVector * (_vBoxExtent.x / 2) ) + (ForwardVector * (_vBoxExtent.z / 2)  = StartPosition */
	/* 3. 두 점을 이으는 박스를 만듬. Extent를 사용 ※ㅁㅁㅁㅁㅁㅁ※ => ※는 Start, Endposition */
	/* 4. 이렇게 박스를 하여 Sweep 함수에 걸린 애들 중에 적만 추림 */
	/* 5. 적 중에 가장 가까운 녀석의 위치를 얻어옴 */
	/* 6. 적의 위치에서 내 위치를 뺀다. = Dir백터 */
	/* 7. Foward 백터와 Dir백터 간의 내적을 하여 델타 값을 구하고 이 것을 각도(f)로 변환한다. */
	/* 8. 각도(f)를 래퍼런스 FRoator에 넣는다. */
	/* 9. 타겟을 그넘으로 갱신한다. */

	bool TraceNearEnemyObject_ByBox(ANP4CharacterBase* _pMyObject, ANP4CharacterBase*& _pTarget, float _fDist, FVector _vBoxExtent, FRotator& _rResultRot);
};
