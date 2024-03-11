#include "RotatingFire.h"

ARotatingFire::ARotatingFire()
{
}

ARotatingFire::~ARotatingFire()
{
}

void ARotatingFire::BeginPlay()
{
	AMovingObjectUnit::BeginPlay();
}

void ARotatingFire::Tick(float _DeltaTime)
{
	AMovingObjectUnit::Tick(_DeltaTime);
}
