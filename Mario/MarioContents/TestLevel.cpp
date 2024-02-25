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
	APiranhaPlant* MonsterPiranhaPlant1 = SpawnActor< APiranhaPlant>();

	MonsterPiranhaPlant1->SetActorLocation({ 500,700 });
	PlayerUI->SetActorLocation({ UInGameValue::UIXScaleValue / 2 * UInGameValue::WindowSizeMulValue, UInGameValue::UIYScaleValue / 2 * UInGameValue::WindowSizeMulValue });
	Mario->SetActorLocation({ UInGameValue::MarioInitXPos, UInGameValue::MarioInitYPos });
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