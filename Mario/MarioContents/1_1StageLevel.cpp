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
#include "Castle.h"

U1_1StageLevel::U1_1StageLevel()
{
}

U1_1StageLevel::~U1_1StageLevel()
{
}

void U1_1StageLevel::BeginPlay()
{
	UCreateLevel::BeginPlay();

	ABackGroundMap* Map = SpawnActor< ABackGroundMap>(static_cast<int>(EActorType::Map));
	UCollisionMap* CollisionMap = SpawnActor< UCollisionMap>(static_cast<int>(EActorType::Map));
	APlayerMario* Mario = SpawnActor< APlayerMario>(static_cast<int>(EActorType::Player));
	AUI* PlayerUI = SpawnActor<AUI>(static_cast<int>(EActorType::UI));
	AEndFlag* EndFlag = SpawnActor<AEndFlag>(static_cast<int>(EActorType::Structure));
	ACastle* EndPointCastle = SpawnActor<ACastle>(static_cast<int>(EActorType::Structure));

	Mario->SetActorLocation({ UInGameValue::MarioInitXPos, UInGameValue::MarioInitYPos });
	PlayerUI->SetActorLocation({ UInGameValue::UIXScaleValue / 2 * UInGameValue::WindowSizeMulValue, UInGameValue::UIYScaleValue / 2 * UInGameValue::WindowSizeMulValue });
	EndPointCastle->SetActorLocation({ UInGameValue::EndPointCastleXPos, UInGameValue::EndPointCastleYPos });
	EndFlag->SetActorLocation({ UInGameValue::EndFlagXPos, UInGameValue::EndFlagYPos });
	
	ABrickBlock* BrickBlock1 = SpawnActor< ABrickBlock>(static_cast<int>(EActorType::Block));
	ABrickBlock* BrickBlock2 = SpawnActor< ABrickBlock>(static_cast<int>(EActorType::Block));
	ABrickBlock* BrickBlock3 = SpawnActor< ABrickBlock>(static_cast<int>(EActorType::Block));


	ACoinBlock* CoinBlock1 = SpawnCoinBlock(EActorType::Block, EItemType::Coin);
	ACoinBlock* CoinBlock2 = SpawnCoinBlock(EActorType::Block, EItemType::Item);
	ACoinBlock* CoinBlock3 = SpawnCoinBlock(EActorType::Block, EItemType::Coin);
	ACoinBlock* CoinBlock4 = SpawnCoinBlock(EActorType::Block, EItemType::Coin);

	int StandardYPos = 456;
	int SecondYPos = 264;

	CoinBlock1->SetActorLocation({ 792, StandardYPos });
	BrickBlock1->SetActorLocation({ 984, StandardYPos });
	CoinBlock2->SetActorLocation({ 984 + 48,StandardYPos });
	BrickBlock2->SetActorLocation({ 984 + 48 * 2,StandardYPos });
	CoinBlock3->SetActorLocation({ 984 + 48 * 3,StandardYPos });
	BrickBlock3->SetActorLocation({ 984 + 48 * 4,StandardYPos });
	CoinBlock4->SetActorLocation({ 984 + 48 * 2,SecondYPos });
}

void U1_1StageLevel::Tick(float _DeltaTime)
{
	UCreateLevel::Tick(_DeltaTime);
}