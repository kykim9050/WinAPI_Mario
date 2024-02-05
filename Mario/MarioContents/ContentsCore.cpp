#include "ContentsCore.h"
#include "TitleLevel.h"
#include "PlayLevel.h"
#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineFile.h>
#include <EngineCore/EngineResourcesManager.h>

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

	// 윈도우 크기 배율
	int WindowSizeMulValue = 1;

	// 마리오용 윈도우 크기 설정
	MainWindow.SetWindowScale({ 256 * WindowSizeMulValue, 240 * WindowSizeMulValue });
	

	UEngineDirectory ResourcesDir = UEngineDirectory();
	ResourcesDir.MoveParent();
	ResourcesDir.Move("Resources");

	std::list<UEngineFile> ResourcesList = ResourcesDir.AllFile({ ".png", "bmp" }, true);

	for (UEngineFile& CurFIle : ResourcesList)
	{
		UEngineResourcesManager::GetInst().LoadImg(CurFIle.GetFullPath());
	}


	CreateLevel<UTitleLevel>("TitleLevel");
	//CreateLevel<UPlayLevel>("PlayLevel");

	ChangeLevel("TitleLevel");
}

void ContentsCore::Tick(float _DeltaTime)
{

}

void ContentsCore::End()
{
}