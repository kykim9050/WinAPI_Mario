#include "TitleBackGround.h"
#include "ContentsCore.h"
#include "EnumClass.h"

ATitleBackGround::ATitleBackGround()
{
}

ATitleBackGround::~ATitleBackGround()
{
}

void ATitleBackGround::BeginPlay()
{
	AActor::BeginPlay();

	UImageRenderer* TitleBackGroundRenderer = CreateImageRenderer(static_cast<int>(ETitleRenderOrder::BackGroundMap));

	TitleBackGroundRenderer->SetImage("Mario_Title_Background.png");

	FVector ImageFVector = TitleBackGroundRenderer->GetImage()->GetScale();
	
	TitleBackGroundRenderer->SetTransform({ { ImageFVector.ihX(), ImageFVector.ihY()}, { ImageFVector} });
}

void ATitleBackGround::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

}