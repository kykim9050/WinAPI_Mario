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
	ABrickBlock* BrickBlock4 = SpawnActor< ABrickBlock>(static_cast<int>(EActorType::Block));
	ABrickBlock* BrickBlock5 = SpawnActor< ABrickBlock>(static_cast<int>(EActorType::Block));
	ABrickBlock* BrickBlock6 = SpawnActor< ABrickBlock>(static_cast<int>(EActorType::Block));
	ABrickBlock* BrickBlock7 = SpawnActor< ABrickBlock>(static_cast<int>(EActorType::Block));
	ABrickBlock* BrickBlock8 = SpawnActor< ABrickBlock>(static_cast<int>(EActorType::Block));
	ABrickBlock* BrickBlock9 = SpawnActor< ABrickBlock>(static_cast<int>(EActorType::Block));
	ABrickBlock* BrickBlock10 = SpawnActor< ABrickBlock>(static_cast<int>(EActorType::Block));
	ABrickBlock* BrickBlock11 = SpawnActor< ABrickBlock>(static_cast<int>(EActorType::Block));
	ABrickBlock* BrickBlock12 = SpawnActor< ABrickBlock>(static_cast<int>(EActorType::Block));
	ABrickBlock* BrickBlock13 = SpawnActor< ABrickBlock>(static_cast<int>(EActorType::Block));
	ABrickBlock* BrickBlock14 = SpawnActor< ABrickBlock>(static_cast<int>(EActorType::Block));
	ABrickBlock* BrickBlock15 = SpawnActor< ABrickBlock>(static_cast<int>(EActorType::Block));
	ABrickBlock* BrickBlock16 = SpawnActor< ABrickBlock>(static_cast<int>(EActorType::Block));
	ABrickBlock* BrickBlock17 = SpawnActor< ABrickBlock>(static_cast<int>(EActorType::Block));
	ABrickBlock* BrickBlock18 = SpawnActor< ABrickBlock>(static_cast<int>(EActorType::Block));
	ABrickBlock* BrickBlock19 = SpawnActor< ABrickBlock>(static_cast<int>(EActorType::Block));


	ACoinBlock* CoinBlock1 = SpawnCoinBlock(EActorType::Block, EItemType::Coin);
	ACoinBlock* CoinBlock2 = SpawnCoinBlock(EActorType::Block, EItemType::Item);
	ACoinBlock* CoinBlock3 = SpawnCoinBlock(EActorType::Block, EItemType::Coin);
	ACoinBlock* CoinBlock4 = SpawnCoinBlock(EActorType::Block, EItemType::Coin);
	ACoinBlock* CoinBlock5 = SpawnCoinBlock(EActorType::Block, EItemType::Item);
	ACoinBlock* CoinBlock6 = SpawnCoinBlock(EActorType::Block, EItemType::Coin);
	ACoinBlock* CoinBlock7 = SpawnCoinBlock(EActorType::Block, EItemType::Coin);
	ACoinBlock* CoinBlock8 = SpawnCoinBlock(EActorType::Block, EItemType::Coin);
	ACoinBlock* CoinBlock9 = SpawnCoinBlock(EActorType::Block, EItemType::Coin);
	ACoinBlock* CoinBlock10 = SpawnCoinBlock(EActorType::Block, EItemType::Coin);


	int StandardYPos = 456;
	int SecondYPos = 264;

	CoinBlock1->SetActorLocation({ 792, StandardYPos });
	BrickBlock1->SetActorLocation({ 984, StandardYPos });
	CoinBlock2->SetActorLocation({ 984 + 48,StandardYPos });
	BrickBlock2->SetActorLocation({ 984 + 48 * 2,StandardYPos });
	CoinBlock3->SetActorLocation({ 984 + 48 * 3,StandardYPos });
	BrickBlock3->SetActorLocation({ 984 + 48 * 4,StandardYPos });
	CoinBlock4->SetActorLocation({ 984 + 48 * 2,SecondYPos });


	BrickBlock4->SetActorLocation({ 3720, StandardYPos });
	CoinBlock5->SetActorLocation({ 3720 + 48, StandardYPos });
	BrickBlock5->SetActorLocation({ 3720 + 48 *2, StandardYPos });
	BrickBlock6->SetActorLocation({ 3720 + 48 * 3, SecondYPos });
	BrickBlock7->SetActorLocation({ 3720 + 48 * 4, SecondYPos });
	BrickBlock8->SetActorLocation({ 3720 + 48 * 5, SecondYPos });
	BrickBlock9->SetActorLocation({ 3720 + 48 * 6, SecondYPos });
	BrickBlock10->SetActorLocation({ 3720 + 48 * 7, SecondYPos });
	BrickBlock11->SetActorLocation({ 3720 + 48 * 8, SecondYPos });
	BrickBlock12->SetActorLocation({ 3720 + 48 * 9, SecondYPos });
	BrickBlock13->SetActorLocation({ 3720 + 48 * 10, SecondYPos });

	BrickBlock14->SetActorLocation({ 3720 + 48 * 14, SecondYPos });
	BrickBlock15->SetActorLocation({ 3720 + 48 * 15, SecondYPos });
	BrickBlock16->SetActorLocation({ 3720 + 48 * 16, SecondYPos });
	CoinBlock6->SetActorLocation({ 3720 + 48 * 17, SecondYPos });
	BrickBlock17->SetActorLocation({ 3720 + 48 * 17, StandardYPos });

	BrickBlock18->SetActorLocation({ 4776 + 48, StandardYPos });
	BrickBlock19->SetActorLocation({ 4776 + 48 * 2, StandardYPos });
	CoinBlock7->SetActorLocation({ 4776 + 48 * 7, StandardYPos });
	CoinBlock8->SetActorLocation({ 4776 + 48 * 10, StandardYPos });
	CoinBlock9->SetActorLocation({ 4776 + 48 * 13, StandardYPos });
	CoinBlock10->SetActorLocation({ 4776 + 48 * 10, SecondYPos });
}

void U1_1StageLevel::Tick(float _DeltaTime)
{
	UCreateLevel::Tick(_DeltaTime);
}