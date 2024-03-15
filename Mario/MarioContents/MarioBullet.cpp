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
	Renderer->CreateAnimation("FireBallDestroy", "FireBall.png", 4, 6, 0.05f, false);
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

	CalHorizonVelocityVector(_DeltaTime);
	CalJumpVelocityVector(_DeltaTime);
	CalGravityVelocityVector(_DeltaTime);
	CalTotalVelocityVector(_DeltaTime);
	AddActorLocation(TotalVelocityVector * _DeltaTime);
}

void AMarioBullet::FallDownStart()
{
	GravityVelocityVector = FVector::Down * FallDownGravityVel;
	HorizonVelocityVector = FVector::Right * 500.0f;
}

void AMarioBullet::ExplosionStart()
{
	Renderer->ChangeAnimation("FireBallDestroy");
}

void AMarioBullet::FallDown(float _DeltaTime)
{
	if (true == FallDownGroundCheck())
	{
		return;
	}

	CalHorizonVelocityVector(_DeltaTime);
	CalTotalVelocityVector(_DeltaTime);
	AddActorLocation(TotalVelocityVector * _DeltaTime);
}

void AMarioBullet::Explosion(float _DeltaTime)
{
	if (Renderer->IsCurAnimationEnd())
	{
		int a = 0;
	}
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

void AMarioBullet::CalHorizonVelocityVector(float _DeltaTime)
{
	FVector RightPos = GetActorLocation();
	FVector LeftPos = GetActorLocation();

	RightPos.X += GetBodyCollision()->GetTransform().GetRadius();
	LeftPos.X -= GetBodyCollision()->GetTransform().GetRadius();

	Color8Bit RightColor = UContentsFunction::GetCollisionMapImg()->GetColor(RightPos.iX(), RightPos.iY(), UInGameValue::CollisionColor);
	Color8Bit LeftColor = UContentsFunction::GetCollisionMapImg()->GetColor(LeftPos.iX(), LeftPos.iY(), UInGameValue::CollisionColor);

	if (RightColor == UInGameValue::CollisionColor
		|| LeftColor == UInGameValue::CollisionColor
		|| RightPos.X >= GetWorld()->GetCameraPos().X + static_cast<float>(UInGameValue::ResultMainWindowXScale)
		|| LeftPos.X <= GetWorld()->GetCameraPos().X)
	{
		StateChange(EActorState::Explosion);
		return;
	}
}

bool AMarioBullet::FallDownGroundCheck()
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

