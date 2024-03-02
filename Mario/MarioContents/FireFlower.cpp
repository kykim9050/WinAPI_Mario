#include "FireFlower.h"

AFireFlower::AFireFlower()
{
}

AFireFlower::~AFireFlower()
{
}

void AFireFlower::BeginPlay()
{
	AItemUnit::BeginPlay();
}

void AFireFlower::Tick(float _DeltaTime)
{
	AItemUnit::Tick(_DeltaTime);
}
