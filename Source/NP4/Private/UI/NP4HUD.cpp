// Fill out your copyright notice in the Description page of Project Settings.
/* juhee
	HP Bar�� C++�ڵ带 ����Ͽ� �������� ���� �ڵ��̴�.
	������ �ʰ� �ּ�ó�� �� �ξ���.
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
	//if (MyGameState->GameMapState == EGameMapState::Stage1) // ���� gamestate ���� ����. �����Ǹ� �׶� �߰�.
	//{
	//	// ���� DrawActorsHealth()�� �� ��ġ�� ����.
	//	//DrawActorsHealth();
	//}

	//DrawActorsHealth();

//}
//
////�ڵ� ���� Ȯ���� ���� ����� ����
//int timetest = 0;
//int num = 0;
//void ANP4HUD::DrawActorsHealth()
//{
//	//�ڵ� ���� Ȯ���� ���� ����� ����
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
//			//ANP4PlayerState* pState = CastPlayer->m_pPlayerState; // �̰� �ƴ϶� ���� NP4GameState class�� �ʿ��� �� ���Ƽ� �̰����� �ϰ� �غ��ڴ�.
//			ANP4GameState* const MyGameState = GetWorld()->GetGameState<ANP4GameState>();
//			if (MyGameState) // �̰� �츮�� ����� �ƴϰ�, AGameState.h�� �ִ°ǵ�, �� ������ �𸣰ڴ�! �������ӿ��� ����ϴ� if��. ����ȴ�.
//			{
//				// ȣ��� : Menu level , MyMap(Game) level
//				// ȣ��x :  Town level
//				//if (0 == num)	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, FString::Printf(TEXT("MyGameState call !")));
//
//				ANP4PlayerState* pState = CastPlayer->m_pPlayerState; // minwook 
//				if (pState) // minwook
//				{
//					//ȣ�� ��
//					//if (0 == num)	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, FString::Printf(TEXT("pState call !")));
//					temHealth = pState->GetPlayerHealth();
//					//temHealth = 70.f;
//					temMaxHealth = CastPlayer->m_pPlayerState->GetPlayerMaxHealth();
//
//					//CastPlayer�� ANP4PlayerBase !
//					DrawHealthBar(CastPlayer, temHealth / temMaxHealth, 18 * UIScale);
//
//					// �������ӿ��� DrawHealthBar���� b\building class ����ϴ� ��. �̰� �ǹ� �� bar ��� ��!
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
//							// �ǹ��� �ƴ϶� ĳ������ ��! �׷��� APawn�� ����������������
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
