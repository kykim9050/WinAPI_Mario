#include <EngineCore/EngineCore.h>
#include "TestLevel.h"
#include "1_1StageLevel.h"
#include "1_4StageLevel.h"
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
#include "LevelIntro.h"
#include "Koopa.h"
#include "BridgeBlock.h"
#include "CastleBridge.h"
#include "KoopaBullet.h"
#include "FootBoard.h"
#include "Princess.h"
#include "SignalCollision.h"
#include "RotatingFire.h"
#include "ChangingLevel.h"
#include "MarioBullet.h"

UTestLevel::UTestLevel()
{
}

UTestLevel::~UTestLevel()
{
}

void UTestLevel::BeginPlay()
{
	UStageLevel::BeginPlay();

	Mario->SetActorLocation({ UInGameValue::Stage1_4MarioInitXPos, UInGameValue::Stage1_4MarioInitYPos });
	//Mario->SetActorLocation({ 6000, 400 });

	Map->GetMapRenderer()->SetImage("1_1Stage_Map.png");
	FVector MapImageFVector = Map->GetMapRenderer()->GetImage()->GetScale();
	Map->GetMapRenderer()->SetTransform({ { MapImageFVector.ihX(), MapImageFVector.ihY()}, {MapImageFVector} });

	ColMap->GetColMapRenderer()->SetImage("1_1Stage_CollisionMap.png");
	FVector ColMapImageFVector = ColMap->GetColMapRenderer()->GetImage()->GetScale();
	ColMap->GetColMapRenderer()->SetTransform({ { ColMapImageFVector.ihX(), ColMapImageFVector.ihY()}, {ColMapImageFVector} });

	ABlockUnit* CoinBlock = SpawnCoinBlock(EActorType::Block, EItemType::Item);
	ABlockUnit* BrickBlock1 = SpawnActor<ABrickBlock>();
	ABlockUnit* BrickBlock2 = SpawnActor<ABrickBlock>();
	ABlockUnit* BrickBlock3 = SpawnActor<ABrickBlock>();
	CoinBlock->SetActorLocation({ 300, 500 });
	BrickBlock1->SetActorLocation({ 348, 500 });
	BrickBlock2->SetActorLocation({ 348 + 48, 500 });
	BrickBlock3->SetActorLocation({ 348 + 48 * 2, 500 });



	//AMarioBullet* PlayerBullet = SpawnActor<AMarioBullet>();
	//PlayerBullet->SetActorLocation({ 200, 400 });
	//AKoopaTroopa* MonsterTroopa1 = SpawnActor<AKoopaTroopa>(static_cast<int>(EActorType::Monster));
	//AKoopaTroopa* MonsterTroopa2 = SpawnActor<AKoopaTroopa>(static_cast<int>(EActorType::Monster));
	//AKoopaTroopa* MonsterTroopa3 = SpawnActor<AKoopaTroopa>(static_cast<int>(EActorType::Monster));
	//AKoopaTroopa* MonsterTroopa4 = SpawnActor<AKoopaTroopa>(static_cast<int>(EActorType::Monster));
	//MonsterTroopa1->SetActorLocation({ 500, 580 });
	//MonsterTroopa2->SetActorLocation({ 850, 580 });
	//MonsterTroopa3->SetActorLocation({ 950, 580 });
	//MonsterTroopa4->SetActorLocation({ 1050, 580 });

	AActor* Goomba1 = SpawnActor<AGoomba>(static_cast<int>(EActorType::Monster));
	AActor* Goomba2 = SpawnActor<AGoomba>(static_cast<int>(EActorType::Monster));
	AActor* Goomba3 = SpawnActor<AGoomba>(static_cast<int>(EActorType::Monster));
	Goomba1->SetActorLocation({ 800, 580 });
	Goomba2->SetActorLocation({ 900, 580 });
	Goomba3->SetActorLocation({ 1000, 580 });
}

void UTestLevel::Tick(float _DeltaTime)
{
	UStageLevel::Tick(_DeltaTime);

	if (UEngineInput::IsDown(VK_RETURN))
	{
		GEngine->CreateLevel<UChangingLevel>("Changing");
		GEngine->ChangeLevel("Changing");
	}
}