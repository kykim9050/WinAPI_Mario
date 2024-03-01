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
#include "ItemUnit.h"

UTestLevel::UTestLevel()
{
}

UTestLevel::~UTestLevel()
{
}

void UTestLevel::BeginPlay()
{
	ULevel::BeginPlay();

	ABackGroundMap* Map = SpawnActor< ABackGroundMap>(static_cast<int>(EActorType::Map));
	UCollisionMap* CollisionMap = SpawnActor< UCollisionMap>(static_cast<int>(EActorType::Map));
	APlayerMario* Mario = SpawnActor< APlayerMario>(static_cast<int>(EActorType::Player));
	AUI* PlayerUI = SpawnActor<AUI>(static_cast<int>(EActorType::UI));

	//ABrickBlock* BrickBlock1 = SpawnActor< ABrickBlock>(static_cast<int>(EActorType::Block));
	//ABrickBlock* BrickBlock2 = SpawnActor< ABrickBlock>(static_cast<int>(EActorType::Block));
	//ABrickBlock* BrickBlock3 = SpawnActor< ABrickBlock>(static_cast<int>(EActorType::Block));
	//ABrickBlock* BrickBlock4 = SpawnActor< ABrickBlock>(static_cast<int>(EActorType::Block));

	ACoinBlock* CoinBlock1 = SpawnActor< ACoinBlock>(static_cast<int>(EActorType::Block));
	//ACoinBlock* CoinBlock2 = SpawnActor< ACoinBlock>(static_cast<int>(EActorType::Block));
	//ACoinBlock* CoinBlock3 = SpawnActor< ACoinBlock>(static_cast<int>(EActorType::Block));
	//ACoinBlock* CoinBlock4 = SpawnActor< ACoinBlock>(static_cast<int>(EActorType::Block));
	//AItemUnit* Coin = SpawnActor< AItemUnit>(static_cast<int>(EActorType::Item));

	AGoomba* MonsterGoomba1 = SpawnActor<AGoomba>(static_cast<int>(EActorType::Monster));
	AGoomba* MonsterGoomba2 = SpawnActor<AGoomba>(static_cast<int>(EActorType::Monster));
	AGoomba* MonsterGoomba3 = SpawnActor<AGoomba>(static_cast<int>(EActorType::Monster));
	//
	//AKoopaTroopa* MonsterKoopaTroopa1 = SpawnActor< AKoopaTroopa>(static_cast<int>(EActorType::Monster));
	//AKoopaTroopa* MonsterKoopaTroopa2 = SpawnActor< AKoopaTroopa>(static_cast<int>(EActorType::Monster));
	//
	//APiranhaPlant* MonsterPiranhaPlant1 = SpawnActor< APiranhaPlant>(static_cast<int>(EActorType::Monster));

	Mario->SetActorLocation({ UInGameValue::MarioInitXPos, UInGameValue::MarioInitYPos });
	PlayerUI->SetActorLocation({ UInGameValue::UIXScaleValue / 2 * UInGameValue::WindowSizeMulValue, UInGameValue::UIYScaleValue / 2 * UInGameValue::WindowSizeMulValue });

	//BrickBlock1->SetActorLocation({ 250,350 });
	//BrickBlock2->SetActorLocation({ 250 + 48,350 });
	//BrickBlock3->SetActorLocation({ 250 + 48 * 2,350});
	//BrickBlock4->SetActorLocation({ 250 + 48 * 3,350 });

	CoinBlock1->SetActorLocation({ 250 + 48 * 4,450 });
	//CoinBlock2->SetActorLocation({ 250 + 48 * 5,450 });
	//CoinBlock3->SetActorLocation({ 250 + 48 * 6,450 });
	//CoinBlock4->SetActorLocation({ 250 + 48 * 7,450 });

	//Coin->SetActorLocation({ 250,400 });

	//MonsterPiranhaPlant1->SetActorLocation({ 1875,550 });
	//
	//MonsterKoopaTroopa1->SetActorLocation({ 1000,500 });
	//MonsterKoopaTroopa2->SetActorLocation({ 1700,500 });
	//
	MonsterGoomba1->SetActorLocation({ 800, 500 });
	MonsterGoomba2->SetActorLocation({ 700, 500 });
	MonsterGoomba3->SetActorLocation({ 900, 500 });
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