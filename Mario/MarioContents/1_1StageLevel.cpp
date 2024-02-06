#include "1_1StageLevel.h"
#include "BackGroundMap.h"
#include "PlayerMario.h"

U1_1StageLevel::U1_1StageLevel()
{
}

U1_1StageLevel::~U1_1StageLevel()
{
}

void U1_1StageLevel::BeginPlay()
{
	ULevel::BeginPlay();

	ABackGroundMap* Stage1_1Map = SpawnActor< ABackGroundMap>();
	APlayerMario* Mario = SpawnActor< APlayerMario>();
}

void U1_1StageLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);
}
