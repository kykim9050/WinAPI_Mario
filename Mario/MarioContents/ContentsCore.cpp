#include "ContentsCore.h"
#include "TitleLevel.h"
#include "1_1StageLevel.h"
#include "EndingLevel.h"
#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineFile.h>
#include <EngineCore/EngineResourcesManager.h>
#include "InGameValue.h"




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
	MainWindow.SetWindowScale({ UInGameValue::MainWindowXScale * UInGameValue::WindowSizeMulValue, UInGameValue::MainWindowYScale * UInGameValue::WindowSizeMulValue });


	UEngineDirectory ResourcesDir = UEngineDirectory();
	ResourcesDir.MoveParent();
	ResourcesDir.Move("Resources");

	std::list<UEngineFile> ResourcesList = ResourcesDir.AllFile({ ".png" }, true);

	for (UEngineFile& CurFIle : ResourcesList)
	{
		UEngineResourcesManager::GetInst().LoadImg(CurFIle.GetFullPath());
	}

	UEngineResourcesManager::GetInst().CuttingImage("TitleCoin.png", UInGameValue::TitleCoinImgX, UInGameValue::TitleCoinImgY);
	UEngineResourcesManager::GetInst().CuttingImage("Mario_Right.png", UInGameValue::MarioRightImageXValue, UInGameValue::MarioRightImageYValue);
	UEngineResourcesManager::GetInst().CuttingImage("Mario_Left.png", UInGameValue::MarioLeftImageXValue, UInGameValue::MarioLeftImageYValue);


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