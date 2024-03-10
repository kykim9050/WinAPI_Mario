#include "SignalCollision.h"
#include "PlayerMario.h"

USignalCollision::USignalCollision()
{
}

USignalCollision::~USignalCollision()
{
}

void USignalCollision::BeginPlay()
{
	AStructureUnit::BeginPlay();

	BodyCollision = CreateCollision(ECollisionOrder::SignalCol);
	BodyCollision->SetTransform({ { 0,0 }, { UInGameValue::EndFlagCollisionXScale, UInGameValue::EndFlagCollisionYScale} });
	BodyCollision->SetColType(ECollisionType::Rect);
}

void USignalCollision::Tick(float _DeltaTime)
{
	AStructureUnit::Tick(_DeltaTime);
}

void USignalCollision::CollisionCheck()
{
	std::vector<UCollision*> Result = std::vector<UCollision*>();

	if (nullptr != BodyCollision && true == BodyCollision->CollisionCheck(ECollisionOrder::Player, Result))
	{
		BodyCollision->ActiveOff();
		APlayerMario::ReachToBossRoom();
		return;
	}
}