#include "BlockUnit.h"


ABlockUnit::ABlockUnit()
{
}

ABlockUnit::~ABlockUnit()
{
}

void ABlockUnit::BeginPlay()
{
	UStateUnit::BeginPlay();

	SideCollision = CreateCollision(ECollisionOrder::BlockSide);
	SideCollision->SetTransform({ { 0, 0 }, { UInGameValue::BlockCollisionScaleX, UInGameValue::BlockCollisionScaleY - 16} });
	SideCollision->SetColType(ECollisionType::Rect);

	TopCollision = CreateCollision(ECollisionOrder::BlockTop);
	TopCollision->SetTransform({ { ColInitXPos, -ColInitYPos -4 }, { UInGameValue::BlockCollisionScaleX - 24, UInGameValue::BlockCollisionScaleY - ColYoffset - 8 } });
	TopCollision->SetColType(ECollisionType::Rect);

	BodyCollision = CreateCollision(ECollisionOrder::BlockBot);
	BodyCollision->SetTransform({ { ColInitXPos, ColInitYPos }, { UInGameValue::BlockCollisionScaleX, UInGameValue::BlockCollisionScaleY - ColYoffset} });
	BodyCollision->SetColType(ECollisionType::Rect);
}

void ABlockUnit::Tick(float _DeltaTime)
{
	UStateUnit::Tick(_DeltaTime);
}


void ABlockUnit::CollisionStateChange(ECollisionState _CollisionState)
{
	if (ActorCollisionState != _CollisionState)
	{
		switch (_CollisionState)
		{
		case ECollisionState::GetHit:
			GetHitStart();
			break;
		default:
			break;
		}
	}

	SetCollisionState(_CollisionState);
}

void ABlockUnit::FirstInit(float _Deltatime)
{
	InitPos = GetActorLocation();
	StateChange(EActorState::Idle);
}

void ABlockUnit::ResultMovementUpdate(float _DeltaTime)
{
	GravityVelocityVector += GravityAccVector * _DeltaTime;
	CalTotalVelocityVector(_DeltaTime);
	AddActorLocation(TotalVelocityVector * _DeltaTime);
}

void ABlockUnit::StateUpdate(float _DeltaTime)
{
	switch (ActorState)
	{
	case EActorState::FirstInit:
		FirstInit(_DeltaTime);
		break;
	case EActorState::Idle:
		Idle(_DeltaTime);
		break;
	case EActorState::Move:
		Move(_DeltaTime);
		break;
	case EActorState::Fixed:
		Fixed(_DeltaTime);
		break;
	case EActorState::Debris:
		Debris(_DeltaTime);
		break;
	default:
		break;
	}
}

void ABlockUnit::StateChange(EActorState _ActorState)
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
		case EActorState::Fixed:
			FixedStart();
			break;
		case EActorState::Debris:
			DebrisStart();
			break;
		default:
			break;
		}
	}

	SetActorState(_ActorState);
}


void ABlockUnit::GetHitStart()
{
	if (EActorState::Fixed == ActorState)
	{
		return;
	}

	APlayerMario* Player = APlayerMario::GetMainPlayer();

	if (nullptr == Player)
	{
		MsgBoxAssert("플레이어가 존재하지 않습니다.");
	}

	EMarioType type = Player->GetPlayerType();


	switch (type)
	{
	case EMarioType::Small:
		StateChange(EActorState::Move);
		break;
	case EMarioType::Big:
		StateChange(EActorState::Debris);
		break;
	default:
		break;
	}

	
}

void ABlockUnit::MoveStart()
{
	JumpVelocityVector = FVector::Up * 200.0f;
}

void ABlockUnit::Idle(float _DeltaTime)
{

}

void ABlockUnit::Move(float _DeltaTime)
{
	ResultMovementUpdate(_DeltaTime);
}

void ABlockUnit::Fixed(float _DeltaTime)
{

}