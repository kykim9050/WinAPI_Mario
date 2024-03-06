#include "1_4StageLevel.h"
#include "BackGroundMap.h"
#include "CollisionMap.h"


U1_4StageLevel::U1_4StageLevel()
{
}

U1_4StageLevel::~U1_4StageLevel()
{
}

void U1_4StageLevel::BeginPlay()
{
	UCreateLevel::BeginPlay();

	Map = SpawnActor<ABackGroundMap>(static_cast<int>(EActorType::Map));
	Map->GetMapRenderer()->SetImage("1_4Stage_Map.png");
	FVector MapImageFVector = Map->GetMapRenderer()->GetImage()->GetScale();
	Map->GetMapRenderer()->SetTransform({ { MapImageFVector.ihX(), MapImageFVector.ihY()}, {MapImageFVector} });

	ColMap = SpawnActor<UCollisionMap>(static_cast<int>(EActorType::Map));
	ColMap->GetColMapRenderer()->SetImage("1_4Stage_CollisionMap.png");
	FVector ColMapImageFVector = ColMap->GetColMapRenderer()->GetImage()->GetScale();
	ColMap->GetColMapRenderer()->SetTransform({ { ColMapImageFVector.ihX(), ColMapImageFVector.ihY()}, {ColMapImageFVector} });

	Mario = SpawnActor< APlayerMario>(static_cast<int>(EActorType::Player));
	Mario->SetActorLocation({ UInGameValue::MarioInitXPos, UInGameValue::MarioInitYPos });

	//AUI* PlayerUI = SpawnActor<AUI>(static_cast<int>(EActorType::UI));
	//PlayerUI->SetActorLocation({ UInGameValue::UIXScaleValue / 2 * UInGameValue::WindowSizeMulValue, UInGameValue::UIYScaleValue / 2 * UInGameValue::WindowSizeMulValue });

}

void U1_4StageLevel::Tick(float _DeltaTime)
{
	UCreateLevel::Tick(_DeltaTime);
}

