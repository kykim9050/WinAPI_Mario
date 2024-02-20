#include "Goomba.h"
#include "EnumClass.h"
#include "InGameValue.h"
#include "ContentsFunction.h"

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
	
	BodyCollision = CreateCollision(ECollisionOrder::Monster);
	BodyCollision->SetScale({ 100, 100 });
	BodyCollision->SetColType(ECollisionType::Rect);

	GravityVelocityVector = FVector::Down * 500.0f;
	HorizonVelocityVector = FVector::Left * 50.0f;

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
	ResultMovementUpdate(_DeltaTime);
}

void AGoomba::ResultMovementUpdate(float _DeltaTime)
{
	Color8Bit Color = UContentsFunction::GetCollisionMapImg()->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), UInGameValue::CollisionColor);

	if (UInGameValue::CollisionColor == Color)
	{
		GravityVelocityVector = FVector::Zero;
	}

	TotalVelocityVector = FVector::Zero;
	TotalVelocityVector = TotalVelocityVector + GravityVelocityVector + HorizonVelocityVector;
	AddActorLocation(TotalVelocityVector * _DeltaTime);
}
