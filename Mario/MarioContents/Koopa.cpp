#include "Koopa.h"

AKoopa::AKoopa()
{
}

AKoopa::~AKoopa()
{
}

void AKoopa::BeginPlay()
{
	AMonsterUnit::BeginPlay();

	Renderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::Monster));
	Renderer->SetImage("Koopa_Left.png");
	FVector KoopaScale = Renderer->GetImage()->GetScale();
	Renderer->SetTransform({ {0,0}, {KoopaScale.iX() / UInGameValue::KoopaImgXValue * UInGameValue::WindowSizeMulValue, KoopaScale.iY() / UInGameValue::KoopaImgYValue * UInGameValue::WindowSizeMulValue} });
	Renderer->CreateAnimation("Koopa_LeftMove", "Koopa_Left.png", 0, 1, 0.3f, true);
	Renderer->CreateAnimation("Koopa_RightMove", "Koopa_Right.png", 0, 1, 0.3f, true);

	BodyCollision = CreateCollision(ECollisionOrder::Monster);
	BodyCollision->SetTransform({ { 0,0 }, { UInGameValue::KoopaBodyCollisionScaleX, UInGameValue::KoopaBodyCollisionScaleY} });
	BodyCollision->SetPosition({ 0, -(BodyCollision->GetTransform().GetScale().ihY()) });
	BodyCollision->SetColType(ECollisionType::Rect);

	SetActorState(EActorState::Idle);

}

void AKoopa::Tick(float _DeltaTime)
{
	AMonsterUnit::Tick(_DeltaTime);
}

void AKoopa::MoveStart()
{
	AMonsterUnit::MoveStart();

	Renderer->ChangeAnimation("Koopa_LeftMove");
}

void AKoopa::Move(float _DeltaTime)
{

	ResultMovementUpdate(_DeltaTime);
}

void AKoopa::Idle(float _DeltaTime)
{
	if (GetActorLocation().iX() - GetPlayer()->GetActorLocation().iX() < 100.0f)
	{
		StateChange(EActorState::Move);
	}
}

//void AKoopa::ResultMovementUpdate(float _DeltaTime)
//{
//	CalGravityVelocityVector(_DeltaTime);
//	CalTotalVelocityVector(_DeltaTime);
//	AddActorLocation(TotalVelocityVector * _DeltaTime);
//}

//void AKoopa::CalGravityVelocityVector(float _DeltaTime)
//{
//	std::vector<UCollision*> Result = std::vector<UCollision*>();
//	Color8Bit Color = UContentsFunction::GetCollisionMapImg()->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), UInGameValue::CollisionColor);
//
//	if (UInGameValue::CollisionColor == Color || true == BodyCollision->CollisionCheck(ECollisionOrder::BlockTop, Result))
//	{
//		GravityVelocityVector = FVector::Zero;
//		SetGravityRatio(0.0f);
//	}
//	else
//	{
//		SetGravityRatio(0.5f);
//	}
//
//	GravityVelocityVector += GravityAccVector * _DeltaTime * GravityRatio;
//}