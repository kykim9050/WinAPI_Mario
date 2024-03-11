#include "ChangingLevel.h"
#include <EngineCore/EngineCore.h>
#include "TestLevel.h"
#include "PlayerInfoManager.h"
#include "1_1StageLevel.h"
#include "1_4StageLevel.h"

UChangingLevel::UChangingLevel()
{
}

UChangingLevel::~UChangingLevel()
{
}

void UChangingLevel::BeginPlay()
{
	ULevel::BeginPlay();
}

void UChangingLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	std::string LevelName = GetName();
	std::string UpperLevelName = UEngineString::ToUpper(LevelName);


	if ("PLAYERDEAD" == UpperLevelName)
	{
		if (0 == UPlayerInfoManager::GetInst().GetPlayerLife())
		{
			MsgBoxAssert("아직 목숨 0일때 그림이 없으니 일단 터뜨리기");
			return;
		}

		std::string StageLevel = UPlayerInfoManager::GetInst().GetPrevStageLevel();
		
		if ("1-1" == StageLevel)
		{
			GEngine->CreateLevel<U1_1StageLevel>("1-1");
			GEngine->ChangeLevel("1-1");
			return;
		}
		else if ("1-4" == StageLevel)
		{
			GEngine->CreateLevel<U1_4StageLevel>("1-4");
			GEngine->ChangeLevel("1-4");
			return;
		}
	}



}

void UChangingLevel::LevelStart(ULevel* _PrevLevel)
{
	ULevel::LevelStart(_PrevLevel);
}

void UChangingLevel::LevelEnd(ULevel* _NextLevel)
{
	ULevel::LevelEnd(_NextLevel);
	std::string LevelName = GetName();
	GEngine->DestroyLevel(LevelName);
}


