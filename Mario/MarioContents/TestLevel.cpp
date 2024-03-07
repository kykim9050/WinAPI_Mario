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
	//BossMonsterKoopa->SetActorLocation({ 6300, 360 });
	BossMonsterKoopa->SetActorLocation({ 500, 400 });

	ACastleBridge* CastleBridge = SpawnActor<ACastleBridge>(static_cast<int>(EActorType::Structure));
	

}

void UTestLevel::Tick(float _DeltaTime)
{
	UStageLevel::Tick(_DeltaTime);

	//if (UEngineInput::IsDown(VK_RETURN))
	//{
	//	GEngine->CreateLevel<U1_4StageLevel>("1-4");
	//	GEngine->ChangeLevel("1-4");
	//}
}