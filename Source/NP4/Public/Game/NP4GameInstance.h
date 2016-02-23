// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "NP4GameInstance.generated.h"

/**
 *  Data 저장용
    멤버 변수를 통해 우리가 레벨 전환시 필요한 데이터를 저장한다.
	사용법은 
	UNP4GameInstance* SGI = Cast<UNP4GameInstance>(GetGameInstance());
	if(SGI)
	{
	SGI->맴버 변수, 함수 로 접근하도록 
	}
	by 정훈
 */
UCLASS()
class NP4_API UNP4GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
	 
	
	
};
