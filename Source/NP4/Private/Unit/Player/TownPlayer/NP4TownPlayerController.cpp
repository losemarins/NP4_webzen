// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"
#include "NP4TownPlayerController.h"
#include "NP4TownPlayer.h"
#include "NP4Input.h"

ANP4TownPlayerController::ANP4TownPlayerController()
	: bIgnoreInput(false)
{
	PlayerCameraManagerClass = ANP4CameraManager::StaticClass();
	PrimaryActorTick.bCanEverTick = true;
	bHidden = false;
	bShowMouseCursor = true;
	m_fMinZoomLevel = 0.4f;
	m_fMaxZoomLevel = 1.0f;
	m_ZoomDistance = 2000;
	m_bIsSwipe = false;
	m_bBuildMode = false;
}

void ANP4TownPlayerController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);
	m_pPossessPawn = Cast<ANP4TownPlayer>(InPawn);
}

void ANP4TownPlayerController::Tick(float DeltaSeconds)
{
	UpdateCamera(DeltaSeconds);	

	if (!m_bBuildMode && m_bIsSwipe)
	{
		OnSwipeUpdate();
	}

	if (m_bBuildMode)
	{
		ANP4TownGameState const* const MyGameState = GetWorld()->GetGameState<ANP4TownGameState>();
	}
}


void ANP4TownPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//InputHandler = NewObject<UNP4Input>(this);
	//BIND_1P_ACTION(InputHandler, EGameKey::Tap, IE_Pressed, &ANP4TownPlayerController::OnTapPressed);
	//BIND_1P_ACTION(InputHandler, EGameKey::Hold, IE_Pressed, &ANP4TownPlayerController::OnHoldPressed);
	//BIND_1P_ACTION(InputHandler, EGameKey::Hold, IE_Released, &ANP4TownPlayerController::OnHoldReleased);
	/*BIND_1P_ACTION(InputHandler, EGameKey::Swipe, IE_Pressed, &ANP4TownPlayerController::OnSwipeStarted);
	BIND_1P_ACTION(InputHandler, EGameKey::Swipe, IE_Repeat, &ANP4TownPlayerController::OnSwipeUpdate);
	BIND_1P_ACTION(InputHandler, EGameKey::Swipe, IE_Released, &ANP4TownPlayerController::OnSwipeReleased);*/
	//BIND_2P_ACTION(InputHandler, EGameKey::SwipeTwoPoints, IE_Pressed, &ANP4TownPlayerController::OnSwipeTwoPointsStarted);
	//BIND_2P_ACTION(InputHandler, EGameKey::SwipeTwoPoints, IE_Repeat, &ANP4TownPlayerController::OnSwipeTwoPointsUpdate);
	//BIND_2P_ACTION(InputHandler, EGameKey::Pinch, IE_Pressed, &ANP4TownPlayerController::OnPinchStarted);
	//BIND_2P_ACTION(InputHandler, EGameKey::Pinch, IE_Repeat, &ANP4TownPlayerController::OnPinchUpdate);
	
	//InputComponent->BindAction("MouseLClick", IE_Pressed, this, &ANP4TownPlayerController::OnSwipeStarted);
	//InputComponent->BindAction("MouseLClick", IE_Repeat, this, &ANP4TownPlayerController::OnSwipeUpdate);
	//InputComponent->BindAction("MouseLClick", IE_Released, this, &ANP4TownPlayerController::OnSwipeReleased);
	InputComponent->BindAction("MouseLClick", IE_Pressed, this, &ANP4TownPlayerController::OnSwipeStarted);
	InputComponent->BindAction("MouseLClick", IE_Released, this, &ANP4TownPlayerController::OnSwipeReleased);

	InputComponent->BindAction("ZoomOut", IE_Pressed, this, &ANP4TownPlayerController::OnZoomOut);
	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &ANP4TownPlayerController::OnZoomIn);

	//FInputActionBinding& ToggleInGameMenuBinding = InputComponent->BindAction("InGameMenu", IE_Pressed, this, &ANP4TownPlayerController::OnToggleInGameMenu);
	//ToggleInGameMenuBinding.bExecuteWhenPaused = true;
}

void ANP4TownPlayerController::OnZoomOut()
{
	m_bZoomingIn = false;
	if(m_ZoomDistance < 3000)
		m_ZoomDistance += 150;
}

