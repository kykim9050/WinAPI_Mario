#include "TitleLevel.h"
#include <EngineCore\EngineCore.h>
#include "TitleBackGround.h"
#include "TitleCoin.h"
#include "1_1StageLevel.h"
#include "LoadingLevel.h"
#include "Manual.h"

UTitleLevel::UTitleLevel()
{
}

UTitleLevel::~UTitleLevel()
{
}

void UTitleLevel::BeginPlay()
{
	ULevel::BeginPlay();

	ATitleBackGround* Background = SpawnActor< ATitleBackGround>(static_cast<int>(EActorType::Map));
	ATitleCoin* Coin = SpawnActor<ATitleCoin>(static_cast<int>(EActorType::Item));
	AManual* Manual = SpawnActor<AManual>(static_cast<int>(EActorType::Manual));
}

void UTitleLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	if (UEngineInput::IsDown(VK_RETURN))
	{
		std::string LevelName = GetName();
		GEngine->DestroyLevel(LevelName);
		UPlayerInfoManager::GetInst().SetPrevStageLevel(LevelName);
		GEngine->CreateLevel<ULoadingLevel>("NextLevel");
		GEngine->ChangeLevel("NextLevel");
	}
}