#include "StageLevel.h"
#include "PlayerMario.h"
#include "BackGroundMap.h"
#include "CollisionMap.h"
#include "UI.h"
#include "LevelIntro.h"
#include "Windows.h"

UStageLevel::UStageLevel()
{
}

UStageLevel::~UStageLevel()
{
}

void UStageLevel::BeginPlay()
{
	UDebugLevel::BeginPlay();

	Map = SpawnActor<ABackGroundMap>(static_cast<int>(EActorType::Map));
	ColMap = SpawnActor<UCollisionMap>(static_cast<int>(EActorType::Map));
	Mario = SpawnActor< APlayerMario>(static_cast<int>(EActorType::Player));
	PlayerUI = SpawnActor<AUI>(static_cast<int>(EActorType::UI));

	SetTimeScale(EActorType::UI, 0.0f);
	SetTimeScale(EActorType::Player, 0.0f);
	SetTimeScale(EActorType::Monster, 0.0f);

	ALevelIntro* LevelInfo = SpawnActor<ALevelIntro>(static_cast<int>(EActorType::Intro));
}

void UStageLevel::Tick(float _DeltaTime)
{
	UDebugLevel::Tick(_DeltaTime);
}

void UStageLevel::LevelStart(ULevel* _PrevLevel)
{
	UDebugLevel::LevelStart(_PrevLevel);
}

void UStageLevel::LevelEnd(ULevel* _NextLevel)
{
	UDebugLevel::LevelEnd(_NextLevel);
}
