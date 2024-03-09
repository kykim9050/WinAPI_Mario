#include "FootBoard.h"
#include "PlayerMario.h"

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

	SetActorState(EActorState::Idle);
}

void AFootBoard::Tick(float _DeltaTime)
{
	UStateUnit::Tick(_DeltaTime);
}

void AFootBoard::StateUpdate(float _DeltaTime)
{
	switch (ActorState)
	{
	case EActorState::Idle:
		Idle(_DeltaTime);
		break;
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
		case EActorState::Idle:
			IdleStart();
			break;
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

void AFootBoard::Idle(float _DeltaTime)
{
	InitPos = GetActorLocation();
	if (GetActorLocation().iX() - GetPlayer()->GetActorLocation().iX() < UInGameValue::ResultMainWindowXScale)
	{
		StateChange(EActorState::Move);
	}
}

void AFootBoard::Move(float _DeltaTime)
{
	CalTotalVelocityVector(_DeltaTime);
	AddActorLocation(TotalVelocityVector * _DeltaTime);

	if (GetActorLocation().iX() <= InitPos.iX() - UInGameValue::MovingBoardDeadline_F)
	{
		ActorMoveDir = FVector::Right;
		HorizonVelocityVector = ActorMoveDir * MoveSpeed;
		AddActorLocation(FVector::Right * 1);
	}
	else if (GetActorLocation().iX() >= InitPos.iX() + UInGameValue::MovingBoardDeadline_R)
	{
		ActorMoveDir = FVector::Left;
		HorizonVelocityVector = ActorMoveDir * MoveSpeed;
		AddActorLocation(FVector::Left * 1);
	}
}
