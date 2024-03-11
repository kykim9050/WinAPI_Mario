﻿#include "RotatingFire.h"
#include "PlayerMario.h"


void ARotatingFire::AFireObstacle::CreateFireObstacle()
{
	ObstacleRenderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::AttackableTrap));
	ObstacleRenderer->SetImage("FireBall.png");

	FVector FireObstacleScale = ObstacleRenderer->GetImage()->GetScale();

	ObstacleRenderer->SetTransform({ {0,0}, {FireObstacleScale.iX() / UInGameValue::FireBallImageXValue * UInGameValue::WindowSizeMulValue, FireObstacleScale.iY() / UInGameValue::FireBallImageYValue * UInGameValue::WindowSizeMulValue} });
	ObstacleRenderer->CreateAnimation("Fire_Rotating", "FireBall.png", 0, 3, 0.3f, true);
	ObstacleRenderer->ChangeAnimation("Fire_Rotating");

	ObstacleCol = CreateCollision(ECollisionOrder::AttackableTrap);
	ObstacleCol->SetTransform({ {0,0}, {UInGameValue::FireBallDia, UInGameValue::FireBallDia} });
	ObstacleCol->SetColType(ECollisionType::CirCle);
}

ARotatingFire::ARotatingFire()
{
}

ARotatingFire::~ARotatingFire()
{
}

void ARotatingFire::BeginPlay()
{
	AMovingObjectUnit::BeginPlay();

	for (int i = 0; i < ObstacleNum; i++)
	{
		AFireObstacle* obstacle = GetWorld()->SpawnActor<AFireObstacle>(static_cast<int>(EActorType::AttackableTrap));
		obstacle->CreateFireObstacle();
		RotatingFire.push_back(obstacle);
	}

	SetActorState(EActorState::FirstInit);
}

void ARotatingFire::Tick(float _DeltaTime)
{
	AMovingObjectUnit::Tick(_DeltaTime);
}

void ARotatingFire::FirstInit()
{
	InitPos = GetActorLocation();

	for (int i = 0; i < ObstacleNum; i++)
	{
		RotatingFire[i]->SetActorLocation({ InitPos.iX() , InitPos.iY() + UInGameValue::FireBallDia * i});
	}

	StateChange(EActorState::Idle);
}

void ARotatingFire::Idle(float _DeltaTime)
{
	if (GetActorLocation().iX() - GetPlayer()->GetActorLocation().iX() < UInGameValue::ResultMainWindowXScale)
	{
		StateChange(EActorState::Rotating);
	}
}

void ARotatingFire::Rotating(float _DeltaTime)
{
	int a = 0;
}
