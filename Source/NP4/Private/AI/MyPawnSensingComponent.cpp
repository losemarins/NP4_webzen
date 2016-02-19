// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "MyPawnSensingComponent.h"




FVector UMyPawnSensingComponent::GetSensorLocation() const
{
	FVector SensorLocation(FVector::ZeroVector);
	const AActor* SensorActor = GetSensorActor();

	if (SensorActor != NULL)
	{
		FRotator ViewRotation;
		SensorActor->GetActorEyesViewPoint(SensorLocation, ViewRotation);
	}

	SensorLocation += FVector(0, 0, -40);
	return SensorLocation;
}