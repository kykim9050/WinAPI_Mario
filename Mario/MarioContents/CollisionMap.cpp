#include "CollisionMap.h"
#include "EnumClass.h"

UImageRenderer* UCollisionMap::CollisionMapRenderer = nullptr;

UCollisionMap::UCollisionMap()
{
}

UCollisionMap::~UCollisionMap()
{
}

void UCollisionMap::BeginPlay()
{
	AActor::BeginPlay();

	CollisionMapRenderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::CollisionMap));
}

void UCollisionMap::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}
