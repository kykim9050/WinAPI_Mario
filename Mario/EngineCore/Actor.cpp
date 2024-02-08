#include "Actor.h"
#include "ImageRenderer.h"

AActor::AActor()
{
}

AActor::~AActor()
{
	for (UImageRenderer* ImageRenderer : Renderers)
	{
		if (nullptr == ImageRenderer)
		{
			MsgBoxAssert("이미지 랜더러가 nullptr인 상황이 있었습니다");
		}

		delete ImageRenderer;
		ImageRenderer = nullptr;
	}

	Renderers.clear();
}

void AActor::Tick(float _DeltaTime)
{
	UTickObject::Tick(_DeltaTime);
}

UImageRenderer* AActor::CreateImageRenderer(int Order /*= 0*/)
{
	UImageRenderer* NewRenderer = new UImageRenderer();
	UActorComponent* ActorCom = NewRenderer;
	ActorCom->SetOwner(this);
	ActorCom->SetOrder(Order);
	ActorCom->BeginPlay();
	Renderers.push_back(NewRenderer);
	return NewRenderer;
}

void AActor::Destroy(float _DestroyTime /*= 0.0f*/)
{
	UTickObject::Destroy(_DestroyTime);

	for (UImageRenderer* Renderer : Renderers)
	{
		Renderer->Destroy(_DestroyTime);
	}
}

void AActor::DestroyUpdate(float _DeltaTime)
{
	UTickObject::DestroyUpdate(_DeltaTime);

	for (UImageRenderer* Renderer : Renderers)
	{
		Renderer->DestroyUpdate(_DeltaTime);
	}
}

void AActor::ActiveUpdate(float _DeltaTime)
{
	UTickObject::ActiveUpdate(_DeltaTime);

	for (UImageRenderer* Renderer : Renderers)
	{
		Renderer->ActiveUpdate(_DeltaTime);
	}
}