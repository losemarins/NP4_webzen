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
	m_bIsBuildpossibility = false;
	m_OldSelectActor = NULL;
	m_fCameraScrollSpeed = 2500.f;
	m_EBuildType = EBuilding::Defualt;
}

void ANP4TownPlayerController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);
	m_pPossessPawn = Cast<ANP4TownPlayer>(InPawn);
	m_pPossessPawn->SetActorEnableCollision(false);
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
		TileDetecting();
		MouseScrolling(DeltaSeconds);
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
	if (m_ZoomDistance < 3000)
		m_ZoomDistance += 150;
}

void ANP4TownPlayerController::UpdateCamera(float DeltaTime)
{
	Cast<ANP4TownPlayer>(m_pPossessPawn)->GetCamera()->FieldOfView = FMath::Lerp<float>(90.0f, 60.0f, m_ZoomFactor);
	Cast<ANP4TownPlayer>(m_pPossessPawn)->GetSpringArm()->TargetArmLength = FMath::Lerp<float>(m_ZoomDistance, m_ZoomDistance, 1);
}

void ANP4TownPlayerController::MouseScrolling(float DeltaTime)
{
	FVector2D MousePos = GetMousePos();
	ULocalPlayer* const LocalPlayer = Cast<ULocalPlayer>(Player);

	if (LocalPlayer && LocalPlayer->ViewportClient && LocalPlayer->ViewportClient->Viewport)
	{
		FViewport* Viewport = LocalPlayer->ViewportClient->Viewport;
		const float ScrollSpeed = 60.0f;
		const FIntPoint ViewportSize = Viewport->GetSizeXY();
		const uint32 ViewLeft = FMath::TruncToInt(LocalPlayer->Origin.X * ViewportSize.X);
		const uint32 ViewRight = ViewLeft + FMath::TruncToInt(LocalPlayer->Size.X * ViewportSize.X);
		const uint32 ViewTop = FMath::TruncToInt(LocalPlayer->Origin.Y * ViewportSize.Y);
		const uint32 ViewBottom = ViewTop + FMath::TruncToInt(LocalPlayer->Size.Y * ViewportSize.Y);



		const uint32 MouseX = MousePos.X;
		const uint32 MouseY = MousePos.Y;
		float CameraActiveBorder = 80.f;
		FVector vLocation = m_pPossessPawn->GetActorLocation();

		if (MouseX >= ViewLeft && MouseX <= (ViewLeft + CameraActiveBorder))
		{
			vLocation.Y -= m_fCameraScrollSpeed * DeltaTime;
			Viewport->SetMouse(CameraActiveBorder, MouseY);

		}
		if (MouseX >= (ViewRight - CameraActiveBorder) && MouseX <= ViewRight)
		{
			vLocation.Y += m_fCameraScrollSpeed * DeltaTime;
			Viewport->SetMouse(ViewRight - CameraActiveBorder, MouseY);
		}

		if (MouseY >= ViewTop && MouseY <= (ViewTop + CameraActiveBorder))
		{
			vLocation.X += m_fCameraScrollSpeed * DeltaTime;
			Viewport->SetMouse(MouseX, ViewTop + CameraActiveBorder);
		}
		if (MouseY >= (ViewBottom - CameraActiveBorder) && MouseY <= ViewBottom)
		{
			vLocation.X -= m_fCameraScrollSpeed * DeltaTime;
			Viewport->SetMouse(MouseX, ViewBottom - CameraActiveBorder);
		}

		if (vLocation.X > 3100 || vLocation.X < -5800 || vLocation.Y < -4600 || vLocation.Y > 4000)
			return;
		m_pPossessPawn->SetActorLocation(vLocation);

	}

}

FHitResult ANP4TownPlayerController::GetSelectActor(FVector2D MousePos)
{
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

	return TraceHitResult;
}

FVector2D ANP4TownPlayerController::GetMousePos()
{
	const ULocalPlayer* LP = Cast<ULocalPlayer>(Player);
	FVector2D MousePos = LP->ViewportClient->GetMousePosition();

	return MousePos;
}

void ANP4TownPlayerController::TileDetecting()
{
	FVector2D MousePos = GetMousePos();
	FHitResult HitResult = GetSelectActor(MousePos);

	ATile* pTile = Cast<ATile>(HitResult.GetActor());

	if (!pTile)
		return;

	if (!m_OldSelectActor)
		m_OldSelectActor = pTile;
	else
		Cast<ATile>(m_OldSelectActor)->SetMeshMetarial(EColor::Original);


	if (pTile->GetBuilding())
	{
		//타일에 이미 건물이 건설되어있으면 Red로 변경
		pTile->SetMeshMetarial(EColor::Red);
	}
	else
	{
		// 타일에 건물이 없으면 Green으로 변경.
		pTile->SetMeshMetarial(EColor::Green);
	}

	m_OldSelectActor = pTile;
}

