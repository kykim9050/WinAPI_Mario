#include "StateUnit.h"

UStateUnit::UStateUnit()
{
}

UStateUnit::~UStateUnit()
{
}

void UStateUnit::BeginPlay()
{
	AActor::BeginPlay();
}

void UStateUnit::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}

std::string UStateUnit::ChangeAnimationName(std::string _MainName)
{
	std::string Dir = "";
	CurAnimationName = _MainName;

	switch (ActorDir)
	{
	case EActorDir::Left:
		Dir = "_Left";
		break;
	case EActorDir::Right:
		Dir = "_Right";
		break;
	default:
		break;
	}

	return CurAnimationName + Dir;
}

void UStateUnit::CalGravityVelocityVector(float _DeltaTime)
{
	GravityVelocityVector += GravityAccVector * _DeltaTime;

	Color8Bit Color = UContentsFunction::GetCollisionMapImg()->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), UInGameValue::CollisionColor);

	if (UInGameValue::CollisionColor == Color)
	{
		GravityVelocityVector = FVector::Zero;
	}
}

void UStateUnit::CalTotalVelocityVector(float _DeltaTime)
{
	TotalVelocityVector = FVector::Zero;
	TotalVelocityVector = TotalVelocityVector + HorizonVelocityVector + GravityVelocityVector + JumpVelocityVector;
}