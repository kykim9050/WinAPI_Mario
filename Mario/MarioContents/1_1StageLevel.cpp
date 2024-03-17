#include "1_1StageLevel.h"
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
#include "BackGroundMap.h"
#include <EngineCore/EngineCore.h>
#include "1_4StageLevel.h"
#include "SoundManager.h"
#include "Pipe.h"

U1_1StageLevel::U1_1StageLevel()
{
}

U1_1StageLevel::~U1_1StageLevel()
{
}

void U1_1StageLevel::BeginPlay()
{
	UStageLevel::BeginPlay();

	Mario->SetActorLocation({ UInGameValue::Stage1_1MarioInitXPos, UInGameValue::Stage1_1MarioInitYPos });

	Map->GetMapRenderer()->SetImage("1_1Stage_Map.png");
	FVector MapImageFVector = Map->GetMapRenderer()->GetImage()->GetScale();
	Map->GetMapRenderer()->SetTransform({ { MapImageFVector.ihX(), MapImageFVector.ihY()}, {MapImageFVector} });

	ColMap->GetColMapRenderer()->SetImage("1_1Stage_CollisionMap.png");
	FVector ColMapImageFVector = ColMap->GetColMapRenderer()->GetImage()->GetScale();
	ColMap->GetColMapRenderer()->SetTransform({ { ColMapImageFVector.ihX(), ColMapImageFVector.ihY()}, {ColMapImageFVector} });

	AEndFlag* EndFlag = SpawnActor<AEndFlag>(static_cast<int>(EActorType::Structure));
	ACastle* EndPointCastle = SpawnActor<ACastle>(static_cast<int>(EActorType::Structure));
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
	ABrickBlock* BrickBlock20 = SpawnActor< ABrickBlock>(static_cast<int>(EActorType::Block));
	ABrickBlock* BrickBlock21 = SpawnActor< ABrickBlock>(static_cast<int>(EActorType::Block));
	ABrickBlock* BrickBlock22 = SpawnActor< ABrickBlock>(static_cast<int>(EActorType::Block));
	ABrickBlock* BrickBlock23 = SpawnActor< ABrickBlock>(static_cast<int>(EActorType::Block));
	ABrickBlock* BrickBlock24 = SpawnActor< ABrickBlock>(static_cast<int>(EActorType::Block));
	ABrickBlock* BrickBlock25 = SpawnActor< ABrickBlock>(static_cast<int>(EActorType::Block));
	ABrickBlock* BrickBlock26 = SpawnActor< ABrickBlock>(static_cast<int>(EActorType::Block));
	ABrickBlock* BrickBlock27 = SpawnActor< ABrickBlock>(static_cast<int>(EActorType::Block));
	ABrickBlock* BrickBlock28 = SpawnActor< ABrickBlock>(static_cast<int>(EActorType::Block));
	ABrickBlock* BrickBlock29 = SpawnActor< ABrickBlock>(static_cast<int>(EActorType::Block));
	ABrickBlock* BrickBlock30 = SpawnActor< ABrickBlock>(static_cast<int>(EActorType::Block));

	ACoinBlock* CoinBlock1 = SpawnCoinBlock(EActorType::Block, EItemType::Coin);
	ACoinBlock* CoinBlock2 = SpawnCoinBlock(EActorType::Block, EItemType::Item);
	ACoinBlock* CoinBlock3 = SpawnCoinBlock(EActorType::Block, EItemType::Coin);
	ACoinBlock* CoinBlock4 = SpawnCoinBlock(EActorType::Block, EItemType::Coin);
	ACoinBlock* CoinBlock5 = SpawnCoinBlock(EActorType::Block, EItemType::Item);
	ACoinBlock* CoinBlock6 = SpawnCoinBlock(EActorType::Block, EItemType::Coin);
	ACoinBlock* CoinBlock7 = SpawnCoinBlock(EActorType::Block, EItemType::Coin);
	ACoinBlock* CoinBlock8 = SpawnCoinBlock(EActorType::Block, EItemType::Coin);
	ACoinBlock* CoinBlock9 = SpawnCoinBlock(EActorType::Block, EItemType::Item);
	ACoinBlock* CoinBlock10 = SpawnCoinBlock(EActorType::Block, EItemType::Coin);
	ACoinBlock* CoinBlock11 = SpawnCoinBlock(EActorType::Block, EItemType::Coin);
	ACoinBlock* CoinBlock12 = SpawnCoinBlock(EActorType::Block, EItemType::Coin);
	ACoinBlock* CoinBlock13 = SpawnCoinBlock(EActorType::Block, EItemType::Item);

	AActor* Pipe1 = SpawnActor<APipe>(static_cast<int>(EActorType::Structure));
	AActor* PiranhaFlower = SpawnActor<APiranhaPlant>(static_cast<int>(EActorType::Monster));

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
	CoinBlock10->SetActorLocation({ 4776 + 48 * 10, SecondYPos });
	CoinBlock9->SetActorLocation({ 4776 + 48 * 13, StandardYPos });

	BrickBlock20->SetActorLocation({ 5688, StandardYPos });
	BrickBlock21->SetActorLocation({ 5688 + 48 * 3, SecondYPos });
	BrickBlock22->SetActorLocation({ 5688 + 48 * 4, SecondYPos });
	BrickBlock23->SetActorLocation({ 5688 + 48 * 5, SecondYPos });

	BrickBlock24->SetActorLocation({ 5688 + 48 * 5 + 48 * 5, SecondYPos });
	CoinBlock11->SetActorLocation({ 5688 + 48 * 5 + 48 * 6, SecondYPos });
	CoinBlock12->SetActorLocation({ 5688 + 48 * 5 + 48 * 7, SecondYPos });
	BrickBlock25->SetActorLocation({ 5688 + 48 * 5 + 48 * 8, SecondYPos });

	BrickBlock26->SetActorLocation({ 5688 + 48 * 5 + 48 * 6, StandardYPos });
	BrickBlock27->SetActorLocation({ 5688 + 48 * 5 + 48 * 7, StandardYPos });

	BrickBlock28->SetActorLocation({ 8088 , StandardYPos });
	BrickBlock29->SetActorLocation({ 8088 + 48, StandardYPos });
	CoinBlock13->SetActorLocation({ 8088 + 48 * 2, StandardYPos });
	BrickBlock30->SetActorLocation({ 8088 + 48 * 3, StandardYPos });

	AGoomba* MonsterGoomba1 = SpawnActor<AGoomba>(static_cast<int>(EActorType::Monster));
	AGoomba* MonsterGoomba2 = SpawnActor<AGoomba>(static_cast<int>(EActorType::Monster));
	AGoomba* MonsterGoomba3 = SpawnActor<AGoomba>(static_cast<int>(EActorType::Monster));
	AGoomba* MonsterGoomba4 = SpawnActor<AGoomba>(static_cast<int>(EActorType::Monster));
	AGoomba* MonsterGoomba5 = SpawnActor<AGoomba>(static_cast<int>(EActorType::Monster));
	AGoomba* MonsterGoomba6 = SpawnActor<AGoomba>(static_cast<int>(EActorType::Monster));
	AGoomba* MonsterGoomba7 = SpawnActor<AGoomba>(static_cast<int>(EActorType::Monster));
	AGoomba* MonsterGoomba8 = SpawnActor<AGoomba>(static_cast<int>(EActorType::Monster));
	AGoomba* MonsterGoomba9 = SpawnActor<AGoomba>(static_cast<int>(EActorType::Monster));
	AGoomba* MonsterGoomba10 = SpawnActor<AGoomba>(static_cast<int>(EActorType::Monster));
	AGoomba* MonsterGoomba11 = SpawnActor<AGoomba>(static_cast<int>(EActorType::Monster));
	AGoomba* MonsterGoomba12 = SpawnActor<AGoomba>(static_cast<int>(EActorType::Monster));
	AGoomba* MonsterGoomba13 = SpawnActor<AGoomba>(static_cast<int>(EActorType::Monster));
	AGoomba* MonsterGoomba14 = SpawnActor<AGoomba>(static_cast<int>(EActorType::Monster));
	AGoomba* MonsterGoomba15 = SpawnActor<AGoomba>(static_cast<int>(EActorType::Monster));
	AKoopaTroopa* MonsterTroopa1 = SpawnActor<AKoopaTroopa>(static_cast<int>(EActorType::Monster));
	
	int MonsterInitHeight = 580;
	int MonsterHighHeight = 200;

	MonsterGoomba1->SetActorLocation({ 1180, MonsterInitHeight });
	MonsterGoomba2->SetActorLocation({ 2444, MonsterInitHeight });
	MonsterGoomba3->SetActorLocation({ 2600, MonsterInitHeight });
	MonsterGoomba4->SetActorLocation({ 3948, MonsterHighHeight });
	MonsterGoomba5->SetActorLocation({ 4074, MonsterHighHeight });
	MonsterGoomba6->SetActorLocation({ 4800, MonsterInitHeight });
	MonsterGoomba7->SetActorLocation({ 4864, MonsterInitHeight });
	MonsterGoomba8->SetActorLocation({ 5500, MonsterInitHeight });
	MonsterGoomba9->SetActorLocation({ 5600, MonsterInitHeight });
	MonsterGoomba10->SetActorLocation({ 6000, MonsterInitHeight });
	MonsterGoomba11->SetActorLocation({ 6060, MonsterInitHeight });
	MonsterGoomba12->SetActorLocation({ 6312, MonsterInitHeight });
	MonsterGoomba13->SetActorLocation({ 6380, MonsterInitHeight });
	MonsterGoomba14->SetActorLocation({ 8340, MonsterInitHeight });
	MonsterGoomba15->SetActorLocation({ 8420, MonsterInitHeight });

	MonsterTroopa1->SetActorLocation({ 5140, MonsterInitHeight });

	Pipe1->SetActorLocation({ 2784, 528 });
	PiranhaFlower->SetActorLocation({ 2784, 504 });
}

void U1_1StageLevel::Tick(float _DeltaTime)
{
	UStageLevel::Tick(_DeltaTime);
}