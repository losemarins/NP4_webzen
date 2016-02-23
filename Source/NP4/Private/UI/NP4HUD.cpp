// Fill out your copyright notice in the Description page of Project Settings.
/* juhee
	HP Bar를 C++코드를 사용하여 구현했을 때의 코드이다.
	날리지 않고 주석처리 해 두었다.
*/


#include "NP4.h"

//#include "Define.h"
//#include "NP4GameState.h"
//#include "NP4PlayerBase.h"
//#include "NP4PlayerController.h"
//#include "NP4PlayerBase.h"
#include "NP4HUD.h"



ANP4HUD::ANP4HUD()
{

	//static ConstructorHelpers::FObjectFinder<UTexture2D> BarFillObj(TEXT("/Game/UI/HUD/BarFill"));
	//static ConstructorHelpers::FObjectFinder<UTexture2D> PlayerTeamHPObj(TEXT("/Game/UI/HUD/PlayerTeamHealthBar"));
	//static ConstructorHelpers::FObjectFinder<UTexture2D> EnemyTeamHPObj(TEXT("/Game/UI/HUD/EnemyTeamHealthBar"));

	//BarFillTexture = BarFillObj.Object;
	//PlayerTeamHPTexture = PlayerTeamHPObj.Object;
	//EnemyTeamHPTexure = EnemyTeamHPObj.Object;

}

/**
* This is the main drawing pump. it will determine which hud we need to draw (Game or PostGame). Any drawing that should occur
* regardless of the game state should go here.
*/
//void ANP4HUD::DrawHUD()
//{
	//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, FString::Printf(TEXT("function DrawHUD call 1 !")));

	//if (GEngine && GEngine->GameViewport)
	//{
	//	FVector2D ViewportSize;
	//	GEngine->GameViewport->GetViewportSize(ViewportSize);
	//	UIScale = ViewportSize.X / 2048.f;
	//}
	//Super::DrawHUD();
	////GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, FString::Printf(TEXT("function DrawHUD call 2 !")));

	//ANP4GameState const* const MyGameState = GetWorld()->GetGameState<ANP4GameState>();
	//if (MyGameState->GameMapState == EGameMapState::Stage1) // 현재 gamestate 값이 없다. 설정되면 그때 추가.
	//{
	//	// 원래 DrawActorsHealth()가 이 위치에 있음.
	//	//DrawActorsHealth();
	//}

	//DrawActorsHealth();

//}
//
////코드 실행 확인을 위해 사용한 변수
//int timetest = 0;
//int num = 0;
//void ANP4HUD::DrawActorsHealth()
//{
//	//코드 실행 확인을 위해 사용한 변수
//	timetest++;
//	num = timetest % 1000;
//
//	//if(num==0)	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, FString::Printf(TEXT("function DrawActorsHealth call 123")));
//
//	ANP4PlayerController* pController = Cast<ANP4PlayerController>(GetNP4PlayerController()); // minwook
//
//	if (pController) // minwook
//	{
//		//if (0 == num)	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, FString::Printf(TEXT("pController call !")));
//
//		APawn* TestPawn = pController->GetPossessPawn();
//
//		ANP4PlayerBase* CastPlayer = Cast<ANP4PlayerBase>(TestPawn);
//
//		float temHealth = 0.f, temMaxHealth = 0.f;
//
//		if (CastPlayer) // minwook
//		{
//			//if (0 == num)	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, FString::Printf(TEXT("CastPlayer call !")));
//
//			//Staff
//			//ANP4PlayerState* pState = CastPlayer->m_pPlayerState; // 이게 아니라 지금 NP4GameState class가 필요한 것 같아서 이것으로 하고 해보겠다.
//			ANP4GameState* const MyGameState = GetWorld()->GetGameState<ANP4GameState>();
//			if (MyGameState) // 이거 우리가 만든게 아니고, AGameState.h에 있는건데, 왜 쓰는지 모르겠다! 전략게임에서 사용하는 if문. 실행된다.
//			{
//				// 호출됨 : Menu level , MyMap(Game) level
//				// 호출x :  Town level
//				//if (0 == num)	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, FString::Printf(TEXT("MyGameState call !")));
//
//				ANP4PlayerState* pState = CastPlayer->m_pPlayerState; // minwook 
//				if (pState) // minwook
//				{
//					//호출 됨
//					//if (0 == num)	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, FString::Printf(TEXT("pState call !")));
//					temHealth = pState->GetPlayerHealth();
//					//temHealth = 70.f;
//					temMaxHealth = CastPlayer->m_pPlayerState->GetPlayerMaxHealth();
//
//					//CastPlayer는 ANP4PlayerBase !
//					DrawHealthBar(CastPlayer, temHealth / temMaxHealth, 18 * UIScale);
//
//					// 전략게임에서 DrawHealthBar에서 b\building class 사용하는 건. 이건 건물 위 bar 띄울 때!
//
//
//				}
//			}
//		}
//	}
//
//}
//
//void ANP4HUD::DrawHealthBar(AActor* ForActor, float HealthPercentage, int32 BarHeight, int OffsetY) const
//{
//	//if (0 == num)	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, FString::Printf(TEXT("DrawHealthBar call !")));
//
//	FBox BB = ForActor->GetComponentsBoundingBox();
//	FVector Center = BB.GetCenter();
//	FVector Extent = BB.GetExtent();
//	FVector2D Center2D = FVector2D(Canvas->Project(FVector(Center.X, Center.Y, Center.Z + Extent.Z)));
//	float ActorExtent = 40; // default value setting
//
//							// 건물이 아니라 캐릭터일 때! 그래서 APawn을 가져오나봐ㅏㅏㅏ
//	if (Cast<APawn>(ForActor) != NULL)
//	{
//		//if (0 == num)	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, FString::Printf(TEXT("APawn call !")));
//
//		ANP4PlayerBase* CastPlayer = Cast<ANP4PlayerBase>(ForActor);
//		if ((CastPlayer != NULL) && (CastPlayer->GetCapsuleComponent() != NULL))
//		{
//			//if (0 == num)	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, FString::Printf(TEXT("GetCapsuleComponent call !")));
//			ActorExtent = CastPlayer->GetCapsuleComponent()->GetScaledCapsuleRadius();
//		}
//	}
//
//	FVector Pos1 = Canvas->Project(FVector(Center.X, Center.Y - ActorExtent * 2, Center.Z + Extent.Z));
//	FVector Pos2 = Canvas->Project(FVector(Center.X, Center.Y + ActorExtent * 2, Center.Z + Extent.Z));
//	float HealthBarLength = (Pos2 - Pos1).Size2D();
//
//	UTexture2D* HealthBarTexture = PlayerTeamHPTexture;
//
//	float XX = Center2D.X - HealthBarLength / 2;
//	float YY = Center2D.Y + OffsetY;
//	FCanvasTileItem TileItem(FVector2D(XX, YY), HealthBarTexture->Resource, FVector2D(HealthBarLength*HealthPercentage, BarHeight), FLinearColor::White);
//	TileItem.BlendMode = SE_BLEND_Translucent;
//	TileItem.UV1 = FVector2D(HealthPercentage, 1.f);
//
//	if (0 == num)	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, FString::Printf(TEXT(" DrawItem call !")));
//
//	Canvas->DrawItem(TileItem);
//
//	//if (0 == num)	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, FString::Printf(TEXT("after DrawItem call !")));
//
//}
