#include "Goomba.h"
#include "EnumClass.h"
#include "InGameValue.h"

AGoomba::AGoomba()
{
}

AGoomba::~AGoomba()
{
}

void AGoomba::BeginPlay()
{
	AActor::BeginPlay();

	Renderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::Monster));
	Renderer->SetImage("Goomba.png");
	
	FVector GoombaScale = Renderer->GetImage()->GetScale();

	Renderer->SetTransform({ {0,0}, {GoombaScale.iX() / UInGameValue::GoombaImageXValue * UInGameValue::WindowSizeMulValue, GoombaScale.iY() / UInGameValue::GoombaImageYValue * UInGameValue::WindowSizeMulValue} });
	Renderer->CreateAnimation("Goomba_Move", "Goomba.png", 0, 1, 0.1f, true);
	Renderer->CreateAnimation("Goomba_Dead", "Goomba.png", 2, 2, 0.1f, true);

	Renderer->ChangeAnimation("Goomba_Move");
	SetActorState(EPlayerState::Move);
}

void AGoomba::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void AGoomba::StateUpdate(float _DeltaTime)
{
	switch (ActorState)
	{
	/*case EPlayerState::Idle:
		Idle(_DeltaTime);
		break;*/
	case EPlayerState::Move:
		Move(_DeltaTime);
		break;
	default:
		break;
	}

}

void AGoomba::Move(float _DeltaTime)
{
	int a = 0;
}

