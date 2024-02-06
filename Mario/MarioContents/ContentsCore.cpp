#include "ContentsCore.h"
#include "TitleLevel.h"
#include "1_1StageLevel.h"
#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineFile.h>
#include <EngineCore/EngineResourcesManager.h>

// 윈도우 크기 배율
const int ContentsCore::WindowSizeMulValue = 3;

ContentsCore::ContentsCore()
	: UEngineCore()
{
}

ContentsCore::~ContentsCore()
{
}

// 프로그램 시작
void ContentsCore::BeginPlay()
{
	UEngineCore::BeginPlay();


	// 마리오용 윈도우 크기 설정
	MainWindow.SetWindowScale({ 256 * WindowSizeMulValue, 240 * WindowSizeMulValue });


	UEngineDirectory ResourcesDir = UEngineDirectory();
	ResourcesDir.MoveParent();
	ResourcesDir.Move("Resources");

	std::list<UEngineFile> ResourcesList = ResourcesDir.AllFile({ ".png" }, true);

	for (UEngineFile& CurFIle : ResourcesList)
	{
		UEngineResourcesManager::GetInst().LoadImg(CurFIle.GetFullPath());
	}

	UEngineResourcesManager::GetInst().CuttingImage("TitleCoin.png", 5, 1);

	CreateLevel<UTitleLevel>("TitleLevel");
	CreateLevel<U1_1StageLevel>("1_1StageLevel");

	ChangeLevel("TitleLevel");
}

void ContentsCore::Tick(float _DeltaTime)
{

}

void ContentsCore::End()
{
}