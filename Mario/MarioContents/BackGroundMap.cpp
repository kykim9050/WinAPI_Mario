#include "BackGroundMap.h"


ABackGroundMap::ABackGroundMap()
{
}

ABackGroundMap::~ABackGroundMap()
{
}

void ABackGroundMap::BeginPlay()
{
	AActor::BeginPlay();

	BackGroundMapRenderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::BackGroundMap));
}


void ABackGroundMap::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

}
