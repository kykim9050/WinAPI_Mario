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

	JumpVelocityVector = MaxJumpVelocityVector;
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




// X축 이동만을 담당하는 함수
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

	ReverseMoveCheck();

	if (UEngineInput::IsPress(VK_LEFT))
	{
		AddHorizonVelocityVector(FVector::Left * _DeltaTime);
	}
	if (UEngineInput::IsPress(VK_RIGHT))
	{
		AddHorizonVelocityVector(FVector::Right * _DeltaTime);
	}


	ResultMovementUpdate(_DeltaTime);
}

void APlayerMario::Jump(float _DeltaTime)
{
	if (UEngineInput::IsPress(VK_LEFT))
	{
		AddHorizonVelocityVector(FVector::Left * _DeltaTime);
	}

	if (UEngineInput::IsPress(VK_RIGHT))
	{
		AddHorizonVelocityVector(FVector::Right * _DeltaTime);
	}

	ResultMovementUpdate(_DeltaTime);

	Color8Bit Color = UContentsFunction::GetCollisionMapImg()->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), UInGameValue::CollisionColor);

	if (UInGameValue::CollisionColor == Color)
	{
		JumpVelocityVector = FVector::Zero;
		if (true == UEngineInput::IsPress(VK_LEFT) || true == UEngineInput::IsPress(VK_RIGHT))
		{
			StateChange(EPlayerState::Move);
			return;
		}

		StateChange(EPlayerState::Idle);
		return;
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

	ResultMovementUpdate(_DeltaTime);
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






void APlayerMario::AddHorizonVelocityVector(const FVector& _DirDelta)
{
	HorizonVelocityVector += _DirDelta * HorizonAccVector;
}

void APlayerMario::ApplyMovement(float _DeltaTime)
{
	AddActorLocation(TotalVelocityVector * _DeltaTime);
	// 플레이어가 윈도우 화면 절반 지점에 왔을 때 카메라 이동
	CameraPosUpdate(GetActorLocation(), HorizonVelocityVector * _DeltaTime);
}

void APlayerMario::CalHorizonVelocityVector(float _DeltaTime)
{
	FVector CheckPos = GetActorLocation();
	CheckPos.Y -= UInGameValue::ColOffSetY;

	FVector BackPos = GetActorLocation();
	BackPos.Y -= UInGameValue::ColOffSetY;

	switch (MarioDir)
	{
	case EPlayerDir::Right:
		CheckPos.X += UInGameValue::ColOffSetX;
		BackPos.X -= UInGameValue::ColOffSetX;
		break;
	case EPlayerDir::Left:
		CheckPos.X -= UInGameValue::ColOffSetX;
		BackPos.X += UInGameValue::ColOffSetX;
		break;
	default:
		break;
	}

	Color8Bit Color = UContentsFunction::GetCollisionMapImg()->GetColor(CheckPos.iX(), CheckPos.iY(), UInGameValue::CollisionColor);
	Color8Bit PlayerBackColor = UContentsFunction::GetCollisionMapImg()->GetColor(BackPos.iX(), BackPos.iY(), UInGameValue::CollisionColor);

	if (Color == UInGameValue::CollisionColor)
	{
		HorizonVelocityVector = FVector::Zero;
	}

	if (PlayerBackColor == UInGameValue::CollisionColor)
	{
		switch (MarioDir)
		{
		case EPlayerDir::Right:
			HorizonVelocityVector = FVector::Right* _DeltaTime * HorizonAccVector;
			break;
		case EPlayerDir::Left:
			HorizonVelocityVector = FVector::Left * _DeltaTime * HorizonAccVector;
			break;
		default:
			break;
		}
	}


	if (true == UEngineInput::IsFree(VK_LEFT) && true == UEngineInput::IsFree(VK_RIGHT))
	{
		if (0.001 <= HorizonVelocityVector.Size2D())
		{
			HorizonVelocityVector += (-HorizonVelocityVector.Normalize2DReturn()) * _DeltaTime * HorizonAccVector;
		}
		else {
			HorizonVelocityVector = float4::Zero;
		}
	}

	if (HorizonMaxSpeed <= HorizonVelocityVector.Size2D())
	{
		HorizonVelocityVector = HorizonVelocityVector.Normalize2DReturn() * HorizonMaxSpeed;
	}
}

void APlayerMario::CalGravityVelocityVector(float _DeltaTime)
{
	GravityVelocityVector += GravityAccVector * _DeltaTime;

	Color8Bit Color = UContentsFunction::GetCollisionMapImg()->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), UInGameValue::CollisionColor);

	if (UInGameValue::CollisionColor == Color)
	{
		GravityVelocityVector = FVector::Zero;
	}
}

void APlayerMario::CalTotalVelocityVector(float _DeltaTime)
{
	TotalVelocityVector = FVector::Zero;
	TotalVelocityVector = TotalVelocityVector + HorizonVelocityVector + GravityVelocityVector + JumpVelocityVector;
}

void APlayerMario::CalJumpVelocityVector(float _DeltaTime)
{

}

void APlayerMario::ResultMovementUpdate(float _DeltaTime)
{
	CalHorizonVelocityVector(_DeltaTime);
	CalGravityVelocityVector(_DeltaTime);
	CalJumpVelocityVector(_DeltaTime);
	CalTotalVelocityVector(_DeltaTime);
	ApplyMovement(_DeltaTime);
}
