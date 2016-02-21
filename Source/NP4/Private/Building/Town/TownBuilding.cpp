// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "TownBuilding.h"




void ATownBuilding::Init()
{
	MeshComp->SetSimulatePhysics(true);
}

void ATownBuilding::WindowOpen()
{
	switch (m_EBuildingType)
	{
	case EBuilding::Barrack:
		break;
	case EBuilding::HeroManagement:
		break;
	case EBuilding::Laboratory:
		break;
	}
}
