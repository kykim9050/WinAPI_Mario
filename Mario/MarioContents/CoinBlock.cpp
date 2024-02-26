#include "CoinBlock.h"

ACoinBlock::ACoinBlock()
{
}

ACoinBlock::~ACoinBlock()
{
}

void ACoinBlock::BeginPlay()
{
	ABlockUnit::BeginPlay();

	Renderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::Block));
	Renderer->SetImage("CoinBlock.png");

	FVector CoinBlockScale = Renderer->GetImage()->GetScale();

	Renderer->SetTransform({ {0,0}, {CoinBlockScale.iX() / UInGameValue::CoinBlockImageXValue * UInGameValue::WindowSizeMulValue, CoinBlockScale.iY() / UInGameValue::CoinBlockImageYValue * UInGameValue::WindowSizeMulValue} });
	Renderer->CreateAnimation("CoinBlock_Init", "CoinBlock.png", { 0, 0, 0, 0, 1, 2, 1 }, 0.15f, true);
	Renderer->CreateAnimation("CoinBlock_Hit", "CoinBlock.png", 3, 3, 0.1f, true);
	Renderer->CreateAnimation("CoinBlock_AfterHit", "CoinBlock.png", 4, 4, 0.1f, true);

	BodyCollision = CreateCollision(ECollisionOrder::Block);
	BodyCollision->SetTransform({ { 0,0 }, { UInGameValue::BlockCollisionScaleX, UInGameValue::BlockCollisionScaleY} });
	BodyCollision->SetColType(ECollisionType::Rect);

	SetActorState(EActorState::FirstInit);
}

void ACoinBlock::Tick(float _DeltaTime)
{
	ABlockUnit::Tick(_DeltaTime);
}

void ACoinBlock::IdleStart()
{
	ABlockUnit::IdleStart();
	Renderer->ChangeAnimation("CoinBlock_Init");
}