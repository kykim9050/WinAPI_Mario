#include "TitleBackGround.h"
#include "ContentsCore.h"

ATitleBackGround::ATitleBackGround()
{
}

ATitleBackGround::~ATitleBackGround()
{
}

void ATitleBackGround::BeginPlay()
{
	AActor::BeginPlay();

	UImageRenderer* TitleBackGroundRenderer = CreateImageRenderer();

	TitleBackGroundRenderer->SetImage("Mario_Title_Background.png");

	// 윈도우 사이즈 받아올 수 있도록 수정 필요
	TitleBackGroundRenderer->SetTransform({ { 128 * ContentsCore::WindowSizeMulValue, 120 * ContentsCore::WindowSizeMulValue }, { 256 * ContentsCore::WindowSizeMulValue,240 * ContentsCore::WindowSizeMulValue } });
}

void ATitleBackGround::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

}