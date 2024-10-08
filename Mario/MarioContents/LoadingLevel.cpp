﻿#include "LoadingLevel.h"
#include <EngineCore/EngineCore.h>
#include "TestLevel.h"
#include "PlayerInfoManager.h"
#include "1_1StageLevel.h"
#include "1_4StageLevel.h"
#include "GameOverLevel.h"
#include "TimeUpLevel.h"
#include "TitleLevel.h"

ULoadingLevel::ULoadingLevel()
{
}

ULoadingLevel::~ULoadingLevel()
{
}

void ULoadingLevel::BeginPlay()
{
	ULevel::BeginPlay();
}

void ULoadingLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	std::string LevelName = GetName();
	std::string UpperLevelName = UEngineString::ToUpper(LevelName);


	if ("PLAYERDEAD" == UpperLevelName)
	{
		if (0 == UPlayerInfoManager::GetInst().GetPlayerLife())
		{
			GEngine->CreateLevel<UGameOverLevel>("GameOver");
			GEngine->ChangeLevel("GameOver");
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

	if ("NEXTLEVEL" == UpperLevelName)
	{
		std::string PrevStage = UPlayerInfoManager::GetInst().GetPrevStageLevel();

		if ("0-0" == PrevStage)
		{
			GEngine->CreateLevel<U1_1StageLevel>("1-1");
			GEngine->ChangeLevel("1-1");
			return;
		}

		if ("1-1" == PrevStage)
		{
			GEngine->CreateLevel<U1_4StageLevel>("1-4");
			GEngine->ChangeLevel("1-4");
			return;
		}

	}

	if ("TIMEUP" == UpperLevelName)
	{
		GEngine->CreateLevel<UTimeUpLevel>("TimeUpUI");
		GEngine->ChangeLevel("TimeUpUI");
		return;
	}

	if ("RESTART" == UpperLevelName)
	{
		UPlayerInfoManager::GetInst().ReSetInfo();
		GEngine->CreateLevel<UTitleLevel>("0-0");
		GEngine->ChangeLevel("0-0");
		return;
	}
}

void ULoadingLevel::LevelStart(ULevel* _PrevLevel)
{
	ULevel::LevelStart(_PrevLevel);
}

void ULoadingLevel::LevelEnd(ULevel* _NextLevel)
{
	ULevel::LevelEnd(_NextLevel);
	std::string LevelName = GetName();
	GEngine->DestroyLevel(LevelName);
}


