#include "BackGroundMap.h"
#include "EngineCore/EngineCore.h"
#include "EnumClass.h"

ABackGroundMap::ABackGroundMap()
{
}

ABackGroundMap::~ABackGroundMap()
{
}

void ABackGroundMap::BeginPlay()
{
	AActor::BeginPlay();

	BackGroundRenderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::BackGroundMap));
	
	//BackGroundRenderer->SetImage("1_1Stage_Map.png");
	//FVector ImageFVector = BackGroundRenderer->GetImage()->GetScale();

	//BackGroundRenderer->SetTransform({ { ImageFVector.ihX(), ImageFVector.ihY()}, {ImageFVector}});


}


void ABackGroundMap::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

}
