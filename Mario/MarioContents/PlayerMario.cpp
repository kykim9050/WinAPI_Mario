#include "PlayerMario.h"
#include "EnumClass.h"
#include <EnginePlatform/EngineInput.h>
#include <EngineBase/EngineMath.h>
#include "InGameValue.h"
#include <EngineBase/EngineDebug.h>
#include "ContentsFunction.h"
#include <cmath>

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

	MarioRenderer->SetTransform({ {0,0}, {MarioScale.iX() / UInGameValue::MarioRightImageXValue * UInGameValue::WindowSizeMulValue, MarioScale.iY() / UInGameValue::MarioRightImageYValue * UInGameValue::WindowSizeMulValue} });

	MarioRenderer->CreateAnimation("Idle_Right", "Mario_Right.png", 0, 0, 0.1f, true);
	MarioRenderer->CreateAnimation("Idle_Left", "Mario_Left.png", 0, 0, 0.1f, true);

	MarioRenderer->CreateAnimation("Move_Right", "Mario_Right.png", 1, 3, 0.1f, true);
	MarioRenderer->CreateAnimation("Move_Left", "Mario_Left.png", 1, 3, 0.1f, true);

	MarioRenderer->CreateAnimation("Jump_Right", "Mario_Right.png", 5, 5, 0.1f, true);
	MarioRenderer->CreateAnimation("Jump_Left", "Mario_Left.png", 5, 5, 0.1f, true);



	MarioState = EPlayerState::Idle;
}

void APlayerMario::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
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
		case EPlayerState::FreeMove:
			FreeMoveStart();
			break;
		case EPlayerState::Jump:
			JumpStart();
			break;
		default:
			break;
		}
	}

	SetMarioState(_PlayerState);
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
	case EPlayerState::FreeMove:
		FreeMove(_DeltaTime);
		break;
	case EPlayerState::CameraMove:
		CameraMove(_DeltaTime);
		break;
	case EPlayerState::Jump:
		Jump(_DeltaTime);
		break;
	default:
		break;
	}
}



void APlayerMario::JumpStart()
{
	DirCheck();
	MarioRenderer->ChangeAnimation(ChangeAnimationName("Jump"));

	// 현재의 좌표 기준으로 최대 점프 높이를 계산해 놓는다.
	FVector CurPos = GetActorLocation();
	PJumpHeightLimit = CurPos.Y - UInGameValue::JumpLimitValue;
	JumpEnd = false;
}

void APlayerMario::FreeMoveStart()
{
	MarioRenderer->ChangeAnimation("Idle_Right");
}

void APlayerMario::IdleStart()
{
	DirCheck();
	MarioRenderer->ChangeAnimation(ChangeAnimationName("Idle"));
}

void APlayerMario::MoveStart()
{
	DirCheck();
	MarioRenderer->ChangeAnimation(ChangeAnimationName("Move"));
}





void APlayerMario::Move(float _DeltaTime)
{

	if ((UEngineInput::IsFree(VK_LEFT) && UEngineInput::IsFree(VK_RIGHT)))
	{
		StateChange(EPlayerState::Idle);
		return;
	}

	if (UEngineInput::IsDown('Z'))
	{
		StateChange(EPlayerState::Jump);
		return;
	}

	GravityCheck(_DeltaTime);

	ReverseMoveCheck();


	FVector MovePos = FVector::Zero;

	if (UEngineInput::IsPress(VK_LEFT))
	{
		Accel(_DeltaTime);
		MovePos += FVector::Left * PVelocity * _DeltaTime;
	}
	if (UEngineInput::IsPress(VK_RIGHT))
	{
		Accel(_DeltaTime);
		MovePos += FVector::Right * PVelocity * _DeltaTime;
	}

	// CollisionMap과 충돌을 예상할 수 있도록 기존 Actor의 좌표값에 Offset값을 추가 가공한 좌표를 반환
	FVector ComparePos = GetActorOffSetPos();

	Color8Bit ColMapColor = UContentsFunction::GetCollisionMapImg()->GetColor(ComparePos.iX(), ComparePos.iY(), UInGameValue::CollisionColor);

	if (UInGameValue::CollisionColor != ColMapColor)
	{
		AddActorLocation(MovePos);

		// 플레이어가 윈도우 화면 절반 지점에 왔을 때 카메라 이동
		CameraPosUpdate(GetActorLocation(), MovePos);

	}
}

void APlayerMario::Jump(float _DeltaTime)
{

	// 먼저 일정 높이 이상 떠오르고
	if (false == JumpEnd && GetActorLocation().iY() >= std::lround(PJumpHeightLimit))
	{
		AddActorLocation(FVector::Up * PJumpVelocity * _DeltaTime);
		return;
	}
	else
	{
		PJumpHeightLimit = 0.0f;
		JumpEnd = true;
	}

	// 일정 높이 됬을 때 중력에 영향 받을 수 있도록 GravityCheck
	if (GravityCheck(_DeltaTime))
	{
		if ((UEngineInput::IsFree(VK_LEFT) && UEngineInput::IsFree(VK_RIGHT)))
		{
			StateChange(EPlayerState::Idle);
			return;
		}

		if (UEngineInput::IsPress(VK_LEFT) || UEngineInput::IsPress(VK_RIGHT))
		{
			StateChange(EPlayerState::Move);
			return;
		}
	}
}

