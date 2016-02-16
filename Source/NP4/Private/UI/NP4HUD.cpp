// Fill out your copyright notice in the Description page of Project Settings.

#include "NP4.h"

#include "Define.h"
#include "NP4GameState.h"
#include "NP4PlayerBase.h"
#include "NP4PlayerController.h"
#include "NP4PlayerBase.h"
#include "NP4HUD.h"



ANP4HUD::ANP4HUD()
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> BarFillObj(TEXT("/Game/UI/HUD/BarFill"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> PlayerTeamHPObj(TEXT("/Game/UI/HUD/PlayerTeamHealthBar"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> EnemyTeamHPObj(TEXT("/Game/UI/HUD/EnemyTeamHealthBar"));

	BarFillTexture = BarFillObj.Object;
	PlayerTeamHPTexture = PlayerTeamHPObj.Object;
	EnemyTeamHPTexure = EnemyTeamHPObj.Object;

}

/**
* This is the main drawing pump. it will determine which hud we need to draw (Game or PostGame). Any drawing that should occur
* regardless of the game state should go here.
*/
void ANP4HUD::DrawHUD()
{
	if (GEngine && GEngine->GameViewport)
	{
		FVector2D ViewportSize;
		GEngine->GameViewport->GetViewportSize(ViewportSize);
		UIScale = ViewportSize.X / 2048.f;
	}
	Super::DrawHUD();
	
	ANP4GameState const* const MyGameState = GetWorld()->GetGameState<ANP4GameState>();
	if (MyGameState)
	{
		// 원래 DrawActorsHealth()가 이 위치에 있음.
	}

	DrawActorsHealth();

}

void ANP4HUD::DrawActorsHealth()
{
	ANP4PlayerController* pController = Cast<ANP4PlayerController>(GetNP4PlayerController());
	
	if (pController)
	{
		APawn* TestPawn = pController->GetPossessPawn();

		ANP4PlayerBase* CastPlayer = Cast<ANP4PlayerBase>(TestPawn);

		float temHealth = 0.f, temMaxHealth = 0.f;

		if (CastPlayer)
		{
			//Staff
			temHealth = CastPlayer->m_pPlayerState->GetPlayerHealth();
			temMaxHealth = CastPlayer->m_pPlayerState->GetPlayerMaxHealth();

			DrawHealthBar(CastPlayer, temHealth / temMaxHealth, 18 * UIScale);
		}
	}
	
}

void ANP4HUD::DrawHealthBar(AActor* ForActor, float HealthPct, int32 BarHeight, int OffsetY) const
{
	// I have to do it tomorrow
}
