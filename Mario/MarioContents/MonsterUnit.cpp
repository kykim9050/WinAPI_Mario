#include "MonsterUnit.h"

AMonsterUnit::AMonsterUnit()
{
}

AMonsterUnit::~AMonsterUnit()
{
}

void AMonsterUnit::BeginPlay()
{
	UStateUnit::BeginPlay();
}

void AMonsterUnit::Tick(float _DeltaTime)
{
	UStateUnit::Tick(_DeltaTime);

	//StateUpdate(_DeltaTime);

	//CollisionUpdate(_DeltaTime);
}

void AMonsterUnit::CalHorizonVelocityVector(float _DeltaTime)
{
	FVector CheckPos = GetActorLocation();
	CheckPos.Y -= UInGameValue::ColOffSetY;

	switch (ActorDir)
	{
	case EActorDir::Right:
		CheckPos.X += UInGameValue::ColOffSetX;
		break;
	case EActorDir::Left:
		CheckPos.X -= UInGameValue::ColOffSetX;
		break;
	default:
		break;
	}

	Color8Bit Color = UContentsFunction::GetCollisionMapImg()->GetColor(CheckPos.iX(), CheckPos.iY(), UInGameValue::CollisionColor);

	if (Color == UInGameValue::CollisionColor)
	{
		switch (ActorDir)
		{
		case EActorDir::Right:
		{
			ActorDir = EActorDir::Left;
			ActorMoveDir = FVector::Left;
			break;
		}
		case EActorDir::Left:
		{
			ActorDir = EActorDir::Right;
			ActorMoveDir = FVector::Right;
			break;
		}
		default:
			break;
		}
	}
}

void AMonsterUnit::StateUpdate(float _DeltaTime)
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
	case EActorState::GetFirstHit:
		GetFirstHit(_DeltaTime);
		break;
	case EActorState::GetSecondHit:
		GetSecondHit(_DeltaTime);
		break;
	case EActorState::GetMonsterHit:
		GetMonsterHit(_DeltaTime);
		break;
	case EActorState::GetHit:
	default:
		break;
	}

}