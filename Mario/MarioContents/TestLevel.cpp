#include "TestLevel.h"
#include "1_1StageLevel.h"
#include "BackGroundMap.h"
#include "PlayerMario.h"
#include "CollisionMap.h"
#include "InGameValue.h"
#include "UI.h"
#include "Goomba.h"
#include "KoopaTroopa.h"
#include <EnginePlatform/EngineInput.h>
#include "PiranhaPlant.h"
#include "BrickBlock.h"
#include "CoinBlock.h"

UTestLevel::UTestLevel()
{
}

UTestLevel::~UTestLevel()
{
}

void UTestLevel::BeginPlay()
{
	ULevel::BeginPlay();

	ABackGroundMap* Map = SpawnActor< ABackGroundMap>();
	UCollisionMap* CollisionMap = SpawnActor< UCollisionMap>();
	APlayerMario* Mario = SpawnActor< APlayerMario>();
	AUI* PlayerUI = SpawnActor<AUI>();
	//APiranhaPlant* MonsterPiranhaPlant1 = SpawnActor< APiranhaPlant>();
	ABrickBlock* BrickBlock1 = SpawnActor< ABrickBlock>();
	ACoinBlock* CoinBlock1 = SpawnActor< ACoinBlock>();

	Mario->SetActorLocation({ UInGameValue::MarioInitXPos, UInGameValue::MarioInitYPos });
	PlayerUI->SetActorLocation({ UInGameValue::UIXScaleValue / 2 * UInGameValue::WindowSizeMulValue, UInGameValue::UIYScaleValue / 2 * UInGameValue::WindowSizeMulValue });
	//MonsterPiranhaPlant1->SetActorLocation({ 500,700 });
	BrickBlock1->SetActorLocation({ 500,450 });
	CoinBlock1->SetActorLocation({ 600,450 });
}

void UTestLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	if (true == UEngineInput::IsDown(VK_F3))
	{
		APlayerMario* Player = APlayerMario::GetMainPlayer();

		if (nullptr == Player)
		{
			UEngineDebug::OutPutDebugText("Player가 없습니다.");
			return;
		}

		if (Player->GetBodyCollision()->IsActive())
		{
			Player->GetBodyCollision()->SetActive(false);
			Player->GetRenderer()->SetAlpha(0.5f);
		}
		else
		{
			Player->GetBodyCollision()->SetActive(true);
			Player->GetRenderer()->SetAlpha(1.0f);
		}
	}
}