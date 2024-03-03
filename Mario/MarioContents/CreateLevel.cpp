#include "CreateLevel.h"

UCreateLevel::UCreateLevel()
{
}

UCreateLevel::~UCreateLevel()
{
}

void UCreateLevel::BeginPlay()
{
	UDebugLevel::BeginPlay();
}

void UCreateLevel::Tick(float _DeltaTime)
{
	UDebugLevel::Tick(_DeltaTime);
}


