﻿#include "PlayerMario.h"
#include "EnumClass.h"
#include <EnginePlatform/EngineInput.h>
#include <EngineBase/EngineMath.h>
#include "InGameValue.h"

APlayerMario::APlayerMario()
{
}

APlayerMario::~APlayerMario()
{
}

void APlayerMario::BeginPlay()
{
	AActor::BeginPlay();

	UImageRenderer* MarioRenderer = CreateImageRenderer(static_cast<int>(StageRenderOrder::Mario));

	MarioRenderer->SetImage("Mario_Right.png");
	FVector MarioScale = MarioRenderer->GetImage()->GetScale();

	// 수정 필요 : 마리오 초기 위치
	MarioRenderer->SetTransform({ {140,624}, {MarioScale.iX() / UInGameValue::MarioRightImageXValue * UInGameValue::WindowSizeMulValue, MarioScale.iY() / UInGameValue::MarioRightImageYValue * UInGameValue::WindowSizeMulValue} });
	MarioRenderer->CreateAnimation("Idle", "Mario_Right.png", 0, 0, 0.1f, true);
	MarioRenderer->ChangeAnimation("Idle");

	MarioState = PlayerState::Idle;
}

void APlayerMario::FreeMove(float _DeltaTime)
{
	if (UEngineInput::IsPress(VK_LEFT))
	{
		AddActorLocation(FVector::Left * PVelocity * _DeltaTime);
		GetWorld()->AddCameraPos(FVector::Left * PVelocity * _DeltaTime);
	}

	if (UEngineInput::IsPress(VK_RIGHT))
	{
		AddActorLocation(FVector::Right * PVelocity * _DeltaTime);
		GetWorld()->AddCameraPos(FVector::Right * PVelocity * _DeltaTime);
	}

	if (UEngineInput::IsPress(VK_UP))
	{
		AddActorLocation(FVector::Up * PVelocity * _DeltaTime);
		GetWorld()->AddCameraPos(FVector::Up * PVelocity * _DeltaTime);
	}

	if (UEngineInput::IsPress(VK_DOWN))
	{
		AddActorLocation(FVector::Down * PVelocity * _DeltaTime);
		GetWorld()->AddCameraPos(FVector::Down * PVelocity * _DeltaTime);
	}
}

void APlayerMario::Idle(float _DeltaTime)
{

	if (UEngineInput::IsPress(VK_LEFT))
	{
		// Left Move
		// 애니메이션 변경 필요
	}

	if (UEngineInput::IsPress(VK_RIGHT))
	{
		// Right Move
		// 애니메이션 변경 필요
	}

}

void APlayerMario::StateUpdate(float _DeltaTime)
{
	switch (MarioState)
	{
	case PlayerState::FreeMove:
		break;
	case PlayerState::CameraMove:
		break;
	case PlayerState::Idle:
		Idle(_DeltaTime);
		break;
	case PlayerState::Move:
		break;
	case PlayerState::Jump:
		break;
	default:
		break;
	}
}

void APlayerMario::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}