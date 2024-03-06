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

	//CollisionMapRenderer->SetImage("1_1Stage_CollisionMap.png");
	//FVector ImageFVector = CollisionMapRenderer->GetImage()->GetScale();

	//// 이미지의 사이즈 받아올 수 있도록 클래스에 맴버 변수 선언, 그리고 상수 치환
	//CollisionMapRenderer->SetTransform({ { ImageFVector.ihX(), ImageFVector.ihY()}, {ImageFVector} });
}

void UCollisionMap::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}
