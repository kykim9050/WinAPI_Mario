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