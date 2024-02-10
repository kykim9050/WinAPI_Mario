#include "PlayerMario.h"
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

	MarioRenderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::Mario));

	MarioRenderer->SetImage("Mario_Right.png");
	FVector MarioScale = MarioRenderer->GetImage()->GetScale();

	// 수정 필요 : 마리오 초기 위치
	MarioRenderer->SetTransform({ {140,624}, {MarioScale.iX() / UInGameValue::MarioRightImageXValue * UInGameValue::WindowSizeMulValue, MarioScale.iY() / UInGameValue::MarioRightImageYValue * UInGameValue::WindowSizeMulValue} });
	
	MarioRenderer->CreateAnimation("Idle_Right", "Mario_Right.png", 0, 0, 0.1f, true);
	MarioRenderer->CreateAnimation("Idle_Left", "Mario_Left.png", 0, 0, 0.1f, true);

	MarioRenderer->CreateAnimation("Move_Right", "Mario_Right.png", 1, 3, 0.1f, true);
	MarioRenderer->CreateAnimation("Move_Left", "Mario_Left.png", 1, 3, 0.1f, true);


	MarioState = EPlayerState::Idle;
}


void APlayerMario::StateChange(EPlayerState _PlayerState)
{
	if (MarioState != _PlayerState)
	{
		switch (_PlayerState)
		{
		case EPlayerState::Idle:
			IdleStart();
			break;
		case EPlayerState::Move:
			MoveStart();
			break;
		default:
			break;
		}
	}

	SetMarioState(_PlayerState);
}

//void APlayerMario::FreeMove(float _DeltaTime)
//{
//	if (UEngineInput::IsPress(VK_LEFT))
//	{
//		AddActorLocation(FVector::Left * PVelocity * _DeltaTime);
//		GetWorld()->AddCameraPos(FVector::Left * PVelocity * _DeltaTime);
//	}
//
//	if (UEngineInput::IsPress(VK_RIGHT))
//	{
//		AddActorLocation(FVector::Right * PVelocity * _DeltaTime);
//		GetWorld()->AddCameraPos(FVector::Right * PVelocity * _DeltaTime);
//	}
//
//	if (UEngineInput::IsPress(VK_UP))
//	{
//		AddActorLocation(FVector::Up * PVelocity * _DeltaTime);
//		GetWorld()->AddCameraPos(FVector::Up * PVelocity * _DeltaTime);
//	}
//
//	if (UEngineInput::IsPress(VK_DOWN))
//	{
//		AddActorLocation(FVector::Down * PVelocity * _DeltaTime);
//		GetWorld()->AddCameraPos(FVector::Down * PVelocity * _DeltaTime);
//	}
//}


void APlayerMario::Idle(float _DeltaTime)
{
	
	if (UEngineInput::IsPress(VK_LEFT) || UEngineInput::IsPress(VK_RIGHT))
	{
		StateChange(EPlayerState::Move);
		return;
	}

}

void APlayerMario::Move(float _DeltaTime)
{
	if ((UEngineInput::IsFree(VK_LEFT) && UEngineInput::IsFree(VK_RIGHT)))
	{
		StateChange(EPlayerState::Idle);
		return;
	}

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
	

}


void APlayerMario::IdleStart()
{
	if (EPlayerDir::Right == MarioDir)
	{
		MarioRenderer->ChangeAnimation("Idle_Right");
	}
}

void APlayerMario::MoveStart()
{
	if (EPlayerDir::Right == MarioDir)
	{
		MarioRenderer->ChangeAnimation("Move_Right");
	}
}


void APlayerMario::StateUpdate(float _DeltaTime)
{
	switch (MarioState)
	{
	case EPlayerState::Idle:
		Idle(_DeltaTime);
		break;
	case EPlayerState::Move:
		Move(_DeltaTime);
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