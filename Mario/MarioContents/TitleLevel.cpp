﻿#include "TitleLevel.h"
#include <EngineCore\EngineCore.h>
#include "TitleBackGround.h"
#include "TitleCoin.h"
#include "TestLevel.h"

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
}

void UTitleLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	if (UEngineInput::IsDown(VK_RETURN))
	{
		GEngine->CreateLevel<UTestLevel>("1-1");
		GEngine->ChangeLevel("1-1");
	}
}