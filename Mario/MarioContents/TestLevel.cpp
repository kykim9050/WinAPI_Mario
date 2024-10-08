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
#include "LoadingLevel.h"
#include "MarioBullet.h"
#include "Pipe.h"

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


	AActor* Pipe1 = SpawnActor<APipe>(static_cast<int>(EActorType::Structure));
	Pipe1->SetActorLocation({ 2784, 528 });
	AActor* PiranhaFlower = SpawnActor<APiranhaPlant>(static_cast<int>(EActorType::Monster));
	PiranhaFlower->SetActorLocation({ 2784, 504});

}

void UTestLevel::Tick(float _DeltaTime)
{
	UStageLevel::Tick(_DeltaTime);

	if (UEngineInput::IsDown(VK_RETURN))
	{
		GEngine->CreateLevel<ULoadingLevel>("Changing");
		GEngine->ChangeLevel("Changing");
	}
}