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

	ABrickBlock* BrickBlock1 = SpawnActor< ABrickBlock>(static_cast<int>(EActorType::Block));
	ABrickBlock* BrickBlock2 = SpawnActor< ABrickBlock>(static_cast<int>(EActorType::Block));

	ACoinBlock* CoinBlock5 = SpawnCoinBlock(EActorType::Block, EItemType::Item);
	ACoinBlock* CoinBlock6 = SpawnCoinBlock(EActorType::Block, EItemType::Item);

	Mario->SetActorLocation({ UInGameValue::MarioInitXPos, UInGameValue::MarioInitYPos });
	PlayerUI->SetActorLocation({ UInGameValue::UIXScaleValue / 2 * UInGameValue::WindowSizeMulValue, UInGameValue::UIYScaleValue / 2 * UInGameValue::WindowSizeMulValue });
	EndPointCastle->SetActorLocation({ UInGameValue::EndPointCastleXPos, UInGameValue::EndPointCastleYPos });
	EndFlag->SetActorLocation({ UInGameValue::EndFlagXPos, UInGameValue::EndFlagYPos });

	int StandardYPos = 450;
	int StandardXPos = 600;

	BrickBlock1->SetActorLocation({ StandardXPos + 48 * 20,StandardYPos });
	BrickBlock2->SetActorLocation({ StandardXPos + 48 * 21,StandardYPos });

	CoinBlock5->SetActorLocation({ 250 + 48 * 8,StandardYPos });
	CoinBlock6->SetActorLocation({ 250 + 48 * 12,StandardYPos });
}

void U1_1StageLevel::Tick(float _DeltaTime)
{
	UCreateLevel::Tick(_DeltaTime);
}