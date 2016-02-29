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

	/* x�� �ڽ��� ���� ��, y�� ���� �� */
	/*   -------- 
	    ����   ����
	    -------- ��
	Z  ����    ����
	   ����--- ����
	    --------��  Y
	       X	
	*/

	/* �Լ� ���� */
	/* �ʿ��Ѱ� : MyLocation, FowardVector, RightVector, Extent, TeamNum, ����(f) = ���۷���*/

	/* Chapter 1. */
	/* 1. Target�� NULL�̸� �ٷ� Chapter2�� ����. */
	/* 2. Taget�� ���� ��� Target���� ������ ���(ForwardVector�� Ÿ���� �ٶ󺸴� ���Ϳ��� ����) */
	/* 3. �� ������ �־��� _fTargetAngle���� Ŭ ��� Chapter2�� ����. */
	/* 4. �� ������ �־��� _fTargetAngle���� �� ������ _rResultRot�� �־� �����ϰ� return true�� �ݳ��Ѵ�. */

	/* Chapter 2. */
	/* ���� ���鿡 ���� ���� ���  */
	/* 1. (RightVector * (_vBoxExtent.x / 2) ) + (ForwardVector * (_vBoxExtent.z / 2)  = EndPosition */
	/* 2. (-RightVector * (_vBoxExtent.x / 2) ) + (ForwardVector * (_vBoxExtent.z / 2)  = StartPosition */
	/* 3. �� ���� ������ �ڽ��� ����. Extent�� ��� �ؤ������������� => �ش� Start, Endposition */
	/* 4. �̷��� �ڽ��� �Ͽ� Sweep �Լ��� �ɸ� �ֵ� �߿� ���� �߸� */
	/* 5. �� �߿� ���� ����� �༮�� ��ġ�� ���� */
	/* 6. ���� ��ġ���� �� ��ġ�� ����. = Dir���� */
	/* 7. Foward ���Ϳ� Dir���� ���� ������ �Ͽ� ��Ÿ ���� ���ϰ� �� ���� ����(f)�� ��ȯ�Ѵ�. */
	/* 8. ����(f)�� ���۷��� FRoator�� �ִ´�. */
	/* 9. Ÿ���� �׳����� �����Ѵ�. */

	bool TraceNearEnemyObject_ByBox(ANP4CharacterBase* _pMyObject, ANP4CharacterBase*& _pTarget, float _fDist, FVector _vBoxExtent, FRotator& _rResultRot);
};
