#include "PlayerMario.h"
#include "EnumClass.h"
#include <EnginePlatform/EngineInput.h>
#include <EngineBase/EngineMath.h>
#include "InGameValue.h"
#include <EngineBase/EngineDebug.h>
#include "ContentsFunction.h"


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

void APlayerMario::GravityCheck(float _DeltaTime)
{
	Color8Bit MapColor = UContentsFunction::GetCollisionMapImg()->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), UInGameValue::CollisionColor);

	if (UInGameValue::CollisionColor != MapColor)
	{
		AddActorLocation(FVector::Down * PGravity * _DeltaTime);
	}
}


void APlayerMario::Idle(float _DeltaTime)
{
	GravityCheck(_DeltaTime);

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

	GravityCheck(_DeltaTime);

	DirCheck();
	MarioRenderer->ChangeAnimation(ChangeAnimationName("Move"));


	FVector MovePos = FVector::Zero;

	if (UEngineInput::IsPress(VK_LEFT))
	{
		MovePos += FVector::Left * PVelocity * _DeltaTime;
	}
	if (UEngineInput::IsPress(VK_RIGHT))
	{
		MovePos += FVector::Right * PVelocity * _DeltaTime;
	}


	FVector ComparePos = GetActorLocation();

	switch (MarioDir)
	{
	case EPlayerDir::Right:
		ComparePos.X += UInGameValue::ColOffSetX;
		break;
	case EPlayerDir::Left:
		ComparePos.X -= UInGameValue::ColOffSetX;
		break;
	default:
		break;
	}

	ComparePos.Y -= UInGameValue::ColOffSetY;

	Color8Bit ColMapColor = UContentsFunction::GetCollisionMapImg()->GetColor(ComparePos.iX(), ComparePos.iY(), UInGameValue::CollisionColor);

	if (UInGameValue::CollisionColor != ColMapColor)
	{
		AddActorLocation(MovePos);
		GetWorld()->AddCameraPos(MovePos);
	}
}

void APlayerMario::DirCheck()
{
	EPlayerDir Dir = MarioDir;

	if (UEngineInput::IsPress(VK_LEFT))
	{
		Dir = EPlayerDir::Left;
		EngineDebug::OutPutDebugText("_Left");
	}
	else if (UEngineInput::IsPress(VK_RIGHT))
	{
		Dir = EPlayerDir::Right;
		EngineDebug::OutPutDebugText("_Right");
	}

	if (MarioDir != Dir)
	{
		SetMarioDir(Dir);
	}
}

void APlayerMario::IdleStart()
{
	DirCheck();
	MarioRenderer->ChangeAnimation(ChangeAnimationName("Idle"));
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

void APlayerMario::MoveStart()
{
	DirCheck();
	MarioRenderer->ChangeAnimation(ChangeAnimationName("Move"));
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