#include "Princess.h"
#include "PlayerMario.h"

APrincess::APrincess()
{
}

APrincess::~APrincess()
{
}

void APrincess::BeginPlay()
{
	UStateUnit::BeginPlay();

	BodyCollision = CreateCollision(ECollisionOrder::Player);
	BodyCollision->SetScale({ UInGameValue::PlayerCollisionScaleX, UInGameValue::PlayerCollisionScaleY });
	BodyCollision->SetColType(ECollisionType::Rect);
}

void APrincess::Tick(float _DeltaTime)
{
	UStateUnit::Tick(_DeltaTime);
}

void APrincess::CollisionCheck()
{
	UStateUnit::CollisionCheck();

	std::vector<UCollision*> Result = std::vector<UCollision*>();

	if (nullptr == BodyCollision)
	{
		MsgBoxAssert("Princess의 BodyCollision이 null입니다.");
		return;
	}

	if (true == BodyCollision->CollisionCheck(ECollisionOrder::Player, Result))
	{
		BodyCollision->ActiveOff();
		GetPlayer()->MeetThePrincess();
		return;
	}
}