void ANP4TownPlayerController::SetBuildMode(EBuilding::Type EBuildType)
{
	m_bBuildMode = true;
	m_EBuildType = EBuildType;
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
	// 마우스 클릭시 
	// 건설 모드인지 검사
	FVector2D MousePos = GetMousePos();
	FHitResult HitResult = GetSelectActor(MousePos);

	if (m_bBuildMode)
	{
		// 건설모드일 경우 마우스 위치에 있는 액터를 얻어온다.
		// 해당 액터가 타일일 경우 타일에 건물이 건설되어 있는지 판단.
		ATile* pTile = Cast<ATile>(HitResult.GetActor());

		//타일이 아니면 종료가 아닌. 다른 방식을 취해야한다. 건물일경우? 
		// 아니다 건물은 무조건 타일에 건설된다.
		// 그렇다면 해당 타일에 어떤 건물이 건설되었는지 정보를 주고.
		// 그 해당 타일의 위치에 있는 건물을 가져온다. 근데 어떻게?
		// 이렇게되면 타일이 건물을 가지고 있도록 만들어야되나?? 
		if (!pTile)
			return;

		if (pTile->GetBuilding())
		{
			//건물이 건설되어 있을경우 눌러도 아무 반응도 하면안됨.
			// 삐빅! 이런 싸운드를 출력하게한다.

		}
		else
		{
			// 건물이 건설되어있지 않을 경우 
			// 타일의 위치에 건물이 생성되야한다. 어떤 건물인지는 UI에서 받아와야하고.
			// State 를 얻어온 후 building해주는 로직을 만들어야함.
			FVector TilePos = pTile->GetActorLocation();
			ANP4TownGameState* MyGameState = GetWorld()->GetGameState<ANP4TownGameState>();
			MyGameState->CreateBuilding(TilePos, m_EBuildType);
		}
	}
	else
	{
		// 건설모드가 아닐경우 카메라 이동처리만 해주면된다.

		if (HitResult.bBlockingHit)
			m_vStartSwipeCoords = HitResult.ImpactPoint;
		/*else
		{
		FVector WorldLocation, WorldDirection;
		DeprojectScreenPositionToWorld(MousePos.X, MousePos.Y, WorldLocation, WorldDirection);
		WorldLocation.Z = m_pPossessPawn->GetActorLocation().Z;
		m_vStartSwipeCoords = WorldLocation;
		}*/
	}
	m_bIsSwipe = true;

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


	//m_vStartSwipeCoords = MouseWorldPosition_3D;
	//m_vPrevSwipeScreenPosition = MousePos;
	FVector2D MousePos = GetMousePos();
	FHitResult TraceHitResult = GetSelectActor(MousePos);


	FVector Delta;
	if (TraceHitResult.bBlockingHit)
	{
		FVector NewSwipeCoords = TraceHitResult.ImpactPoint;
		Delta = m_vStartSwipeCoords - NewSwipeCoords;
		Delta.Z = 0.0f;
	}
	//else
	//{
	//	FVector WorldLocation, WorldDirection;
	//	DeprojectScreenPositionToWorld(MousePos.X, MousePos.Y, WorldLocation, WorldDirection);
	//	WorldLocation.Z = m_pPossessPawn->GetActorLocation().Z;
	//	FVector NewSwipeCoords = WorldLocation;
	//	Delta = m_vStartSwipeCoords - NewSwipeCoords;
	//}


	if (Delta.IsNearlyZero() == false && TraceHitResult.bBlockingHit)
	{
		{
			FVector vLocation = m_pPossessPawn->GetActorLocation();
			vLocation += Delta;
			if (vLocation.X > 3100 || vLocation.X < -5800 || vLocation.Y < -4600 || vLocation.Y > 4000)
				return;
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
	if (m_bBuildMode)
	{
		m_bBuildMode = false;

		FVector2D MousePos = GetMousePos();
		FHitResult HitResult = GetSelectActor(MousePos);

		ATile* pTile = Cast<ATile>(HitResult.GetActor());
		if (!pTile)
			return;

		pTile->SetBuilding(true);
		pTile->SetMeshMetarial(EColor::Original);
	}

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