#include "TitleLevel.h"
#include <EngineCore\EngineCore.h>
#include "TitleBackGround.h"
#include "TitleCoin.h"

UTitleLevel::UTitleLevel()
{
}

UTitleLevel::~UTitleLevel()
{
}

void UTitleLevel::BeginPlay()
{
	ULevel::BeginPlay();

	ATitleBackGround* Background = SpawnActor< ATitleBackGround>();
	ATitleCoin* Coin = SpawnActor<ATitleCoin>();
}

void UTitleLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	if (EngineInput::IsDown(VK_RETURN))
	{
		GEngine->ChangeLevel("1_1StageLevel");
	}

	if (EngineInput::IsDown(VK_SPACE))
	{
		GEngine->ChangeLevel("EndingLevel");
	}
}