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


UTestLevel::UTestLevel()
{
}

UTestLevel::~UTestLevel()
{
}

void UTestLevel::BeginPlay()
{
	UStageLevel::BeginPlay();

	Mario->SetActorLocation({ UInGameValue::MarioInitXPos, UInGameValue::MarioInitYPos });
	//Mario->SetActorLocation({ 6000, 400 });

	Map->GetMapRenderer()->SetImage("1_4Stage_Map.png");
	FVector MapImageFVector = Map->GetMapRenderer()->GetImage()->GetScale();
	Map->GetMapRenderer()->SetTransform({ { MapImageFVector.ihX(), MapImageFVector.ihY()}, {MapImageFVector} });

	ColMap->GetColMapRenderer()->SetImage("1_4Stage_CollisionMap.png");
	FVector ColMapImageFVector = ColMap->GetColMapRenderer()->GetImage()->GetScale();
	ColMap->GetColMapRenderer()->SetTransform({ { ColMapImageFVector.ihX(), ColMapImageFVector.ihY()}, {ColMapImageFVector} });

	AKoopa* BossMonsterKoopa = SpawnActor<AKoopa>(static_cast<int>(EActorType::Monster));
	BossMonsterKoopa->SetActorLocation({ 6600, 450 });
	//BossMonsterKoopa->SetActorLocation({ 500, 400 });

	AFootBoard* FootBoard = SpawnActor<AFootBoard>(static_cast<int>(EActorType::Block));
	FootBoard->SetActorLocation({ UInGameValue::MovingBoardInitXPos, UInGameValue::MovingBoardInitYPos});


	ACastleBridge* CastleBridge = SpawnActor<ACastleBridge>(static_cast<int>(EActorType::Structure));
	CastleBridge->SetActorLocation({ UInGameValue::BridgeStartXPos, UInGameValue::BridgeStartYPos });

	APrincess* Princess = SpawnActor<APrincess>(static_cast<int>(EActorType::Player));
	Princess->SetActorLocation({ 2440 * 3, 197 * 3 });

}

void UTestLevel::Tick(float _DeltaTime)
{
	UStageLevel::Tick(_DeltaTime);

	//if (UEngineInput::IsDown(VK_RETURN))
	//{
	//	GEngine->CreateLevel<U1_1StageLevel>("1-1");
	//	GEngine->ChangeLevel("1-1");
	//}
}