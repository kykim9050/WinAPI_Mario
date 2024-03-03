#include "StructureUnit.h"

AStructureUnit::AStructureUnit()
{
}

AStructureUnit::~AStructureUnit()
{
}

void AStructureUnit::BeginPlay()
{
	UStateUnit::BeginPlay();
}

void AStructureUnit::Tick(float _DeltaTime)
{
	UStateUnit::Tick(_DeltaTime);

	CollisionCheck();
}