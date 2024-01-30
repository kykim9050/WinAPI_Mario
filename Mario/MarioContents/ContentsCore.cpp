#include "ContentsCore.h"
#include "TitleLevel.h"

ContentsCore::ContentsCore()
	: EngineCore()
{
}

ContentsCore::~ContentsCore()
{
}

// 게임시작
void ContentsCore::BeginPlay()
{
	CreateLevel<UTitleLevel>("TitleLevel");

	ChangeLevel("TitleLevel");
}

void ContentsCore::Tick(float _DeltaTime)
{
	// 플레이어 움직여야 한다.
}

void ContentsCore::End()
{
}