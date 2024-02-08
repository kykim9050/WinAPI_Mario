#include "ContentsCore.h"
#include "TitleLevel.h"
#include "1_1StageLevel.h"
#include "EndingLevel.h"
#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineFile.h>
#include <EngineCore/EngineResourcesManager.h>

// 윈도우 크기 배율
const int UContentsCore::WindowSizeMulValue = 3;

UContentsCore::UContentsCore()
	: UEngineCore()
{
}

UContentsCore::~UContentsCore()
{
}

// 프로그램 시작
void UContentsCore::BeginPlay()
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

	UEngineResourcesManager::GetInst().CuttingImage("TitleCoin.png", 6, 1);
	//UEngineResourcesManager::GetInst().CuttingImage("Mario_Ending_BackGround_Message.png", 1, 5);

	CreateLevel<UTitleLevel>("TitleLevel");
	CreateLevel<U1_1StageLevel>("1_1StageLevel");
	CreateLevel<UEndingLevel>("EndingLevel");

	ChangeLevel("TitleLevel");
}

void UContentsCore::Tick(float _DeltaTime)
{
	UEngineCore::Tick(_DeltaTime);

}

void UContentsCore::End()
{
	UEngineCore::End();
}