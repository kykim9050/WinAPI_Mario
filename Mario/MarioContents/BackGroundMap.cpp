#include "BackGroundMap.h"
#include "EngineCore/EngineCore.h"


BackGroundMap::BackGroundMap()
{
}

BackGroundMap::~BackGroundMap()
{
}

void BackGroundMap::BeginPlay()
{
	AActor::BeginPlay();

	UImageRenderer* Stage1_1BackGroundRenderer = CreateImageRenderer();

	Stage1_1BackGroundRenderer->SetImage("1_1StageBackGroundMap.png");

	// 이미지의 사이즈 받아올 수 있도록 클래스에 맴버 변수 선언, 그리고 상수 치환
	Stage1_1BackGroundRenderer->SetTransform({ { 5064, 720 }, { 10128, 1440 } });


}


void BackGroundMap::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

}