void ANP4TownPlayerController::UpdateCamera(float DeltaTime)
{
	Cast<ANP4TownPlayer>(m_pPossessPawn)->GetCamera()->FieldOfView = FMath::Lerp<float>(90.0f, 60.0f, m_ZoomFactor);
	Cast<ANP4TownPlayer>(m_pPossessPawn)->GetSpringArm()->TargetArmLength = FMath::Lerp<float>(m_ZoomDistance, m_ZoomDistance, 1);
}

AActor* ANP4TownPlayerController::GetSelectActor(FVector2D MousePos)
{

}

FVector2D ANP4TownPlayerController::GetMousePose()
{

}

void ANP4TownPlayerController::OnZoomIn()
{
	m_bZoomingIn = true;
	if (m_ZoomDistance > 300)
		m_ZoomDistance -= 150;
}

void ANP4TownPlayerController::OnToggleInGameMenu()
{
	/*AStrategyHUD* const MyHUD = Cast<AStrategyHUD>(GetHUD());
	if (MyHUD)
	{
		MyHUD->TogglePauseMenu();
	}*/
}

void ANP4TownPlayerController::UpdateRotation(float DeltaTime)
{
	FRotator ViewRotation(0, 0, 0);
	FRotator DeltaRot(0, 0, 0);

	// 매틱마다 들어오면서 카메라 제한
	//if (PlayerCameraManager)
	{
		//PlayerCameraManager->ProcessViewRotation(DeltaTime, ViewRotation, DeltaRot);
	}

	SetControlRotation(ViewRotation);
}

void ANP4TownPlayerController::ProcessPlayerInput(const float DeltaTime, const bool bGamePaused)
{
	//if (!bGamePaused && PlayerInput && InputHandler && !bIgnoreInput)
	//{
	//	//InputHandler->UpdateDetection(DeltaTime);
	//}

	Super::ProcessPlayerInput(DeltaTime, bGamePaused);

	//if (!bIgnoreInput)
	{
		//const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player);
		//AStrategySpectatorPawn* StrategyPawn = GetStrategySpectatorPawn();
		//if ((StrategyPawn != NULL) && (LocalPlayer != NULL))
		//{
		//	// Create the bounds for the minimap so we can add it as a 'no scroll' zone.
		//	AStrategyHUD* const HUD = Cast<AStrategyHUD>(GetHUD());
		//	AStrategyGameState const* const MyGameState = GetWorld()->GetGameState<AStrategyGameState>();
		//	if ((MyGameState != NULL) && (MyGameState->MiniMapCamera.IsValid() == true))
		//	{
		//		if (LocalPlayer->ViewportClient != NULL)
		//		{
		//			const FIntPoint ViewportSize = LocalPlayer->ViewportClient->Viewport->GetSizeXY();
		//			const uint32 ViewTop = FMath::TruncToInt(LocalPlayer->Origin.Y * ViewportSize.Y);
		//			const uint32 ViewBottom = ViewTop + FMath::TruncToInt(LocalPlayer->Size.Y * ViewportSize.Y);

		//			FVector TopLeft(HUD->MiniMapMargin, ViewBottom - HUD->MiniMapMargin - MyGameState->MiniMapCamera->MiniMapHeight, 0);
		//			FVector BottomRight((int32)MyGameState->MiniMapCamera->MiniMapWidth, MyGameState->MiniMapCamera->MiniMapHeight, 0);
		//			FBox MiniMapBounds(TopLeft, TopLeft + BottomRight);
		//			StrategyPawn->GetStrategyCameraComponent()->AddNoScrollZone(MiniMapBounds);
		//			StrategyPawn->GetStrategyCameraComponent()->UpdateCameraMovement(this);
		//		}
		//	}
		//}
	}
}

void ANP4TownPlayerController::SetCameraTarget(const FVector& CameraTarget)
{
	//없어도됨
	/*if (GetCameraComponent() != NULL)
	{
		GetCameraComponent()->SetCameraTarget(CameraTarget);
	}*/
}

void ANP4TownPlayerController::SetIgnoreInput(bool bIgnore)
{
	bIgnoreInput = bIgnore;
}


//void ANP4TownPlayerController::MouseLeftMinimap()
//{
//	/*if (GetCameraComponent() != NULL)
//	{
//		GetCameraComponent()->EndSwipeNow();
//	}*/
//}
//void ANP4TownPlayerController::MousePressedOverMinimap()
//{
//	//if (GetCameraComponent() != NULL)
//	{
//		//GetCameraComponent()->EndSwipeNow();
//	}
//}



