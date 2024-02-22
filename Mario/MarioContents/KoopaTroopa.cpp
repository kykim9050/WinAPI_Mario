#include "KoopaTroopa.h"

AKoopaTroopa::AKoopaTroopa()
{
}

AKoopaTroopa::~AKoopaTroopa()
{
}

void AKoopaTroopa::BeginPlay()
{
	UStateUnit::BeginPlay();

	Renderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::Monster));
	Renderer->SetImage("KoopaTroopa_Left.png");

	FVector KoopaTroopaScale = Renderer->GetImage()->GetScale();

	Renderer->SetTransform({ {0,0}, {KoopaTroopaScale.iX() / UInGameValue::KoopaTroopaImageXValue * UInGameValue::WindowSizeMulValue, KoopaTroopaScale.iY() / UInGameValue::KoopaTroopaImageYValue * UInGameValue::WindowSizeMulValue} });
	Renderer->CreateAnimation("KoopaTroopa_Right_Move", "KoopaTroopa_Right.png", 0, 1, 0.3f, true);
	Renderer->CreateAnimation("KoopaTroopa_Left_Move", "KoopaTroopa_Left.png", 0, 1, 0.3f, true);
	Renderer->CreateAnimation("KoopaTroopa_OneHit", "KoopaTroopa_Left.png", 5, 5, 0.1f, true);
	Renderer->CreateAnimation("KoopaTroopa_TwoHit", "KoopaTroopa_Left.png", 4, 4, 0.1f, true);

	Renderer->ChangeAnimation("KoopaTroopa_Left_Move");


	BodyCollision = CreateCollision(ECollisionOrder::Monster);
	BodyCollision->SetTransform({ { 0,0 }, { UInGameValue::KoopaTroopaBodyCollisionScaleX, UInGameValue::KoopaTroopaBodyCollisionScaleY} });
	BodyCollision->SetPosition({ 0, -(BodyCollision->GetTransform().GetScale().ihY()) });
	BodyCollision->SetColType(ECollisionType::Rect);


	GravityVelocityVector = FVector::Down * 500.0f;
	HorizonVelocityVector = FVector::Left * 50.0f;

	SetActorState(EActorState::Move);
}

void AKoopaTroopa::Tick(float _DeltaTime)
{
	UStateUnit::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void AKoopaTroopa::StateUpdate(float _DeltaTime)
{
	switch (ActorState)
	{
		/*case EPlayerState::Idle:
			Idle(_DeltaTime);
			break;*/
	case EActorState::Move:
		Move(_DeltaTime);
		break;
	default:
		break;
	}

}

void AKoopaTroopa::Move(float _DeltaTime)
{
	ResultMovementUpdate(_DeltaTime);
}

void AKoopaTroopa::ResultMovementUpdate(float _DeltaTime)
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

