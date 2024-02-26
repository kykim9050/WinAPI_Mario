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

	ABrickBlock* BrickBlock1 = SpawnActor< ABrickBlock>();
	ACoinBlock* CoinBlock1 = SpawnActor< ACoinBlock>();
	
	AGoomba* MonsterGoomba1 = SpawnActor<AGoomba>();
	AGoomba* MonsterGoomba2 = SpawnActor<AGoomba>();
	AGoomba* MonsterGoomba3 = SpawnActor<AGoomba>();
	
	AKoopaTroopa* MonsterKoopaTroopa1 = SpawnActor< AKoopaTroopa>();
	AKoopaTroopa* MonsterKoopaTroopa2 = SpawnActor< AKoopaTroopa>();
	
	APiranhaPlant* MonsterPiranhaPlant1 = SpawnActor< APiranhaPlant>();

	Mario->SetActorLocation({ UInGameValue::MarioInitXPos, UInGameValue::MarioInitYPos });
	PlayerUI->SetActorLocation({ UInGameValue::UIXScaleValue / 2 * UInGameValue::WindowSizeMulValue, UInGameValue::UIYScaleValue / 2 * UInGameValue::WindowSizeMulValue });
	BrickBlock1->SetActorLocation({ 250,450 });
	CoinBlock1->SetActorLocation({ 350,450 });
	
	MonsterPiranhaPlant1->SetActorLocation({ 1875,550 });
	
	MonsterKoopaTroopa1->SetActorLocation({ 1000,500 });
	MonsterKoopaTroopa2->SetActorLocation({ 1700,500 });
	
	MonsterGoomba1->SetActorLocation({ 1800, 500 });
	MonsterGoomba2->SetActorLocation({ 1300, 500 });
	MonsterGoomba3->SetActorLocation({ 2000, 500 });
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