void ANP4TownPlayerController::OnTapPressed(const FVector2D& ScreenPosition, float DownTime)
{
	/*FVector WorldPosition(0.f);
	AActor* const HitActor = GetFriendlyTarget(ScreenPosition, WorldPosition);

	SetSelectedActor(HitActor, WorldPosition);

	if (HitActor && HitActor->GetClass()->ImplementsInterface(UStrategyInputInterface::StaticClass()))
	{
		IStrategyInputInterface::Execute_OnInputTap(HitActor);
	}*/
	FVector WorldPosition(0.f);
	
}

void ANP4TownPlayerController::OnHoldPressed(const FVector2D& ScreenPosition, float DownTime)
{
	/*FVector WorldPosition(0.0f);
	AActor* const HitActor = GetFriendlyTarget(ScreenPosition, WorldPosition);

	SetSelectedActor(HitActor, WorldPosition);

	if (HitActor && HitActor->GetClass()->ImplementsInterface(UStrategyInputInterface::StaticClass()))
	{
		IStrategyInputInterface::Execute_OnInputHold(HitActor);
	}*/
}

void ANP4TownPlayerController::OnHoldReleased(const FVector2D& ScreenPosition, float DownTime)
{
	/*AActor* const Selected = SelectedActor.Get();
	if (Selected && Selected->GetClass()->ImplementsInterface(UStrategyInputInterface::StaticClass()))
	{
		IStrategyInputInterface::Execute_OnInputHoldReleased(Selected, DownTime);
	}*/
}

void ANP4TownPlayerController::OnSwipeStarted(/*const FVector2D& AnchorPosition, float DownTime*/)
{
	m_bIsSwipe = true;
	const ULocalPlayer* LP = Cast<ULocalPlayer>(Player);
	FVector2D MousePos = LP->ViewportClient->GetMousePosition();
	FVector WorldOrigin, WorldDirection, TraceEnd; // 마우스 커서의 월드 위치, 가리키는 방향, 트레이스 끝지점
	FVector MouseWorldPosition_3D;
	FHitResult TraceHitResult;
	FCollisionObjectQueryParams TraceObjectParam; // 충돌이 어떤 유형의 오브젝트에 유효할것인지
	FCollisionQueryParams TraceParam;
	TraceObjectParam.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);
	TraceObjectParam.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldDynamic);
	TraceObjectParam.AddObjectTypesToQuery(ECollisionChannel::ECC_Pawn);

	TraceParam.bTraceComplex = true;
	TraceParam.bTraceAsyncScene = true;
	TraceParam.bReturnPhysicalMaterial = false;
	DeprojectScreenPositionToWorld(MousePos.X, MousePos.Y, WorldOrigin, WorldDirection);

	TraceEnd = WorldOrigin + WorldDirection * 65536.0f;

	GetWorld()->LineTraceSingle(TraceHitResult, WorldOrigin, TraceEnd, TraceParam, TraceObjectParam);
	
	if (TraceHitResult.bBlockingHit)
		m_vStartSwipeCoords = TraceHitResult.ImpactPoint;
	else
		m_vStartSwipeCoords = WorldOrigin;
	//m_vPrevSwipeScreenPosition = MousePos;
	
	//if (GetCameraComponent())
	//{
	//	bool bResult = false;
	//	if (AreCoordsInNoScrollZone(AnchorPosition) == false)
	//	{
	//		
	//		// Get intersection point with the plan used to move around
	//		FHitResult Hit;
	//		if (GetHitResultAtScreenPosition(AnchorPosition, COLLISION_PANCAMERA, true, Hit))
	//		{
	//			m_vStartSwipeCoords = Hit.ImpactPoint;
	//			bResult = true;
	//		}
	//	}
	//	else
	//	{
	//		EndSwipeNow();
	//	}
	//}

	//FVector WorldPosition(0.0f);
	//AActor* const HitActor = GetFriendlyTarget(AnchorPosition, WorldPosition);
	//SetSelectedActor(HitActor, WorldPosition);

	/////** Get our position in 3d space */
	///*if (SelectedActor.IsValid())
	//{
	//	SwipeAnchor3D = SelectedActor->GetActorLocation();
	//}*/

	//m_vPrevSwipeScreenPosition = AnchorPosition;
}

