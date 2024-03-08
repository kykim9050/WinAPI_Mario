#include "BulletUnit.h"

ABulletUnit::ABulletUnit()
{
}

ABulletUnit::~ABulletUnit()
{
}

void ABulletUnit::BeginPlay()
{
	UStateUnit::BeginPlay();
}

void ABulletUnit::Tick(float _DeltaTime)
{
	UStateUnit::Tick(_DeltaTime);
}