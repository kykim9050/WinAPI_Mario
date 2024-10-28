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

	// ������ ������ �޾ƿ� �� �ֵ��� ���� �ʿ�
	TitleBackGroundRenderer->SetTransform({ { 128 * ContentsCore::WindowSizeMulValue, 120 * ContentsCore::WindowSizeMulValue }, { 256 * ContentsCore::WindowSizeMulValue,240 * ContentsCore::WindowSizeMulValue } });
}

void ATitleBackGround::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

}