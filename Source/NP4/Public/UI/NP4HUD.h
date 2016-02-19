// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "NP4HUD.generated.h"

/**
 * 
 */
UCLASS()
class NP4_API ANP4HUD : public AHUD
{
	GENERATED_BODY()

public:
	ANP4HUD();

	// Begin HUD interface
	virtual void DrawHUD() override;
	// End HUD interface

	/** current UI scale */
	//float UIScale;
	
	
	/**
	* Draws health bar for specific actor.
	*
	* @param		ForActor		Actor for which the health bar is for.
	* @param		HealthPct	Current Health percentage.
	* @param		BarHeight	Height of the health bar
	* @param		OffsetY		Y Offset of the bealth bar.
	*/
//	void DrawHealthBar(AActor* ForActor, float HealthPct, int32 BarHeight, int OffsetY = 0) const;
//
//	/** draw health bars for actors */
//	void DrawActorsHealth();
//
//protected:
//
//	/** gets player (hero) controller */
//	class ANP4HeroController* GetHeroController() const;
//
//	/** gray health bar terxture */
//	UPROPERTY()
//	class UTexture2D* BarFillTexture;
//
//	/**player team health bar texture */
//	UPROPERTY()
//	class UTexture2D* PlayerTeamHPTexture;
//
//	/** enemy team health bar texture */
//	UPROPERTY()
//	class UTexture2D* EnemyTeamHPTexure;


};
