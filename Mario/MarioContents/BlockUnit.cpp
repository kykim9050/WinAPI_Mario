#include "BlockUnit.h"
#include "Goomba.h"


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
	SideCollision->SetTransform({ { 0, 0 }, { UInGameValue::BlockCollisionScaleX, UInGameValue::BlockCollisionScaleY - 24} });
	SideCollision->SetColType(ECollisionType::Rect);

	TopCollision = CreateCollision(ECollisionOrder::BlockTop);
	TopCollision->SetTransform({ { ColInitXPos, -ColInitYPos -4 }, { UInGameValue::BlockCollisionScaleX - 24, UInGameValue::BlockCollisionScaleY - ColYoffset - 8 } });
	TopCollision->SetColType(ECollisionType::Rect);

	BodyCollision = CreateCollision(ECollisionOrder::BlockBot);
	BodyCollision->SetTransform({ { ColInitXPos, ColInitYPos +4 }, { UInGameValue::BlockCollisionScaleX, UInGameValue::BlockCollisionScaleY - ColYoffset} });
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
	case EActorState::Wait:
		Wait(_DeltaTime);
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
		case EActorState::Release:
			Destroy();
			break;
		default:
			break;
		}
	}

	SetActorState(_ActorState);
}


void ABlockUnit::MoveStart()
{
	OnTheBlockMonsterCheck();

	JumpVelocityVector = FVector::Up * 200.0f;
}

void ABlockUnit::Move(float _DeltaTime)
{
	ResultMovementUpdate(_DeltaTime);
}

void ABlockUnit::OnTheBlockMonsterCheck()
{
	std::vector<UCollision*> Result = std::vector<UCollision*>();

	if (true == TopCollision->CollisionCheck(ECollisionOrder::MonsterFootCollision, Result))
	{
		AGoomba* Monster = dynamic_cast<AGoomba*>(Result[0]->GetOwner());

		if (nullptr == Monster)
		{
			MsgBoxAssert("충돌 대상이 Monster가 아닙니다.");
			return;
		}

		Monster->SetBlockHit();
	}
}

bool ABlockUnit::PlayerSideColCheck()
{
	std::vector<UCollision*> Result = std::vector<UCollision*>();

	if (true == SideCollision->CollisionCheck(ECollisionOrder::Player, Result))
	{
		APlayerMario* Player = dynamic_cast<APlayerMario*>(Result[0]->GetOwner());

		if (nullptr == Player)
		{
			MsgBoxAssert("충돌 대상이 Player가 아닙니다.");
			return false;
		}

		float BlockXPos = GetActorLocation().X;
		float PlayerXPos = Player->GetActorLocation().X;

		if (PlayerXPos < BlockXPos)
		{
			Player->SetLeftSideBlockHit();
			return true;
		}
		else if (PlayerXPos > BlockXPos)
		{
			Player->SetRightSideBlockHit();
			return true;
		}
	}

	return false;
}