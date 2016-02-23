// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "TownBuilding.h"




void ATownBuilding::Init()
{
	MeshComp->SetSimulatePhysics(true);
	MeshComp->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	//MeshC->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel1, ECollisionResponse::ECR_Ignore);
}

void ATownBuilding::WindowOpen()
{
	
}
