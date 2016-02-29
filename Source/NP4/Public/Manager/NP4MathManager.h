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

	/* x亜 酵什税 室稽 葵, y亜 亜稽 葵 */
	/*   -------- 
	    ��Β   ��Β
	    -------- Β
	Z  ΒΒ    ΒΒ
	   Β��--- ΒΒ
	    --------��  Y
	       X	
	*/

	/* 敗呪 竺誤 */
	/* 琶推廃葵 : MyLocation, FowardVector, RightVector, Extent, TeamNum, 唖亀(f) = 掘遁訓什*/

	/* Chapter 1. */
	/* 1. Target戚 NULL戚檎 郊稽 Chapter2稽 娃陥. */
	/* 2. Taget戚 赤聖 井酔 Target引税 唖亀研 千陥(ForwardVector人 展為聖 郊虞左澗 拷斗人税 鎧旋) */
	/* 3. 益 唖亀亜 爽嬢遭 _fTargetAngle左陥 適 井酔 Chapter2稽 娃陥. */
	/* 4. 益 唖亀亜 爽嬢遭 _fTargetAngle左陥 益 唖亀研 _rResultRot拭 隔嬢 飴重馬壱 return true研 鋼崖廃陥. */

	/* Chapter 2. */
	/* 幻鉦 舛檎拭 旋戚 蒸聖 井酔  */
	/* 1. (RightVector * (_vBoxExtent.x / 2) ) + (ForwardVector * (_vBoxExtent.z / 2)  = EndPosition */
	/* 2. (-RightVector * (_vBoxExtent.x / 2) ) + (ForwardVector * (_vBoxExtent.z / 2)  = StartPosition */
	/* 3. 砧 繊聖 戚生澗 酵什研 幻給. Extent研 紫遂 『けけけけけけ『 => 『澗 Start, Endposition */
	/* 4. 戚係惟 酵什研 馬食 Sweep 敗呪拭 杏鍵 蕉級 掻拭 旋幻 蓄顕 */
	/* 5. 旋 掻拭 亜舌 亜猿錘 橿汐税 是帖研 条嬢身 */
	/* 6. 旋税 是帖拭辞 鎧 是帖研 捌陥. = Dir拷斗 */
	/* 7. Foward 拷斗人 Dir拷斗 娃税 鎧旋聖 馬食 季展 葵聖 姥馬壱 戚 依聖 唖亀(f)稽 痕発廃陥. */
	/* 8. 唖亀(f)研 掘遁訓什 FRoator拭 隔澗陥. */
	/* 9. 展為聖 益角生稽 飴重廃陥. */

	bool TraceNearEnemyObject_ByBox(ANP4CharacterBase* _pMyObject, ANP4CharacterBase*& _pTarget, float _fDist, FVector _vBoxExtent, FRotator& _rResultRot);
};
