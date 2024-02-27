﻿#include "PlayerMario.h"
#include <EnginePlatform/EngineInput.h>
#include <EngineBase/EngineMath.h>
#include <EngineBase/EngineDebug.h>
#include <cmath>

APlayerMario* APlayerMario::MainPlayer = nullptr;

APlayerMario::APlayerMario()
{
	ActorDir = EActorDir::Right;
	Life = 3;
}

APlayerMario::~APlayerMario()
{
}

void APlayerMario::BeginPlay()
{
	UStateUnit::BeginPlay();

	SetMainPlayer(this);

	Renderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::Mario));

	Renderer->SetImage("Mario_Right.png");
	FVector MarioScale = Renderer->GetImage()->GetScale();

	Renderer->SetTransform({ {0,0}, {MarioScale.iX() / UInGameValue::MarioRightImageXValue * UInGameValue::WindowSizeMulValue, MarioScale.iY() / UInGameValue::MarioRightImageYValue * UInGameValue::WindowSizeMulValue} });

	Renderer->CreateAnimation("Idle_Right", "Mario_Right.png", 0, 0, 0.1f, true);
	Renderer->CreateAnimation("Idle_Left", "Mario_Left.png", 0, 0, 0.1f, true);

	Renderer->CreateAnimation("Move_Right", "Mario_Right.png", 1, 3, 0.1f, true);
	Renderer->CreateAnimation("Move_Left", "Mario_Left.png", 1, 3, 0.1f, true);

	Renderer->CreateAnimation("Jump_Right", "Mario_Right.png", 5, 5, 0.1f, true);
	Renderer->CreateAnimation("Jump_Left", "Mario_Left.png", 5, 5, 0.1f, true);

	Renderer->CreateAnimation("ReverseMove_Right", "Mario_Right.png", 4, 4, 0.1f, true);
	Renderer->CreateAnimation("ReverseMove_Left", "Mario_Left.png", 4, 4, 0.1f, true);

	Renderer->CreateAnimation("Dead", "Mario_Right.png", 6, 6, 0.1f, true);

	BodyCollision = CreateCollision(ECollisionOrder::Player);
	BodyCollision->SetScale({ UInGameValue::PlayerCollisionScaleX, UInGameValue::PlayerCollisionScaleY });
	BodyCollision->SetPosition({0, -(BodyCollision->GetTransform().GetScale().ihY())});
	BodyCollision->SetColType(ECollisionType::Rect);

	ActorState = EActorState::Idle;
}

void APlayerMario::Tick(float _DeltaTime)
{
	UStateUnit::Tick(_DeltaTime);
}


void APlayerMario::StateChange(EActorState _PlayerState)
{
	if (ActorState != _PlayerState)
	{
		switch (_PlayerState)
		{
		case EActorState::Idle:
			IdleStart();
			break;
		case EActorState::Move:
			MoveStart();
			break;
		case EActorState::FreeMove:
			FreeMoveStart();
			break;
		case EActorState::Jump:
			JumpStart();
			break;
		case EActorState::ReverseMove:
			ReverseMoveStart();
			break;
		case EActorState::CollisionJump:
			CollisionJumpStart();
			break;
		case EActorState::GetHit:
			GetHitStart();
			break;
		default:
			break;
		}
	}

	SetActorState(_PlayerState);
}

void APlayerMario::CollisionStateChange(ECollisionState _CollisionState)
{
	if (ActorCollisionState != _CollisionState)
	{
		switch (_CollisionState)
		{
		case ECollisionState::Hit:
			//HitStart();
			break;
		case ECollisionState::GetHit:
			GetHitStart();
			break;
		default:
			break;
		}
	}

	SetCollisionState(_CollisionState);
}

