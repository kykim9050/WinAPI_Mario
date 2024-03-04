#include "Castle.h"

ACastle::ACastle()
{
}

ACastle::~ACastle()
{
}

void ACastle::BeginPlay()
{
	AStructureUnit::BeginPlay();
}

void ACastle::Tick(float _DeltaTime)
{
	AStructureUnit::Tick(_DeltaTime);
}

void ACastle::CollisionCheck()
{
	AStructureUnit::CollisionCheck();
}
