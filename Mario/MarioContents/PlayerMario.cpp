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

	MarioRenderer = CreateImageRenderer(static_cast<int>(StageRenderOrder::Mario));

	MarioRenderer->SetImage("Mario_Right.png");
	FVector MarioScale = MarioRenderer->GetImage()->GetScale();

	// 수정 필요 : 마리오 초기 위치
	MarioRenderer->SetTransform({ {140,624}, {MarioScale.iX() / UInGameValue::MarioRightImageXValue * UInGameValue::WindowSizeMulValue, MarioScale.iY() / UInGameValue::MarioRightImageYValue * UInGameValue::WindowSizeMulValue} });
	
	MarioRenderer->CreateAnimation("Idle_Right", "Mario_Right.png", 0, 0, 0.1f, true);
	MarioRenderer->CreateAnimation("Idle_Left", "Mario_Left.png", 0, 0, 0.1f, true);

	MarioRenderer->CreateAnimation("Move_Right", "Mario_Right.png", 1, 3, 0.1f, true);
	MarioRenderer->CreateAnimation("Move_Left", "Mario_Left.png", 1, 3, 0.1f, true);


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
	if (EPlayerDir::Right == MarioDir)
	{
		MarioRenderer->ChangeAnimation("Idle_Right");
	}

	if (EPlayerDir::Left == MarioDir)
	{
		MarioRenderer->ChangeAnimation("Idle_Left");
	}



	if (UEngineInput::IsPress(VK_LEFT))
	{
		SetMarioDir(EPlayerDir::Left);
		Move(_DeltaTime);
		// Left Move
		// 애니메이션 변경 필요
	}
	if (UEngineInput::IsPress(VK_RIGHT))
	{
		SetMarioDir(EPlayerDir::Right);
		Move(_DeltaTime);
		// Right Move
		// 애니메이션 변경 필요
	}

}

void APlayerMario::Move(float _DeltaTime)
{
	// 수정 필요 : 캐릭터 방향 호출하는거 따로 함수로 만들고
	// 수정 필요 : 애니메이션 지정하는건 Move가 할일이 아니다. (따로 애니메이션을 지정해주는 함수를 만들어서 호출할 것 (FSM)
	if (EPlayerDir::Right == MarioDir)
	{
		MarioRenderer->ChangeAnimation("Move_Right");
	}

	if (EPlayerDir::Left == MarioDir)
	{
		MarioRenderer->ChangeAnimation("Move_Left");
	}



	if (UEngineInput::IsPress(VK_LEFT))
	{
		SetMarioDir(EPlayerDir::Left);
		AddActorLocation(FVector::Left * PVelocity * _DeltaTime);
		GetWorld()->AddCameraPos(FVector::Left * PVelocity * _DeltaTime);
	}
	if (UEngineInput::IsPress(VK_RIGHT))
	{
		SetMarioDir(EPlayerDir::Right);
		AddActorLocation(FVector::Right * PVelocity * _DeltaTime);
		GetWorld()->AddCameraPos(FVector::Right * PVelocity * _DeltaTime);
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
		Move(_DeltaTime);
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