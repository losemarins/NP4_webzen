// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Unit/Player/NP4PlayerController.h"
#include "NP4TownPlayerController.generated.h"

/**
*
*/
class UNP4Input;

UCLASS()
class NP4_API ANP4TownPlayerController : public ANP4PlayerController
{
	GENERATED_BODY()



protected:
	/** update input detection */
	virtual void ProcessPlayerInput(const float DeltaTime, const bool bGamePaused) override;
	virtual void SetupInputComponent() override;

public:
	virtual void Possess(APawn* InPawn) override;
	virtual void Tick(float DeltaSeconds) override;
	/** fixed rotation */
	virtual void UpdateRotation(float DeltaTime) override;
	ANP4TownPlayerController();
	/** set desired camera position. */
	void SetCameraTarget(const FVector& CameraTarget);

	/** helper function to toggle input detection. */
	void SetIgnoreInput(bool bIgnore);

	/** Input handlers. */
	void OnTapPressed(const FVector2D& ScreenPosition, float DownTime);
	void OnHoldPressed(const FVector2D& ScreenPosition, float DownTime);
	void OnHoldReleased(const FVector2D& ScreenPosition, float DownTime);
	void OnSwipeStarted();
	void OnSwipeUpdate();
	void OnSwipeReleased();
	void OnSwipeTwoPointsStarted(const FVector2D& ScreenPosition1, const FVector2D& ScreenPosition2, float DownTime);
	void OnSwipeTwoPointsUpdate(const FVector2D& ScreenPosition1, const FVector2D& ScreenPosition2, float DownTime);
	void OnPinchStarted(const FVector2D& AnchorPosition1, const FVector2D& AnchorPosition2, float DownTime);
	void OnPinchUpdate(const FVector2D& ScreenPosition1, const FVector2D& ScreenPosition2, float DownTime);

	/** Toggles the ingame menu display. */
	void OnToggleInGameMenu();

	///** Handler for mouse leaving the minimap. */
	//void MouseLeftMinimap();

	///** Handler for mouse pressed over minimap. */
	//void MousePressedOverMinimap();

	///** Handler for mouse release over minimap. */
	//void MouseReleasedOverMinimap();

public:
	// Ä«¸Þ¶ó
	UCameraComponent* GetCameraComponent() const;
	bool AreCoordsInNoScrollZone(const FVector2D& SwipePosition);
	void EndSwipeNow();
	AActor* GetFriendlyTarget(const FVector2D& ScreenPoint, FVector& WorldPoint) const;
	void SetSelectedActor(AActor* NewSelectedActor, const FVector& NewPosition);
	void OnZoomIn();
	void OnZoomOut();
	void UpdateCamera(float DeltaTime);
	void MouseScrolling(float DeltaTime);

	UPROPERTY(config)
		float m_fCameraScrollSpeed;
	/* List of zones to exclude from scrolling during the camera movement update. */
	TArray<FBox>	m_NoScrollZones;
	/** The initial position of the swipe/drag. */
	FVector m_vStartSwipeCoords;
	FVector2D m_vPrevSwipeScreenPosition;
	/** currently selected actor */
	TWeakObjectPtr<AActor> m_SelectedActor;
	/** Previous swipe mid point. */
	FVector2D m_vPrevSwipeMidPoint;
	/** Current amount of camera zoom. */
	float m_ZoomFactor;
	float m_fMaxZoomLevel;
	float m_fMinZoomLevel;
	bool m_bZoomingIn;
	float m_ZoomDistance;
	bool m_bIsSwipe;

public:
	FHitResult GetSelectActor(FVector2D MousePos);
	FVector2D GetMousePos();
	void TileDetecting();

	UFUNCTION(BlueprintCallable, Category = "TownBuilding")
		void SetBuildMode(EBuilding::Type EBuildType);

private:
	bool m_bBuildMode;
	bool m_bIsBuildpossibility;
	AActor* m_OldSelectActor;
	EBuilding::Type m_EBuildType;

protected:
	/** if set, input and camera updates will be ignored */
	uint8 bIgnoreInput : 1;

	UPROPERTY()
	class UNP4Input* InputHandler;

};