void APlayerMario::StateUpdate(float _DeltaTime)
{
	switch (ActorState)
	{
	case EActorState::Idle:
		Idle(_DeltaTime);
		break;
	case EActorState::Move:
		Move(_DeltaTime);
		break;
	case EActorState::FreeMove:
		FreeMove(_DeltaTime);
		break;
	case EActorState::CameraMove:
		CameraMove(_DeltaTime);
		break;
	case EActorState::Jump:
		Jump(_DeltaTime);
		break;
	case EActorState::ReverseMove:
		ReverseMove(_DeltaTime);
		break;
	case EActorState::CollisionJump:
		CollisionJump(_DeltaTime);
		break;
	case EActorState::GetHit:
		GetHit(_DeltaTime);
		break;
	default:
		break;
	}
}

void APlayerMario::CollisionUpdate(float _DeltaTime)
{
	switch (ActorCollisionState)
	{
	case ECollisionState::Hit:
		//EngineDebug::OutPutDebugText("Mario Hit");
		break;
	case ECollisionState::GetHit:
		GetHit(_DeltaTime);
		break;
	default:
		break;
	}
}

void APlayerMario::CollisionJumpStart()
{
	if (EActorDir::Left == ActorDir)
	{
		Renderer->ChangeAnimation("Jump_Left");
	}
	else if (EActorDir::Right == ActorDir)
	{
		Renderer->ChangeAnimation("Jump_Right");
	}

	SetGravityZero();
	JumpVelocityVector = CollisionJumpVelocityVector;
}

void APlayerMario::JumpStart()
{
	SetGravityRatio(0.5f);
	//EngineDebug::OutPutDebugText("JumpStart");
	DirCheck();
	Renderer->ChangeAnimation(ChangeAnimationName("Jump"));

	JumpVelocityVector = MaxJumpVelocityVector;
}

void APlayerMario::FreeMoveStart()
{
	Renderer->ChangeAnimation("Idle_Right");
}

void APlayerMario::IdleStart()
{
	//EngineDebug::OutPutDebugText("IdleStart");
	DirCheck();
	SetGravityRatio(1.0f);
	Renderer->ChangeAnimation(ChangeAnimationName("Idle"));
}

void APlayerMario::MoveStart()
{
	SetGravityRatio(1.0f);
	//EngineDebug::OutPutDebugText("MoveStart");
	DirCheck();
	Renderer->ChangeAnimation(ChangeAnimationName("Move"));
}

void APlayerMario::ReverseMoveStart()
{
	SetGravityRatio(1.0f);
	//EngineDebug::OutPutDebugText("ReverseMoveStart");
	DirCheck();
	Renderer->ChangeAnimation(ChangeAnimationName("ReverseMove"));
}




void APlayerMario::ReverseMove(float _DeltaTime)
{
	if (UEngineInput::IsDown('Z'))
	{
		StateChange(EActorState::Jump);
		return;
	}

	if (UEngineInput::IsPress(VK_LEFT))
	{

		//EngineDebug::OutPutDebugText(std::to_string(HorizonVelocityVector.X));
		if (HorizonVelocityVector.X < 0.0f)
		{
			StateChange(EActorState::Move);
			return;
		}

		AddHorizonVelocityVector(FVector::Left * _DeltaTime);

	}

	if (UEngineInput::IsPress(VK_RIGHT))
	{
		//EngineDebug::OutPutDebugText(std::to_string(HorizonVelocityVector.X));
		if (HorizonVelocityVector.X > 0.0f)
		{
			StateChange(EActorState::Move);
			return;
		}
		AddHorizonVelocityVector(FVector::Right * _DeltaTime);
	}

	if ((UEngineInput::IsFree(VK_LEFT) && UEngineInput::IsFree(VK_RIGHT)))
	{
		StateChange(EActorState::Idle);
		return;
	}

	ResultMovementUpdate(_DeltaTime);

}

