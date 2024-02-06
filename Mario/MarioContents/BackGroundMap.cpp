﻿#include "BackGroundMap.h"
#include "EngineCore/EngineCore.h"
#include "EnumClass.h"

ABackGroundMap::ABackGroundMap()
{
}

ABackGroundMap::~ABackGroundMap()
{
}

void ABackGroundMap::BeginPlay()
{
	AActor::BeginPlay();

	UImageRenderer* Stage1_1BackGroundRenderer = CreateImageRenderer(static_cast<int>(StageRenderOrder::BackGroundMap));

	Stage1_1BackGroundRenderer->SetImage("1_1StageBackGroundMap.png");

	// 이미지의 사이즈 받아올 수 있도록 클래스에 맴버 변수 선언, 그리고 상수 치환
	Stage1_1BackGroundRenderer->SetTransform({ { 5064, 720 }, { 10128, 1440 } });


}


void ABackGroundMap::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

}
