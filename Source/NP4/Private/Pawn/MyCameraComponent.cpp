// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "MyCameraComponent.h"

UMyCameraComponent::UMyCameraComponent(const FObjectInitializer& ObjectInitializer)
{
	CameraSpeed = 0.5;
	ZoomAlpha = 1.f;
	MinZoomLevel = 0.f;
	MaxZoomLevel = 1.f;
}

void UMyCameraComponent::SetZoomLevel(float NewLevel)
{
	ZoomAlpha = FMath::Clamp(NewLevel, MinZoomLevel, MaxZoomLevel);
}

APlayerController* UMyCameraComponent::GetPlayerController()
{
	APlayerController* Controller = NULL;
	APawn* Owner = GetOwnerPawn();
	if (Owner != NULL)
		Controller = Cast<APlayerController>(Owner->GetController());

	return Controller;
}

APawn* UMyCameraComponent::GetOwnerPawn()
{
	return Cast<APawn>(GetOwner());
}

void UMyCameraComponent::GetCameraView(float DeltaTime, FMinimalViewInfo& OutResult)
{
	APlayerController* Controller = GetPlayerController();
	if (Controller)
	{
		OutResult.FOV = 30.f;
		OutResult.Location = Controller->GetFocalLocation() - CameraAngle.Vector() * (ZoomAlpha * 3000);
		OutResult.Rotation = CameraAngle;
	}
}

void UMyCameraComponent::MoveForward(float Val)
{
	APawn* OwnerPawn = GetOwnerPawn();
	if (OwnerPawn != NULL)
	{
		APlayerController* Controller = GetPlayerController();
		if ((Val != 0.f) && (Controller != NULL))
		{
			const FRotationMatrix R(Controller->PlayerCameraManager->GetCameraRotation());
			const FVector WorldSpaceAccel = R.GetScaledAxis(EAxis::X) * 100.0f;

			// transform to world space and add it
			OwnerPawn->AddMovementInput(WorldSpaceAccel, Val);
		}
	}
}

void UMyCameraComponent::MoveRight(float Val)
{
	APawn* OwnerPawn = GetOwnerPawn();
	if (OwnerPawn != NULL)
	{
		APlayerController* Controller = GetPlayerController();
		if ((Val != 0.f) && (Controller != NULL))
		{
			const FRotationMatrix R(Controller->PlayerCameraManager->GetCameraRotation());
			const FVector WorldSpaceAccel = R.GetScaledAxis(EAxis::Y) * 100.0f;

			// transform to world space and add it
			OwnerPawn->AddMovementInput(WorldSpaceAccel, Val);
		}
	}
}

void UMyCameraComponent::OnZoomIn()
{
	SetZoomLevel(ZoomAlpha - 0.1f);
}

void UMyCameraComponent::OnZoomOut()
{
	SetZoomLevel(ZoomAlpha + 0.1f);
}