void APlayerMario::FreeMove(float _DeltaTime)
{
	if (UEngineInput::IsDown('1'))
	{
		StateChange(EPlayerState::Idle);
		return;
	}

	if (UEngineInput::IsPress(VK_LEFT))
	{
		AddActorLocation(FVector::Left * PFreeMoveVelocity * _DeltaTime);
		GetWorld()->AddCameraPos(FVector::Left * PFreeMoveVelocity * _DeltaTime);
	}

	if (UEngineInput::IsPress(VK_RIGHT))
	{
		AddActorLocation(FVector::Right * PFreeMoveVelocity * _DeltaTime);
		GetWorld()->AddCameraPos(FVector::Right * PFreeMoveVelocity * _DeltaTime);
	}

	if (UEngineInput::IsPress(VK_UP))
	{
		AddActorLocation(FVector::Up * PFreeMoveVelocity * _DeltaTime);
		GetWorld()->AddCameraPos(FVector::Up * PFreeMoveVelocity * _DeltaTime);
	}

	if (UEngineInput::IsPress(VK_DOWN))
	{
		AddActorLocation(FVector::Down * PFreeMoveVelocity * _DeltaTime);
		GetWorld()->AddCameraPos(FVector::Down * PFreeMoveVelocity * _DeltaTime);
	}
}

void APlayerMario::CameraMove(float _DeltaTime)
{
	if (UEngineInput::IsDown('2'))
	{
		StateChange(EPlayerState::Idle);
		return;
	}

	if (UEngineInput::IsPress(VK_LEFT))
	{
		GetWorld()->AddCameraPos(FVector::Left * PFreeMoveVelocity * _DeltaTime);
	}

	if (UEngineInput::IsPress(VK_RIGHT))
	{
		GetWorld()->AddCameraPos(FVector::Right * PFreeMoveVelocity * _DeltaTime);
	}

	if (UEngineInput::IsPress(VK_UP))
	{
		GetWorld()->AddCameraPos(FVector::Up * PFreeMoveVelocity * _DeltaTime);
	}

	if (UEngineInput::IsPress(VK_DOWN))
	{
		GetWorld()->AddCameraPos(FVector::Down * PFreeMoveVelocity * _DeltaTime);
	}
}

void APlayerMario::Idle(float _DeltaTime)
{
	GravityCheck(_DeltaTime);

	if (UEngineInput::IsDown('1'))
	{
		StateChange(EPlayerState::FreeMove);
		return;
	}

	if (UEngineInput::IsDown('2'))
	{
		StateChange(EPlayerState::CameraMove);
		return;
	}

	if (UEngineInput::IsDown('Z'))
	{
		StateChange(EPlayerState::Jump);
		return;
	}

	if (UEngineInput::IsPress(VK_LEFT) || UEngineInput::IsPress(VK_RIGHT))
	{
		StateChange(EPlayerState::Move);
		return;
	}

}



void APlayerMario::Accel(float _DeltaTime)
{
	if (PVelocity < PMaxVelocity)
	{
		PVelocity += PAcceleration * _DeltaTime;
	}
	else
	{
		PVelocity = PMaxVelocity;
	}

	EngineDebug::OutPutDebugText(std::to_string(PAcceleration));
	EngineDebug::OutPutDebugText(std::to_string(PVelocity));
}

void APlayerMario::DirCheck()
{
	EPlayerDir Dir = MarioDir;

	if (UEngineInput::IsPress(VK_LEFT))
	{
		Dir = EPlayerDir::Left;
	}
	else if (UEngineInput::IsPress(VK_RIGHT))
	{
		Dir = EPlayerDir::Right;
	}

	if (MarioDir != Dir)
	{
		SetMarioDir(Dir);
	}
}

bool APlayerMario::GravityCheck(float _DeltaTime)
{
	Color8Bit MapColor = UContentsFunction::GetCollisionMapImg()->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), UInGameValue::CollisionColor);

	if (UInGameValue::CollisionColor != MapColor)
	{
		AddActorLocation(FVector::Down * PGravity * _DeltaTime);
		return false;
	}

	return true;
}

void APlayerMario::ReverseMoveCheck()
{
	DirCheck();
	MarioRenderer->ChangeAnimation(ChangeAnimationName("Move"));
}


void APlayerMario::CameraPosUpdate(FVector _Player, FVector _MovePos)
{
	if (_Player.iX() >= UInGameValue::MainWindowXScale * UInGameValue::WindowSizeMulValue / 2)
	{
		GetWorld()->AddCameraPos(_MovePos);
	}
}

FVector APlayerMario::GetActorOffSetPos()
{
	FVector Pos = GetActorLocation();

	switch (MarioDir)
	{
	case EPlayerDir::Right:
		Pos.X += UInGameValue::ColOffSetX;
		break;
	case EPlayerDir::Left:
		Pos.X -= UInGameValue::ColOffSetX;
		break;
	default:
		break;
	}

	Pos.Y -= UInGameValue::ColOffSetY;

	return Pos;
}

std::string APlayerMario::ChangeAnimationName(std::string _MainName)
{
	std::string Dir = "";
	CurAnimationName = _MainName;

	switch (MarioDir)
	{
	case EPlayerDir::Left:
		Dir = "_Left";
		break;
	case EPlayerDir::Right:
		Dir = "_Right";
		break;
	default:
		break;
	}

	return CurAnimationName + Dir;
}