// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/CameraComponent.h"
#include "MyCameraComponent.generated.h"

/**
 * 
 */
UCLASS()
class NP4_API UMyCameraComponent : public UCameraComponent
{
	GENERATED_BODY()
	
public :
	float CameraSpeed;
	FRotator CameraAngle;
	float MinZoomLevel;
	float MaxZoomLevel;
	float ZoomAlpha;

public :
	virtual void GetCameraView(float DeltaTime, FMinimalViewInfo& DesiredView) override;

	UMyCameraComponent(const FObjectInitializer& ObjectInitializer);
	void MoveForward(float Val);
	void MoveRight(float Val);
	void OnZoomIn();
	void OnZoomOut();
	void SetZoomLevel(float NewLevel);
	APlayerController* GetPlayerController();
	APawn* GetOwnerPawn();
};
