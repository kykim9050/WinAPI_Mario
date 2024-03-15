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
		StateChange(EActorState::FallDown);
		return;
	}
}

void AMarioBullet::Move(float _DeltaTime)
{
	ABulletUnit::Move(_DeltaTime);

	CalJumpVelocityVector(_DeltaTime);
	CalGravityVelocityVector(_DeltaTime);
	CalTotalVelocityVector(_DeltaTime);
	AddActorLocation(TotalVelocityVector * _DeltaTime);
}

void AMarioBullet::FallDownStart()
{
	GravityVelocityVector = FVector::Down * FallDownGravityVel;
}

void AMarioBullet::FallDown(float _DeltaTime)
{
	if (true == FallDownGrundCheck())
	{
		return;
	}

	CalTotalVelocityVector(_DeltaTime);
	AddActorLocation(TotalVelocityVector * _DeltaTime);

}

void AMarioBullet::CalGravityVelocityVector(float _DeltaTime)
{
	std::vector<UCollision*> Result = std::vector<UCollision*>();

	Color8Bit Color = UContentsFunction::GetCollisionMapImg()->GetColor(GetActorLocation().iX(), GetActorLocation().iY() + GetBodyCollision()->GetTransform().GetScale().ihY(), UInGameValue::CollisionColor);

	if (UInGameValue::CollisionColor == Color || true == GetBodyCollision()->CollisionCheck(ECollisionOrder::BlockTop, Result))
	{
		GravityVelocityVector = FVector::Zero;
	}

	GravityVelocityVector += FVector::Down * GravityAccVel * _DeltaTime;
}

void AMarioBullet::CalJumpVelocityVector(float _DeltaTime)
{
	JumpVelocityVector = FVector::Up * JumpPowerVel;
}

bool AMarioBullet::FallDownGrundCheck()
{
	std::vector<UCollision*> Result = std::vector<UCollision*>();

	Color8Bit Color = UContentsFunction::GetCollisionMapImg()->GetColor(GetActorLocation().iX(), GetActorLocation().iY() + GetBodyCollision()->GetTransform().GetScale().ihY(), UInGameValue::CollisionColor);

	if (UInGameValue::CollisionColor == Color || true == GetBodyCollision()->CollisionCheck(ECollisionOrder::BlockTop, Result))
	{
		GravityVelocityVector = FVector::Zero;
		StateChange(EActorState::Move);
		return true;
	}

	return false;
}