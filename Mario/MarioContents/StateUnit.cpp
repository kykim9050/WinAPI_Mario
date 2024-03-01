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

	CollisionUpdate(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void UStateUnit::CollisionUpdate(float _DeltaTime)
{
	CollisionCheck();
}



void UStateUnit::CalTotalVelocityVector(float _DeltaTime)
{
	TotalVelocityVector = FVector::Zero;
	TotalVelocityVector = TotalVelocityVector + HorizonVelocityVector + GravityVelocityVector + JumpVelocityVector;
}