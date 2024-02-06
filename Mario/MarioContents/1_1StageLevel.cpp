#include "1_1StageLevel.h"
#include "BackGroundMap.h"

U1_1StageLevel::U1_1StageLevel()
{
}

U1_1StageLevel::~U1_1StageLevel()
{
}

void U1_1StageLevel::BeginPlay()
{
	ULevel::BeginPlay();

	BackGroundMap* Stage1_1Map = SpawnActor< BackGroundMap>();
}

void U1_1StageLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);
}
