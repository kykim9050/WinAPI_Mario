#include "StageLevel.h"
#include "PlayerMario.h"
#include "BackGroundMap.h"
#include "CollisionMap.h"
#include "UI.h"

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
}

void UStageLevel::Tick(float _DeltaTime)
{
	UDebugLevel::Tick(_DeltaTime);
}