// X축 이동만을 담당하는 함수
void APlayerMario::Move(float _DeltaTime)
{

	if (HorizonVelocityVector.X < 3.0f && HorizonVelocityVector.X > -3.0f && (UEngineInput::IsFree(VK_LEFT) && UEngineInput::IsFree(VK_RIGHT)))
	{
		StateChange(EActorState::Idle);
		return;
	}

	if (UEngineInput::IsDown('Z'))
	{
		StateChange(EActorState::Jump);
		return;
	}


	if (UEngineInput::IsPress(VK_LEFT))
	{
		AddHorizonVelocityVector(FVector::Left * _DeltaTime);
	}
	if (UEngineInput::IsPress(VK_RIGHT))
	{
		AddHorizonVelocityVector(FVector::Right * _DeltaTime);
	}

	ResultMovementUpdate(_DeltaTime);

	if (true == IsReverseMove())
	{
		StateChange(EActorState::ReverseMove);
		return;
	}
}

void APlayerMario::CollisionJump(float _DeltaTime)
{
	SetActorState(EActorState::Jump);

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
			StateChange(EActorState::Move);
			return;
		}

		StateChange(EActorState::Idle);
		return;
	}
}

void APlayerMario::Jump(float _DeltaTime)
{

	//UEngineDebug::OutPutDebugText(std::to_string(UEngineInput::GetPressTime('Z')));

	if (UEngineInput::IsUp('Z') || 0.15f < UEngineInput::GetPressTime('Z'))
	{
		SetGravityRatio(1.0f);
	}

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
			StateChange(EActorState::Move);
			return;
		}

		StateChange(EActorState::Idle);
		return;
	}
}

void APlayerMario::FreeMove(float _DeltaTime)
{
	if (UEngineInput::IsDown('1'))
	{
		StateChange(EActorState::Idle);
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
		StateChange(EActorState::Idle);
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
		StateChange(EActorState::FreeMove);
		return;
	}

	if (UEngineInput::IsDown('2'))
	{
		StateChange(EActorState::CameraMove);
		return;
	}

	if (UEngineInput::IsDown('Z'))
	{
		StateChange(EActorState::Jump);
		return;
	}

	if (UEngineInput::IsPress(VK_LEFT) || UEngineInput::IsPress(VK_RIGHT))
	{
		StateChange(EActorState::Move);
		return;
	}

	ResultMovementUpdate(_DeltaTime);
}

void APlayerMario::GetHit(float _DeltaTime)
{
	static float DelayTime = 0.5f;

	DelayTime -= _DeltaTime;

	if (0 >= DelayTime)
	{
		GravityVelocityVector += GravityAccVector * _DeltaTime;

		TotalVelocityVector = FVector::Zero;
		TotalVelocityVector = TotalVelocityVector + GravityVelocityVector + JumpVelocityVector;

		AddActorLocation(TotalVelocityVector * _DeltaTime);
	}

	// collision 맵 수정해서 캐릭터가 특정 색깔에 닿을때, 다시 시작하게 하는 Level로 넘어가게 하기
	// 혹은 위 함수가 실행되고 나서 특정 조건을 걸어서 다시 시작하게 하기
	// 여기에 기능 넣어야 함
}

void APlayerMario::GetHitStart()
{
	Renderer->ChangeAnimation("Dead");
	--Life;

	SetGravityZero();
	JumpVelocityVector = FVector::Up * 500.0f;
}



bool APlayerMario::DirCheck()
{
	EActorDir Dir = ActorDir;

	if (UEngineInput::IsPress(VK_LEFT) && UEngineInput::IsFree(VK_RIGHT))
	{
		Dir = EActorDir::Left;
	}

	if (UEngineInput::IsPress(VK_RIGHT) && UEngineInput::IsFree(VK_LEFT))
	{
		Dir = EActorDir::Right;
	}

	if (ActorDir != Dir)
	{
		SetActorDir(Dir);
		return false;
	}

	return true;
}

void APlayerMario::ReverseMoveCheck()
{
	DirCheck();
	Renderer->ChangeAnimation(ChangeAnimationName("Move"));
}

bool APlayerMario::IsReverseMove()
{
	if (false == DirCheck())
	{
		return true;
	}
	return false;
}




