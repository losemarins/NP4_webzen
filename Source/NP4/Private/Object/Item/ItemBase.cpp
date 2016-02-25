// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "ItemBase.h"


// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemBase::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

int32 AItemBase::GetDataBaseKey()
{
	return m_iDBKey;
}

FName AItemBase::GetItemName()
{
	return m_sItemName;
}

eItemID AItemBase::GetItemID()
{
	return m_eItemID;
}