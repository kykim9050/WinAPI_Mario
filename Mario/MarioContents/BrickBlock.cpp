#include "BrickBlock.h"

ABrickBlock::ABrickBlock()
{
}

ABrickBlock::~ABrickBlock()
{
}

void ABrickBlock::BeginPlay()
{
	ABlockUnit::BeginPlay();

	Renderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::Block));
	Renderer->SetImage("BrickBlock.png");

	FVector BrickBlockScale = Renderer->GetImage()->GetScale();

	Renderer->SetTransform({ {0,0}, {BrickBlockScale.iX() / UInGameValue::BrickBlockImageXValue * UInGameValue::WindowSizeMulValue, BrickBlockScale.iY() / UInGameValue::BrickBlockImageYValue * UInGameValue::WindowSizeMulValue} });
	Renderer->CreateAnimation("BrickBlock_Init", "BrickBlock.png", 0, 0, 0.1f, true);
	Renderer->CreateAnimation("BrickBlock_EmptyHit", "BrickBlock.png", 1, 1, 0.1f, true);
	Renderer->CreateAnimation("BrickBlock_Debris", "BrickBlock.png", 2, 2, 0.1f, true);
	Renderer->CreateAnimation("BrickBlock_Hit", "BrickBlock.png", 3, 3, 0.1f, true);
	Renderer->CreateAnimation("BrickBlock_AfterHit", "BrickBlock.png", 4, 4, 0.1f, true);

	BodyCollision = CreateCollision(ECollisionOrder::Block);
	BodyCollision->SetTransform({ { 0,0 }, { UInGameValue::BlockCollisionScaleX, UInGameValue::BlockCollisionScaleY} });
	BodyCollision->SetColType(ECollisionType::Rect);

	StateChange(EActorState::Idle);
}

void ABrickBlock::Tick(float _DeltaTime)
{
	ABlockUnit::Tick(_DeltaTime);
}

void ABrickBlock::StateUpdate(float _DeltaTime)
{
	ABlockUnit::StateUpdate(_DeltaTime);

	switch (ActorState)
	{
	case EActorState::Idle:
		Idle(_DeltaTime);
		break;
	default:
		break;
	}
}

void ABrickBlock::StateChange(EActorState _ActorState)
{
	ABlockUnit::StateChange(_ActorState);

	if (ActorState != _ActorState)
	{
		switch (_ActorState)
		{
		case EActorState::Idle:
			IdleStart();
			break;
		default:
			break;
		}
	}

	SetActorState(_ActorState);
}

//void ABrickBlock::CollisionUpdate(float _DeltaTime)
//{
//	CollisionCheck();
//}





void ABrickBlock::IdleStart()
{
	ABlockUnit::IdleStart();

	Renderer->ChangeAnimation("BrickBlock_Init");
}

void ABrickBlock::Idle(float _DeltaTime)
{
	ABlockUnit::Idle(_DeltaTime);
}


