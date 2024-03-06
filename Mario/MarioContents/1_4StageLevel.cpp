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




}

void U1_4StageLevel::Tick(float _DeltaTime)
{
	UCreateLevel::Tick(_DeltaTime);
}

