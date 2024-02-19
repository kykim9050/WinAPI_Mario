#include "1_1StageLevel.h"
#include "BackGroundMap.h"
#include "PlayerMario.h"
#include "CollisionMap.h"
#include "InGameValue.h"
#include "UI.h"

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
	UCollisionMap* Stage1_1CollisionMap = SpawnActor< UCollisionMap>();
	APlayerMario* Mario = SpawnActor< APlayerMario>();
	AUI* PlayerUI = SpawnActor<AUI>();

	PlayerUI->SetActorLocation({ UInGameValue::UIXScaleValue / 2 * UInGameValue::WindowSizeMulValue, UInGameValue::UIYScaleValue / 2 * UInGameValue::WindowSizeMulValue });
	Mario->SetActorLocation({ UInGameValue::MarioInitXPos, UInGameValue::MarioInitYPos });
}

void U1_1StageLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);
}
