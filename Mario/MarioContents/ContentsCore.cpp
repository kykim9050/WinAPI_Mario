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
	// 마리오용 윈도우 크기 설정
	MainWindow.SetWindowScale({ 800, 600 });
	
	CreateLevel<UTitleLevel>("TitleLevel");
	CreateLevel<UPlayLevel>("PlayLevel");

	ChangeLevel("PlayLevel");
}

void ContentsCore::Tick(float _DeltaTime)
{

}

void ContentsCore::End()
{
}