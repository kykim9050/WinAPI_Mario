﻿#include "Castle.h"

ACastle::ACastle()
{
}

ACastle::~ACastle()
{
}

void ACastle::BeginPlay()
{
	AStructureUnit::BeginPlay();

	Renderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::BackGrundStructure));
	Renderer->SetImage("MiniCastle.png");

	FVector CastleScale = Renderer->GetImage()->GetScale();

	Renderer->SetTransform({ {0,0}, {CastleScale.iX() * UInGameValue::WindowSizeMulValue, CastleScale.iY() * UInGameValue::WindowSizeMulValue} });

	BodyCollision = CreateCollision(ECollisionOrder::CastleGate);
	BodyCollision->SetTransform({ { 24,0 }, { UInGameValue::CastleGateCollisionXScale, UInGameValue::CastleGateCollisionYScale} });
	BodyCollision->SetColType(ECollisionType::Rect);
}

void ACastle::Tick(float _DeltaTime)
{
	AStructureUnit::Tick(_DeltaTime);
}

void ACastle::CollisionCheck()
{
	AStructureUnit::CollisionCheck();
}