void ANP4TownPlayerController::OnSwipeUpdate(/*const FVector2D& ScreenPosition, float DownTime*/)
{
	//AActor* const Selected = m_SelectedActor.Get();
	//if (Selected && Selected->GetClass()->ImplementsInterface(UStrategyInputInterface::StaticClass()))
	//{
	//	ULocalPlayer* const MyPlayer = Cast<ULocalPlayer>(Player);
	//	const FPlane GroundPlane = FPlane(FVector(0, 0, SelectedActor->GetActorLocation().Z), FVector(0, 0, 1));

	//	FVector RayOrigin, RayDirection;
	//	FStrategyHelpers::DeprojectScreenToWorld(ScreenPosition, MyPlayer, RayOrigin, RayDirection);
	//	const FVector ScreenPosition3D = FStrategyHelpers::IntersectRayWithPlane(RayOrigin, RayDirection, GroundPlane);

	//	IStrategyInputInterface::Execute_OnInputSwipeUpdate(Selected, ScreenPosition3D - SwipeAnchor3D);
	//}
	//else
	//if (GetCameraComponent() != NULL)
	//{
	//	if (m_vStartSwipeCoords.IsNearlyZero() == false)
	//	{
	//		FHitResult Hit;
	//		if (GetHitResultAtScreenPosition(ScreenPosition, COLLISION_PANCAMERA, true, Hit))
	//		{

	const ULocalPlayer* LP = Cast<ULocalPlayer>(Player);
	FVector2D MousePos = LP->ViewportClient->GetMousePosition();
	FVector WorldOrigin, WorldDirection, TraceEnd; // 마우스 커서의 월드 위치, 가리키는 방향, 트레이스 끝지점
	FVector MouseWorldPosition_3D;
	FHitResult TraceHitResult;
	FCollisionObjectQueryParams TraceObjectParam; // 충돌이 어떤 유형의 오브젝트에 유효할것인지
	FCollisionQueryParams TraceParam;
	TraceObjectParam.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);
	TraceObjectParam.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldDynamic);
	TraceObjectParam.AddObjectTypesToQuery(ECollisionChannel::ECC_Pawn);

	TraceParam.bTraceComplex = true;
	TraceParam.bTraceAsyncScene = true;
	TraceParam.bReturnPhysicalMaterial = false;
	DeprojectScreenPositionToWorld(MousePos.X, MousePos.Y, WorldOrigin, WorldDirection);

	TraceEnd = WorldOrigin + WorldDirection * 65536.0f;

	GetWorld()->LineTraceSingle(TraceHitResult, WorldOrigin, TraceEnd, TraceParam, TraceObjectParam);
	MouseWorldPosition_3D = TraceHitResult.ImpactPoint;

	//m_vStartSwipeCoords = MouseWorldPosition_3D;
	//m_vPrevSwipeScreenPosition = MousePos;

				FVector NewSwipeCoords = TraceHitResult.ImpactPoint;
				FVector Delta = m_vStartSwipeCoords - NewSwipeCoords;
	//			// Flatten Z axis - we are not interested in that.
				Delta.Z = 0.0f;

				if (Delta.IsNearlyZero() == false)
				{
					{
						FVector vLocation = m_pPossessPawn->GetActorLocation();
						vLocation += Delta;
						m_pPossessPawn->SetActorRelativeLocation(vLocation);
					}
				}
	//		}
	//	}
	//}

	//m_vPrevSwipeScreenPosition = ScreenPosition;
}

void ANP4TownPlayerController::OnSwipeReleased(/*const FVector2D& ScreenPosition, float DownTime*/)
{
	m_bIsSwipe = false;
	/*AActor* const Selected = m_SelectedActor.Get();
	if (Selected && Selected->GetClass()->ImplementsInterface(UStrategyInputInterface::StaticClass()))
	{
		ULocalPlayer* const MyPlayer = Cast<ULocalPlayer>(this->Player);
		const FPlane GroundPlane = FPlane(FVector(0, 0, SelectedActor->GetActorLocation().Z), FVector(0, 0, 1));

		FVector RayOrigin, RayDirection;
		FStrategyHelpers::DeprojectScreenToWorld(ScreenPosition, MyPlayer, RayOrigin, RayDirection);
		const FVector ScreenPosition3D = FStrategyHelpers::IntersectRayWithPlane(RayOrigin, RayDirection, GroundPlane);

		IStrategyInputInterface::Execute_OnInputSwipeReleased(Selected, ScreenPosition3D - SwipeAnchor3D, DownTime);
	}
	else*/
	/*{
		if (GetCameraComponent() != NULL)
		{
			if (m_vStartSwipeCoords.IsNearlyZero() == false)
			{
				FHitResult Hit;
				if (GetHitResultAtScreenPosition(ScreenPosition, COLLISION_PANCAMERA, true, Hit))
				{
					FVector EndSwipeCoords = Hit.ImpactPoint;
				}
				EndSwipeNow();
			}
		}
	}*/
	int a = 0;
}

