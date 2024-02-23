#include "MonsterUnit.h"

UMonsterUnit::UMonsterUnit()
{
}

UMonsterUnit::~UMonsterUnit()
{
}

void UMonsterUnit::BeginPlay()
{
	UStateUnit::BeginPlay();
}

void UMonsterUnit::Tick(float _DeltaTime)
{
	UStateUnit::Tick(_DeltaTime);
}

void UMonsterUnit::CalHorizonVelocityVector(float _DeltaTime)
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