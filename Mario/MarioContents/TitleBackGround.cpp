#include "TitleBackGround.h"

UTitleBackGround::UTitleBackGround()
{
}

UTitleBackGround::~UTitleBackGround()
{
}

void UTitleBackGround::BeginPlay()
{
	AActor::BeginPlay();

	UImageRenderer* TitleBackGroundRenderer = CreateImageRenderer();

	TitleBackGroundRenderer->SetImage("Mario_Title_Background.png");
	TitleBackGroundRenderer->SetPosition({ 128,120 });
	TitleBackGroundRenderer->SetScale({ 256,240 });
}

void UTitleBackGround::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);


}