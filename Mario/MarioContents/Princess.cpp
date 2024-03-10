#include "Princess.h"

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
	//BodyCollision->SetPosition({ 0, -(BodyCollision->GetTransform().GetScale().ihY()) });
	BodyCollision->SetColType(ECollisionType::Rect);
}

void APrincess::Tick(float _DeltaTime)
{
	UStateUnit::Tick(_DeltaTime);
}