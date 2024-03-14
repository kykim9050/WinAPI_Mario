#include "MarioBullet.h"
#include <EnginePlatform/EngineInput.h>

AMarioBullet::AMarioBullet()
{
}

AMarioBullet::~AMarioBullet()
{
}

void AMarioBullet::BeginPlay()
{
	ABulletUnit::BeginPlay();

	Renderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::Bullet));
	Renderer->SetImage("FireBall.png");
	FVector FireBallScale = Renderer->GetImage()->GetScale();
	Renderer->SetTransform({ {0,0}, {FireBallScale.iX() / UInGameValue::FireBallImageXValue * UInGameValue::WindowSizeMulValue, FireBallScale.iY() / UInGameValue::FireBallImageYValue * UInGameValue::WindowSizeMulValue} });
	Renderer->CreateAnimation("FiringBullet", "FireBall.png", 0, 3, 0.1f, true);
	Renderer->CreateAnimation("FireBallDestroy", "FireBall.png", 4, 6, 0.1f, false);
	Renderer->ChangeAnimation("FiringBullet");

	BodyCollision = CreateCollision(ECollisionOrder::PlayerBullet);
	BodyCollision->SetTransform({ {0,0}, {UInGameValue::FireBallDia, UInGameValue::FireBallDia} });
	BodyCollision->SetColType(ECollisionType::CirCle);
	
	SetActorState(EActorState::FirstInit);
}

void AMarioBullet::Tick(float _DeltaTime)
{
	ABulletUnit::Tick(_DeltaTime);

	if (true == UEngineInput::IsDown('P'))
	{
		StateChange(EActorState::Move);
		return;
	}
}

void AMarioBullet::MoveStart()
{
	GravityVelocityVector = FVector::Down * GravityVel;
}

void AMarioBullet::Move(float _DeltaTime)
{
	ABulletUnit::Move(_DeltaTime);

	CalGravityVelocityVector(_DeltaTime);
	CalTotalVelocityVector(_DeltaTime);
	AddActorLocation(TotalVelocityVector * _DeltaTime);
}

void AMarioBullet::CalGravityVelocityVector(float _DeltaTime)
{
	
}



