#include "Item.h"

AItem::AItem()
{
}

AItem::~AItem()
{
}

void AItem::BeginPlay()
{
	AActor::BeginPlay();
}

void AItem::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}