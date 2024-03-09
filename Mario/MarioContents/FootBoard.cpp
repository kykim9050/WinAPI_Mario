#include "FootBoard.h"

AFootBoard::AFootBoard()
{
}

AFootBoard::~AFootBoard()
{
}

void AFootBoard::BeginPlay()
{
	UStateUnit::BeginPlay();

	Renderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::BackGrundStructure));
	Renderer->SetImage("FootBoard.png");

	FVector FootBoardScale = Renderer->GetImage()->GetScale();

	Renderer->SetTransform({ {0,0}, {FootBoardScale.iX() * UInGameValue::WindowSizeMulValue, FootBoardScale.iY() * UInGameValue::WindowSizeMulValue} });


	BodyCollision = CreateCollision(ECollisionOrder::BlockTop);
	BodyCollision->SetTransform({ { 0,0 }, { FootBoardScale.iX() * UInGameValue::WindowSizeMulValue, FootBoardScale.iY() * UInGameValue::WindowSizeMulValue } });
	BodyCollision->SetColType(ECollisionType::Rect);

	StateChange(EActorState::Move);
}

void AFootBoard::Tick(float _DeltaTime)
{
	UStateUnit::Tick(_DeltaTime);
}

void AFootBoard::StateUpdate(float _DeltaTime)
{
	switch (ActorState)
	{
	case EActorState::Move:
		Move(_DeltaTime);
		break;
	default:
		break;
	}
}

void AFootBoard::StateChange(EActorState _ActorState)
{
	if (ActorState != _ActorState)
	{
		switch (_ActorState)
		{
		case EActorState::Move:
			MoveStart();
			break;
		default:
			break;
		}
	}

	SetActorState(_ActorState);
}

void AFootBoard::MoveStart()
{
	HorizonVelocityVector = ActorMoveDir * MoveSpeed;
}

void AFootBoard::Move(float _DeltaTime)
{
	CalTotalVelocityVector(_DeltaTime);
	AddActorLocation(TotalVelocityVector * _DeltaTime);

	if (GetActorLocation().iX() <= /*InitPos.iX()*/ /*- 200*/ 100)
	{
		ActorMoveDir = FVector::Right;
		HorizonVelocityVector = ActorMoveDir * MoveSpeed;
		AddActorLocation(FVector::Right * 1);
	}
	else if (GetActorLocation().iX() >= /*InitPos.iX()*/ + 500)
	{
		ActorMoveDir = FVector::Left;
		HorizonVelocityVector = ActorMoveDir * MoveSpeed;
		AddActorLocation(FVector::Left * 1);
	}
}