void ANP4TownPlayerController::OnSwipeTwoPointsStarted(const FVector2D& ScreenPosition1, const FVector2D& ScreenPosition2, float DownTime)
{
	m_vPrevSwipeMidPoint = (ScreenPosition1 + ScreenPosition2) * 0.5f;
}

void ANP4TownPlayerController::OnSwipeTwoPointsUpdate(const FVector2D& ScreenPosition1, const FVector2D& ScreenPosition2, float DownTime)
{
	/*const FVector2D SwipeMidPoint = (ScreenPosition1 + ScreenPosition2) * 0.5f;
	const FVector MoveDir = FVector(SwipeMidPoint - PrevSwipeMidPoint, 0.0f).GetSafeNormal();
	const float SwipeSpeed = 10000.0f;

	const FRotationMatrix R(PlayerCameraManager->GetCameraRotation() + FRotator(0.0, 90.0, 0.0));
	const FVector WorldSpaceAccel = R.TransformVector(MoveDir) * SwipeSpeed;
	if (GetSpectatorPawn())
	{
		GetSpectatorPawn()->AddMovementInput(WorldSpaceAccel, 1.f);
	}

	PrevSwipeMidPoint = SwipeMidPoint;*/
}

void ANP4TownPlayerController::OnPinchStarted(const FVector2D& AnchorPosition1, const FVector2D& AnchorPosition2, float DownTime)
{
	// Pass the pinch through to the camera component.
	/*if (GetCameraComponent() != NULL)
	{
		GetCameraComponent()->OnPinchStarted(AnchorPosition1, AnchorPosition2, DownTime);
	}*/
}

void ANP4TownPlayerController::OnPinchUpdate(const FVector2D& ScreenPosition1, const FVector2D& ScreenPosition2, float DownTime)
{
	// Pass the pinch through to the camera component.
	/*if (GetCameraComponent() != NULL)
	{
		GetCameraComponent()->OnPinchUpdate(InputHandler, ScreenPosition1, ScreenPosition2, DownTime);
	}*/
}
UCameraComponent* ANP4TownPlayerController::GetCameraComponent() const
{
	UCameraComponent* CameraComponent = NULL;
	if (m_pPossessPawn)
		CameraComponent = Cast<ANP4TownPlayer>(m_pPossessPawn)->GetCamera();

	return CameraComponent;
}

bool ANP4TownPlayerController::AreCoordsInNoScrollZone(const FVector2D& SwipePosition)
{
	bool bResult = false;
	FVector MouseCoords(SwipePosition, 0.0f);
	for (int iZone = 0; iZone < m_NoScrollZones.Num(); iZone++)
	{
		FBox EachZone = m_NoScrollZones[iZone];
		if (EachZone.IsInsideXY(MouseCoords) == true)
		{
			bResult = true;
		}
	}
	return bResult;
}

void ANP4TownPlayerController::EndSwipeNow()
{
	m_vStartSwipeCoords.Set(0.0f, 0.0f, 0.0f);
}

AActor* ANP4TownPlayerController::GetFriendlyTarget(const FVector2D& ScreenPoint, FVector& WorldPoint) const
{
//	FHitResult Hit;
//	if (GetHitResultAtScreenPosition(ScreenPoint, COLLISION_BUILDING, true, Hit))
//	{
//		//if (!ANP4TownPlayerController::OnEnemyTeam(Hit.GetActor(), this))
//		{
//			WorldPoint = Hit.ImpactPoint;
//			return Hit.GetActor();
//		}
//	}
//
	return NULL;
}

void ANP4TownPlayerController::SetSelectedActor(AActor* NewSelectedActor, const FVector& NewPosition)
{
	if (m_SelectedActor != NewSelectedActor)
	{
		// attempt to unselect current selection
		AActor* const OldSelection = m_SelectedActor.Get();
		if (OldSelection /*&& OldSelection->GetClass()->ImplementsInterface(UStrategySelectionInterface::StaticClass())*/)
		{
			/*if (IStrategySelectionInterface::Execute_OnSelectionLost(OldSelection, NewPosition, NewSelectedActor))
			{
				SelectedActor = NULL;
			}*/
		}

		if (!m_SelectedActor.IsValid())
		{
			// attempt to select new selection
			//if (NewSelectedActor && NewSelectedActor->GetClass()->ImplementsInterface(UStrategySelectionInterface::StaticClass()))
			{
			//	if (IStrategySelectionInterface::Execute_OnSelectionGained(NewSelectedActor))
				{
					m_SelectedActor = NewSelectedActor;
				}
			}
		}
	}
}