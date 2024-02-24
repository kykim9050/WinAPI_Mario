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

U1_1StageLevel::U1_1StageLevel()
{
}

U1_1StageLevel::~U1_1StageLevel()
{
}

void U1_1StageLevel::BeginPlay()
{
	ULevel::BeginPlay();

	ABackGroundMap* Stage1_1Map = SpawnActor< ABackGroundMap>();
	UCollisionMap* Stage1_1CollisionMap = SpawnActor< UCollisionMap>();
	APlayerMario* Mario = SpawnActor< APlayerMario>();
	AUI* PlayerUI = SpawnActor<AUI>();
	AGoomba* MonsterGoomba1 = SpawnActor<AGoomba>();
	AGoomba* MonsterGoomba2 = SpawnActor<AGoomba>();
	AGoomba* MonsterGoomba3 = SpawnActor<AGoomba>();
	AKoopaTroopa* MonsterKoopaTroopa1 = SpawnActor< AKoopaTroopa>();
	AKoopaTroopa* MonsterKoopaTroopa2 = SpawnActor< AKoopaTroopa>();
	APiranhaPlant* MonsterPiranhaPlant1 = SpawnActor< APiranhaPlant>();

	MonsterPiranhaPlant1->SetActorLocation({500,500});
	MonsterKoopaTroopa1->SetActorLocation({ 500,500 });
	MonsterKoopaTroopa2->SetActorLocation({ 1700,500 });
	MonsterGoomba1->SetActorLocation({ 1800, 500 });
	MonsterGoomba2->SetActorLocation({ 850, 500 });
	MonsterGoomba3->SetActorLocation({ 1500, 500 });
	PlayerUI->SetActorLocation({ UInGameValue::UIXScaleValue / 2 * UInGameValue::WindowSizeMulValue, UInGameValue::UIYScaleValue / 2 * UInGameValue::WindowSizeMulValue });
	Mario->SetActorLocation({ UInGameValue::MarioInitXPos, UInGameValue::MarioInitYPos });
}

void U1_1StageLevel::Tick(float _DeltaTime)
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
