#include "ImageRenderer.h"
#include "EngineCore.h"
#include "Actor.h"
#include "Level.h"
#include <EngineCore\EngineResourcesManager.h>

UImageRenderer::UImageRenderer()
{
}

UImageRenderer::~UImageRenderer()
{
}

void UImageRenderer::SetOrder(int _Order)
{
	AActor* Owner = GetOwner();
	ULevel* Level = Owner->GetWorld();

	std::map<int, std::list<UImageRenderer*>>& Renderers = Level->Renderers;

	Renderers[GetOrder()].remove(this);

	UTickObject::SetOrder(_Order);

	Renderers[GetOrder()].push_back(this);
}

void UImageRenderer::Render(float _DeltaTime)
{
	if (nullptr == Image)
	{
		MsgBoxAssert("이미지가 존재하지 않는 랜더러 입니다");
	}

	FTransform RendererTrans = GetTransform();

	FTransform ActorTrans = GetOwner()->GetTransform();

	RendererTrans.AddPosition(ActorTrans.GetPosition());

	GEngine->MainWindow.GetBackBufferImage()->TransCopy(Image, RendererTrans, InfoIndex);

}

void UImageRenderer::BeginPlay()
{
	USceneComponent::BeginPlay();
}

void UImageRenderer::SetImage(std::string_view _Name, int _InfoIndex)
{
	Image = UEngineResourcesManager::GetInst().FindImg(_Name);

	if (nullptr == Image)
	{
		MsgBoxAssert(std::string(_Name) + "이미지가 존재하지 않습니다.");
		return;
	}

	InfoIndex = _InfoIndex;
}