void APlayerMario::CameraPosUpdate(FVector _Player, FVector _MovePos)
{
	FVector CameraPos = GetWorld()->GetCameraPos();

	if (GetWorld()->GetCameraPos().X >= UContentsFunction::GetCollisionMapImg()->GetScale().X - UInGameValue::ResultMainWindowXScale)
	{
		GetWorld()->SetCameraPos(CameraPos);
		return;
	}

	float CheckRange = CameraPos.X + 2.0f * static_cast<float>(UInGameValue::ResultMainWindowXScale) / 5.0f;

	if (_Player.X >= CheckRange)
	{
		if (0 >= _MovePos.X)
		{
			_MovePos.X = 0.0f;
		}

		GetWorld()->AddCameraPos(_MovePos);
	}
}

void APlayerMario::AddHorizonVelocityVector(const FVector& _DirDelta)
{
	HorizonVelocityVector += _DirDelta * HorizonAccVector;
}

void APlayerMario::ApplyMovement(float _DeltaTime)
{
	AddActorLocation(TotalVelocityVector * _DeltaTime);
	// 플레이어가 윈도우 화면 2/5 지점에 왔을 때 카메라 이동
	CameraPosUpdate(GetActorLocation(), HorizonVelocityVector * _DeltaTime);

}

void APlayerMario::CalHorizonVelocityVector(float _DeltaTime)
{
	FVector CheckPos = GetActorLocation();
	CheckPos.Y -= UInGameValue::ColOffSetY;

	FVector BackPos = GetActorLocation();
	BackPos.Y -= UInGameValue::ColOffSetY;

	switch (ActorDir)
	{
	case EActorDir::Right:
		CheckPos.X += UInGameValue::ColOffSetX;
		BackPos.X -= UInGameValue::ColOffSetX;
		break;
	case EActorDir::Left:
		CheckPos.X -= UInGameValue::ColOffSetX;
		BackPos.X += UInGameValue::ColOffSetX;
		break;
	default:
		break;
	}

	Color8Bit Color = UContentsFunction::GetCollisionMapImg()->GetColor(CheckPos.iX(), CheckPos.iY(), UInGameValue::CollisionColor);
	Color8Bit PlayerBackColor = UContentsFunction::GetCollisionMapImg()->GetColor(BackPos.iX(), BackPos.iY(), UInGameValue::CollisionColor);

	if (Color == UInGameValue::CollisionColor || CheckPos.X <= GetWorld()->GetCameraPos().X)
	{
		HorizonVelocityVector = FVector::Zero;
	}

	if (PlayerBackColor == UInGameValue::CollisionColor || BackPos.X <= GetWorld()->GetCameraPos().X)
	{
		switch (ActorDir)
		{
		case EActorDir::Right:
			HorizonVelocityVector = FVector::Right * _DeltaTime * HorizonAccVector;
			break;
		case EActorDir::Left:
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
			HorizonVelocityVector = FVector::Zero;
		}
	}

	if (HorizonMaxSpeed <= HorizonVelocityVector.Size2D())
	{
		HorizonVelocityVector = HorizonVelocityVector.Normalize2DReturn() * HorizonMaxSpeed;
	}

}

void APlayerMario::CalJumpVelocityVector(float _DeltaTime)
{

}

void APlayerMario::ResultMovementUpdate(float _DeltaTime)
{
	CalHorizonVelocityVector(_DeltaTime);
	CalGravityVelocityVector(_DeltaTime);
	GroundUp();
	CalJumpVelocityVector(_DeltaTime);
	CalTotalVelocityVector(_DeltaTime);
	ApplyMovement(_DeltaTime);
}

void APlayerMario::GroundUp()
{
	while (true)
	{
		Color8Bit Color = UContentsFunction::GetCollisionMapImg()->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), UInGameValue::CollisionColor);
		if (UInGameValue::CollisionColor == Color)
		{
			AddActorLocation(FVector::Up);
		}
		else
		{
			break;
		}
	}
}