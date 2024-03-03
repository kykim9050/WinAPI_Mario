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
#include "EndFlag.h"

UTestLevel::UTestLevel()
{
}

UTestLevel::~UTestLevel()
{
}

void UTestLevel::BeginPlay()
{
	UCreateLevel::BeginPlay();

	ABackGroundMap* Map = SpawnActor< ABackGroundMap>(static_cast<int>(EActorType::Map));
	UCollisionMap* CollisionMap = SpawnActor< UCollisionMap>(static_cast<int>(EActorType::Map));
	APlayerMario* Mario = SpawnActor< APlayerMario>(static_cast<int>(EActorType::Player));
	AUI* PlayerUI = SpawnActor<AUI>(static_cast<int>(EActorType::UI));
	AEndFlag* EndFlag = SpawnActor<AEndFlag>(static_cast<int>(EActorType::Structure));

	//ABrickBlock* BrickBlock1 = SpawnActor< ABrickBlock>(static_cast<int>(EActorType::Block));
	//ABrickBlock* BrickBlock2 = SpawnActor< ABrickBlock>(static_cast<int>(EActorType::Block));
	//ABrickBlock* BrickBlock3 = SpawnActor< ABrickBlock>(static_cast<int>(EActorType::Block));
	//ABrickBlock* BrickBlock4 = SpawnActor< ABrickBlock>(static_cast<int>(EActorType::Block));

	ACoinBlock* CoinBlock1 = SpawnCoinBlock(EActorType::Block, EItemType::Coin);
	//ACoinBlock* CoinBlock1 = SpawnActor< ACoinBlock>(static_cast<int>(EActorType::Block));
	//ACoinBlock* CoinBlock2 = SpawnActor< ACoinBlock>(static_cast<int>(EActorType::Block));
	//ACoinBlock* CoinBlock3 = SpawnActor< ACoinBlock>(static_cast<int>(EActorType::Block));
	//ACoinBlock* CoinBlock4 = SpawnActor< ACoinBlock>(static_cast<int>(EActorType::Block));
	ACoinBlock* CoinBlock5 = SpawnCoinBlock(EActorType::Block, EItemType::Item);
	ACoinBlock* CoinBlock6 = SpawnCoinBlock(EActorType::Block, EItemType::Item);
	ACoinBlock* CoinBlock7 = SpawnCoinBlock(EActorType::Block, EItemType::Coin);

	//AGoomba* MonsterGoomba1 = SpawnActor<AGoomba>(static_cast<int>(EActorType::Monster));
	//AGoomba* MonsterGoomba2 = SpawnActor<AGoomba>(static_cast<int>(EActorType::Monster));
	//AGoomba* MonsterGoomba3 = SpawnActor<AGoomba>(static_cast<int>(EActorType::Monster));
	//AKoopaTroopa* MonsterKoopaTroopa1 = SpawnActor< AKoopaTroopa>(static_cast<int>(EActorType::Monster));
	//AKoopaTroopa* MonsterKoopaTroopa2 = SpawnActor< AKoopaTroopa>(static_cast<int>(EActorType::Monster));
	//APiranhaPlant* MonsterPiranhaPlant1 = SpawnActor< APiranhaPlant>(static_cast<int>(EActorType::Monster));

	Mario->SetActorLocation({ UInGameValue::MarioInitXPos, UInGameValue::MarioInitYPos });
	PlayerUI->SetActorLocation({ UInGameValue::UIXScaleValue / 2 * UInGameValue::WindowSizeMulValue, UInGameValue::UIYScaleValue / 2 * UInGameValue::WindowSizeMulValue });
	EndFlag->SetActorLocation({ 200 * UInGameValue::WindowSizeMulValue, UInGameValue::EndFlagYPos/*124*/ * UInGameValue::WindowSizeMulValue });

	int StandardYPos = 450;
	int StandardXPos = 600;

	//BrickBlock1->SetActorLocation({ StandardXPos,StandardYPos });
	//BrickBlock2->SetActorLocation({ StandardXPos + 48,StandardYPos });
	//BrickBlock3->SetActorLocation({ StandardXPos + 48 * 2,StandardYPos });
	//BrickBlock4->SetActorLocation({ StandardXPos + 48 * 3,StandardYPos });
	
	CoinBlock1->SetActorLocation({ 250 + 48 * 4,StandardYPos });
	//CoinBlock2->SetActorLocation({ 250 + 48 * 5,450 });
	//CoinBlock3->SetActorLocation({ 250 + 48 * 6,450 });
	//CoinBlock4->SetActorLocation({ 250 + 48 * 7,450 });
	CoinBlock5->SetActorLocation({ 250 + 48 * 8,StandardYPos });
	CoinBlock6->SetActorLocation({ 250 + 48 * 12,StandardYPos });
	CoinBlock7->SetActorLocation({ 250 + 48 * 16,StandardYPos });

	//MonsterPiranhaPlant1->SetActorLocation({ 1875,550 });
	//
	//MonsterKoopaTroopa1->SetActorLocation({ 1000,500 });
	//MonsterKoopaTroopa2->SetActorLocation({ 1700,500 });
	//
	//MonsterGoomba1->SetActorLocation({ 600, 500 });
	//MonsterGoomba2->SetActorLocation({ 700, 500 });
	//MonsterGoomba3->SetActorLocation({ 900, 500 });
}

void UTestLevel::Tick(float _DeltaTime)
{
	UCreateLevel::Tick(_DeltaTime);
}