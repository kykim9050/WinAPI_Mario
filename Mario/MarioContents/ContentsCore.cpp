#include "ContentsCore.h"
#include "TitleLevel.h"
#include "PlayLevel.h"

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
	// 윈도우 크기 배율
	int WindowSizeMulValue = 3;

	// 마리오용 윈도우 크기 설정
	MainWindow.SetWindowScale({ 256 * WindowSizeMulValue, 240 * WindowSizeMulValue });
	
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