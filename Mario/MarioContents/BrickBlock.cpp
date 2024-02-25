#include "BrickBlock.h"

ABrickBlock::ABrickBlock()
{
}

ABrickBlock::~ABrickBlock()
{
}

void ABrickBlock::BeginPlay()
{
	ABlockUnit::BeginPlay();
}

void ABrickBlock::Tick(float _DeltaTime)
{
	ABlockUnit::Tick(_DeltaTime);
}