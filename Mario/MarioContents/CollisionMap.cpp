#include "CollisionMap.h"
#include "EnumClass.h"

UCollisionMap::UCollisionMap()
{
}

UCollisionMap::~UCollisionMap()
{
}

void UCollisionMap::BeginPlay()
{
	AActor::BeginPlay();

	UImageRenderer* Stage1_1CollisionMapRenderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::CollisionMap));


	Stage1_1CollisionMapRenderer->SetImage("1_1Stage_CollisionMap.png");
	FVector ImageFVector = Stage1_1CollisionMapRenderer->GetImage()->GetScale();

	// 이미지의 사이즈 받아올 수 있도록 클래스에 맴버 변수 선언, 그리고 상수 치환
	Stage1_1CollisionMapRenderer->SetTransform({ { ImageFVector.ihX(), ImageFVector.ihY()}, {ImageFVector} });
}

void UCollisionMap::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}
