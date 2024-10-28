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

	//// �̹����� ������ �޾ƿ� �� �ֵ��� Ŭ������ �ɹ� ���� ����, �׸��� ��� ġȯ
	//CollisionMapRenderer->SetTransform({ { ImageFVector.ihX(), ImageFVector.ihY()}, {ImageFVector} });
}

void UCollisionMap::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}
