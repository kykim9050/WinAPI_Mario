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

	UImageRenderer* TitleBackGroundRenderer = CreateImageRenderer(static_cast<int>(TitleRenderOrder::BackGroundMap));

	TitleBackGroundRenderer->SetImage("Mario_Title_Background.png");

	// ������ ������ �޾ƿ� �� �ֵ��� ���� �ʿ�
	TitleBackGroundRenderer->SetTransform({ { 128 * 3, 120 * 3}, { 256 * 3,240 * 3} });
}

void ATitleBackGround::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

}