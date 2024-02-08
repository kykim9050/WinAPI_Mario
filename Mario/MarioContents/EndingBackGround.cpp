#include "EndingBackGround.h"
#include "EnginePlatform/WindowImage.h"
#include "EnumClass.h"

AEndingBackGround::AEndingBackGround()
{
}

AEndingBackGround::~AEndingBackGround()
{
}

void AEndingBackGround::BeginPlay()
{
	AActor::BeginPlay();

	UImageRenderer* Renderer = CreateImageRenderer(static_cast<int>(TitleRenderOrder::BackGroundMap));

	Renderer->SetImage("Mario_Ending_Background.png");
	FVector ImageScale = Renderer->GetImage()->GetScale();
	Renderer->SetTransform({ {ImageScale.ihX(), ImageScale.ihY()},{ImageScale}});
	
}

void AEndingBackGround::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}

