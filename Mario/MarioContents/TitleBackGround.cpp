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

	TitleBackGroundRenderer->SetImage("Mario_Title_Background_Fill.png");

	// 윈도우 사이즈 받아올 수 있도록 수정 필요
	TitleBackGroundRenderer->SetTransform({ { 128 * 3, 120 * 3 }, { 256 * 3,240 * 3 } });
}

void UTitleBackGround::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);


}