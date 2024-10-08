﻿#include "PlayerMario.h"
#include <EnginePlatform/EngineInput.h>
#include <EngineBase/EngineMath.h>
#include <EngineBase/EngineDebug.h>
#include <cmath>
#include <EngineCore/EngineDebug.h>
#include "Koopa.h"
#include "Princess.h"
#include <EngineCore/EngineCore.h>
#include "LoadingLevel.h"
#include "UI.h"
#include "MarioBullet.h"

APlayerMario* APlayerMario::MainPlayer = nullptr;
bool APlayerMario::IsReachingStageEnd = false;
bool APlayerMario::InTheBossRoom = false;
bool APlayerMario::IsReachingCastleGate = false;

APlayerMario::APlayerMario()
{
	ActorDir = EActorDir::Right;
	MarioType = UPlayerInfoManager::GetInst().GetPlayerType();
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

	Renderer->CreateAnimation("Small_Idle_Right", "Mario_Right.png", 0, 0, 0.1f, true);
	Renderer->CreateAnimation("Small_Idle_Left", "Mario_Left.png", 0, 0, 0.1f, true);
	Renderer->CreateAnimation("Small_Move_Right", "Mario_Right.png", 1, 3, 0.1f, true);
	Renderer->CreateAnimation("Small_Move_Left", "Mario_Left.png", 1, 3, 0.1f, true);
	Renderer->CreateAnimation("Small_Jump_Right", "Mario_Right.png", 5, 5, 0.1f, true);
	Renderer->CreateAnimation("Small_Jump_Left", "Mario_Left.png", 5, 5, 0.1f, true);
	Renderer->CreateAnimation("Small_ReverseMove_Right", "Mario_Right.png", 4, 4, 0.1f, true);
	Renderer->CreateAnimation("Small_ReverseMove_Left", "Mario_Left.png", 4, 4, 0.1f, true);
	Renderer->CreateAnimation("GrowUp_Left", "Mario_Left.png", { 29, 30, 31, 30, 31 ,30, 31, 32 }, 0.15f, false);
	Renderer->CreateAnimation("GrowUp_Right", "Mario_Right.png", { 29, 30, 31, 30, 31 , 30, 31, 32 }, 0.15f, false);
	Renderer->CreateAnimation("SmallMario_Dead", "Mario_Right.png", 6, 6, 0.1f, true);


	Renderer->CreateAnimation("Big_Idle_Right", "Mario_Right.png", 14, 14, 0.1f, true);
	Renderer->CreateAnimation("Big_Idle_Left", "Mario_Left.png", 14, 14, 0.1f, true);
	Renderer->CreateAnimation("Big_Move_Right", "Mario_Right.png", 15, 17, 0.1f, true);
	Renderer->CreateAnimation("Big_Move_Left", "Mario_Left.png", 15, 17, 0.1f, true);
	Renderer->CreateAnimation("Big_Jump_Right", "Mario_Right.png", 19, 19, 0.1f, true);
	Renderer->CreateAnimation("Big_Jump_Left", "Mario_Left.png", 19, 19, 0.1f, true);
	Renderer->CreateAnimation("Big_ReverseMove_Right", "Mario_Right.png", 18, 18, 0.1f, true);
	Renderer->CreateAnimation("Big_ReverseMove_Left", "Mario_Left.png", 18, 18, 0.1f, true);
	Renderer->CreateAnimation("Big_SizeDown_Left", "Mario_Left.png", { 32, 33, 34, 33, 34, 33, 34, 35}, 0.15f, false);
	Renderer->CreateAnimation("Big_SizeDown_Right", "Mario_Right.png", { 32, 33, 34, 33, 34, 33, 34, 35 }, 0.15f, false);
	Renderer->CreateAnimation("ChangingFireMario_Right", "ChangingFireMario_Right.png", 0, 2, 0.1f, true);
	Renderer->CreateAnimation("ChangingFireMario_Left", "ChangingFireMario_Left.png", 0, 2, 0.1f, true);


	Renderer->CreateAnimation("Fire_Idle_Right", "FireMario_Right.png", 14, 14, 0.1f, true);
	Renderer->CreateAnimation("Fire_Idle_Left", "FireMario_Left.png", 14, 14, 0.1f, true);
	Renderer->CreateAnimation("Fire_Move_Right", "FireMario_Right.png", 15, 17, 0.1f, true);
	Renderer->CreateAnimation("Fire_Move_Left", "FireMario_Left.png", 15, 17, 0.1f, true);
	Renderer->CreateAnimation("Fire_Jump_Right", "FireMario_Right.png", 19, 19, 0.1f, true);
	Renderer->CreateAnimation("Fire_Jump_Left", "FireMario_Left.png", 19, 19, 0.1f, true);
	Renderer->CreateAnimation("Fire_ReverseMove_Right", "FireMario_Right.png", 18, 18, 0.1f, true);
	Renderer->CreateAnimation("Fire_ReverseMove_Left", "FireMario_Left.png", 18, 18, 0.1f, true);
	Renderer->CreateAnimation("Fire_SizeDown_Left", "Mario_Left.png", { 32, 33, 34, 33, 34, 33, 34, 35 }, 0.15f, false);
	Renderer->CreateAnimation("Fire_SizeDown_Right", "Mario_Right.png", { 32, 33, 34, 33, 34, 33, 34, 35 }, 0.15f, false);
	Renderer->CreateAnimation("Fire_IdleFireThrow_Right", "FireMario_Right.png", 41, 41, 0.05f, false);
	Renderer->CreateAnimation("Fire_IdleFireThrow_Left", "FireMario_Left.png", 41, 41, 0.05f, false);
	Renderer->CreateAnimation("Fire_MoveFireThrow1_Right", "FireMario_Right.png", 36, 36, 0.05f, false);
	Renderer->CreateAnimation("Fire_MoveFireThrow2_Right", "FireMario_Right.png", 37, 37, 0.05f, false);
	Renderer->CreateAnimation("Fire_MoveFireThrow3_Right", "FireMario_Right.png", 38, 38, 0.05f, false);
	Renderer->CreateAnimation("Fire_MoveFireThrow1_Left", "FireMario_Left.png", 36, 36, 0.05f, false);
	Renderer->CreateAnimation("Fire_MoveFireThrow2_Left", "FireMario_Left.png", 37, 37, 0.05f, false);
	Renderer->CreateAnimation("Fire_MoveFireThrow3_Left", "FireMario_Left.png", 38, 38, 0.05f, false);
	Renderer->CreateAnimation("Fire_ReverseMoveFireThrow_Right", "FireMario_Right.png", 39, 39, 0.05f, false);
	Renderer->CreateAnimation("Fire_ReverseMoveFireThrow_Left", "FireMario_Left.png", 39, 39, 0.05f, false);
	Renderer->CreateAnimation("Fire_JumpFireThrow_Right", "FireMario_Right.png", 40, 40, 0.05f, false);
	Renderer->CreateAnimation("Fire_JumpFireThrow_Left", "FireMario_Left.png", 40, 40, 0.05f, false);


	Renderer->CreateAnimation("Small_ClimbDown", "Mario_Right.png", 7, 8, 0.3f, true);
	Renderer->CreateAnimation("Big_ClimbDown", "Mario_Right.png", 21, 22, 0.3f, true);
	Renderer->CreateAnimation("Fire_ClimbDown", "FireMario_Right.png", 21, 22, 0.3f, true);

	Renderer->CreateAnimation("Small_StopClimbDown", "Mario_Right.png", 7, 7, 0.1f, true);
	Renderer->CreateAnimation("Big_StopClimbDown", "Mario_Right.png", 21, 21, 0.1f, true);
	Renderer->CreateAnimation("Fire_StopClimbDown", "FireMario_Right.png", 21, 21, 0.1f, true);
	
	Renderer->CreateAnimation("Small_StopClimbDownAndTurnRight", "Mario_Left.png", 7, 7, 0.1f, true);
	Renderer->CreateAnimation("Big_StopClimbDownAndTurnRight", "Mario_Left.png", 21, 21, 0.1f, true);
	Renderer->CreateAnimation("Fire_StopClimbDownAndTurnRight", "FireMario_Left.png", 21, 21, 0.1f, true);



	BodyCollision = CreateCollision(ECollisionOrder::Player);
	BodyCollision->SetScale({ UPlayerInfoManager::GetInst().GetPlayerColSize().iX(), UPlayerInfoManager::GetInst().GetPlayerColSize().iY()});
	BodyCollision->SetPosition({0, -(BodyCollision->GetTransform().GetScale().ihY())});
	BodyCollision->SetColType(ECollisionType::Rect);

	FootCollision = CreateCollision(ECollisionOrder::PlayerFootCollision);
	FootCollision->SetTransform({ { 0,0 }, {UPlayerInfoManager::GetInst().GetPlayerColSize().iX(), UInGameValue::FootCollisionScaleY} });
	FootCollision->SetPosition({ 0, -(static_cast<int>(UInGameValue::FootCollisionScaleY / 2)) });
	FootCollision->SetColType(ECollisionType::Rect);

	StateChange(EActorState::Idle);
}

void APlayerMario::Tick(float _DeltaTime)
{
	UStateUnit::Tick(_DeltaTime);

	if (false == GetClearBossStage() && true == AKoopa::GetKoopaIsDead())
	{
		SetClearBossStage();
		StateChange(EActorState::BossStageClear);
	}

	UEngineDebug::DebugTextPrint("X Pos : " +std::to_string(GetActorLocation().X) + " , Y Pos : " + std::to_string(GetActorLocation().Y), 20.0f);
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
		{
			switch (MarioType)
			{
			case EMarioType::Small:
				DeadStart();
				_PlayerState = EActorState::Dead;
				break;
			case EMarioType::Big:
			case EMarioType::Fire:
				GetHitStart();
				break;
			default:
				break;
			}
			break;
		}
		case EActorState::MarioGrowUp:
			MarioGrowUpStart();
			break;
		case EActorState::FireMario:
			ChangingFireMarioStart();
			break;
		case EActorState::ReachingEndFlag:
			ReachingEndFlagStart();
			break;
		case EActorState::ReachStageEnd:
			ReachStageEndStart();
			break;
		case EActorState::BossStageClear:
			BossStageClearStart();
			break;
		case EActorState::FallDown:
			FallDownStart();
			break;
		case EActorState::IdleFireThrow:
			IdleFireThrowStart();
			break;
		case EActorState::MoveFireThrow:
			MoveFireThrowStart();
			break;
		case EActorState::ReverseMoveFireThrow:
			ReverseMoveFireThrowStart();
			break;
		case EActorState::JumpFireThrow:
			JumpFireThrowStart();
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
		case ECollisionState::BlockBotHit:
			BlockBotHitStart();
			break;
		case ECollisionState::Invincible:
			InvincibleStart();
			break;
		default:
			break;
		}
	}

	SetCollisionState(_CollisionState);
}

void APlayerMario::StateUpdate(float _DeltaTime)
{
	BulletListReleaseUpdate();
	BulletReloadUpdate(_DeltaTime);

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
	case EActorState::MarioGrowUp:
	case EActorState::FireMario:
		Changing(_DeltaTime);
		break;
	case EActorState::Dead:
		Dead(_DeltaTime);
		break;
	case EActorState::ReachingEndFlag:
		ReachingEndFlag(_DeltaTime);
		break;
	case EActorState::BossStageClear:
		BossStageClear(_DeltaTime);
		break;
	case EActorState::ReachStageEnd:
		ReachStageEnd(_DeltaTime);
		break;
	case EActorState::FallDown:
		FallDown(_DeltaTime);
		break;
	case EActorState::IdleFireThrow:
		IdleFireThrow(_DeltaTime);
		break;
	case EActorState::MoveFireThrow:
		MoveFireThrow(_DeltaTime);
		break;
	case EActorState::ReverseMoveFireThrow:
		ReverseMoveFireThrow(_DeltaTime);
		break;
	case EActorState::JumpFireThrow:
		JumpFireThrow(_DeltaTime);
		break;
	default:
		break;
	}
}

void APlayerMario::CollisionUpdate(float _DeltaTime)
{
	DeadCollisionCheck();
	CollisionStateCheck();
	CollisionAction(_DeltaTime);
}

void APlayerMario::CollisionStateCheck()
{
	std::vector<UCollision*> Result = std::vector<UCollision*>();

	

	if (true == IsReachingStageEnd)
	{
		StateChange(EActorState::ReachingEndFlag);
		IsReachingStageEnd = false;
		return;
	}

	if (true == BodyCollision->CollisionCheck(ECollisionOrder::MonsterBullet, Result)
		|| true == BodyCollision->CollisionCheck(ECollisionOrder::AttackableTrap, Result))
	{
		StateChange(EActorState::GetHit);
		return;
	}

	if (true == IsReachToBossRoom())
	{
		CameraMoveOff();
	}

	if (true == AteMushroom)
	{
		AteMushroom = false;
		StateChange(EActorState::MarioGrowUp);
		return;
	}

	if (true == AteFireFlower)
	{
		AteFireFlower = false;
		
		switch (MarioType)
		{
		case EMarioType::Small:
			StateChange(EActorState::MarioGrowUp);
			break;
		case EMarioType::Big:
			StateChange(EActorState::FireMario);
			break;
		case EMarioType::Fire:
			USoundManager::GetInst().EffectSoundPlay("GetUpgradeItem.wav");
			break;
		default:
			break;
		}
		
		return;
	}

	if (true == BlockBottomHit)
	{
		USoundManager::GetInst().EffectSoundPlay("BlockBottomHit.wav");
		BlockBottomHit = false;
		SetJumpZero();
		SetGravityRatio(1.0f);
	}

	if (false == IsOnTheBlock && true == FootCollision->CollisionCheck(ECollisionOrder::BlockTop, Result) && static_cast<int>(ECollisionOrder::PlayerFootCollision) == FootCollision->GetOrder())
	{
		IsOnTheBlock = true;
		SetGravityZero();
		SetJumpZero();
		StateChange(EActorState::Idle);
	}
	else if(true == IsOnTheBlock && true == FootCollision->CollisionCheck(ECollisionOrder::BlockTop, Result))
	{
		IsOnTheBlock = true;
	}

	if (true == GetLeftSideBlockHit())
	{
		LeftSideBlockHit = false;
		AddActorLocation(FVector::Left);
	}

	if (true == GetRightSideBlockHit())
	{
		RightSideBlockHit = false;
		AddActorLocation(FVector::Right);
	}
	

}

void APlayerMario::CollisionAction(float _DeltaTime)
{
	if (IsInvincible)
	{
		Invincible(_DeltaTime);
	}
}


void APlayerMario::CollisionJumpStart()
{
	DirCheck();
	Renderer->ChangeAnimation(ChangeAnimationName("Jump"));

	SetGravityZero();
	JumpVelocityVector = CollisionJumpVelocityVector;
}

void APlayerMario::DeadStart()
{
	USoundManager::GetInst().BGMSoundStop();
	USoundManager::GetInst().EffectSoundPlay("MarioDie.wav");

	BodyCollision->ActiveOff();
	FootCollision->ActiveOff();
	IsInvincible = true;
	BodyCollision->SetOrder(static_cast<int>(ECollisionOrder::Invincible));

	Renderer->ChangeAnimation("SmallMario_Dead");
	UPlayerInfoManager::GetInst().AddPlayerLife(-1);

	SetGravityZero();
	JumpVelocityVector = FVector::Up * 500.0f;
}

void APlayerMario::JumpStart()
{
	switch (MarioType)
	{
	case EMarioType::Small:
		USoundManager::GetInst().EffectSoundPlay("SmallMarioJump.wav");
		break;
	case EMarioType::Big:
	case EMarioType::Fire:
		USoundManager::GetInst().EffectSoundPlay("BigMarioJump.wav");
		break;
	default:
		break;
	}
	AddActorLocation(FVector::Up * 4);
	SetGravityRatio(0.0f);
	IsOnTheBlock = false;
	DirCheck();
	Renderer->ChangeAnimation(ChangeAnimationName("Jump"));

	JumpVelocityVector = InitJumpVelocityVector;
}

void APlayerMario::FreeMoveStart()
{
	DirCheck();
	Renderer->ChangeAnimation(ChangeAnimationName("Idle"));
	BodyCollision->ActiveOff();
	Renderer->SetAlpha(0.5f);
}

void APlayerMario::IdleStart()
{
	DirCheck();
	Renderer->ChangeAnimation(ChangeAnimationName("Idle"));
}

void APlayerMario::MoveStart()
{
	DirCheck();
	Renderer->ChangeAnimation(ChangeAnimationName("Move"));
}

void APlayerMario::ReverseMoveStart()
{
	DirCheck();
	Renderer->ChangeAnimation(ChangeAnimationName("ReverseMove"));
}




void APlayerMario::ReverseMove(float _DeltaTime)
{
	if (UEngineInput::IsDown('X'))
	{
		if (true == CanUseBullet && EMarioType::Fire == MarioType)
		{
			StateChange(EActorState::ReverseMoveFireThrow);
			return;
		}
	}

	if (UEngineInput::IsDown(VK_SPACE))
	{
		StateChange(EActorState::Jump);
		return;
	}

	if (UEngineInput::IsPress(VK_LEFT))
	{
		if (HorizonVelocityVector.X < 0.0f)
		{
			StateChange(EActorState::Move);
			return;
		}

		AddHorizonVelocityVector(FVector::Left * _DeltaTime);

	}

	if (UEngineInput::IsPress(VK_RIGHT))
	{
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
	if (UEngineInput::IsDown('X'))
	{
		if (true == CanUseBullet && EMarioType::Fire == MarioType)
		{
			StateChange(EActorState::MoveFireThrow);
			return;
		}
	}

	if (HorizonVelocityVector.X < 3.0f && HorizonVelocityVector.X > -3.0f && (UEngineInput::IsFree(VK_LEFT) && UEngineInput::IsFree(VK_RIGHT)))
	{
		StateChange(EActorState::Idle);
		return;
	}

	if (UEngineInput::IsDown(VK_SPACE))
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
		AddHorizonVelocityVector(FVector::Left * _DeltaTime * 0.5);
	}

	if (UEngineInput::IsPress(VK_RIGHT))
	{
		AddHorizonVelocityVector(FVector::Right * _DeltaTime * 0.5);
	}

	ResultMovementUpdate(_DeltaTime);

	Color8Bit Color = UContentsFunction::GetCollisionMapImg()->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), UInGameValue::CollisionColor);

	if (UInGameValue::CollisionColor == Color)
	{
		JumpVelocityVector = FVector::Zero;
		if (true == UEngineInput::IsPress(VK_LEFT) || true == UEngineInput::IsPress(VK_RIGHT))
		{
			if (true == IsReverseMove())
			{
				StateChange(EActorState::ReverseMove);
				return;
			}

			StateChange(EActorState::Move);
			return;
		}

		StateChange(EActorState::Idle);
		return;
	}
}

void APlayerMario::Jump(float _DeltaTime)
{
	if (UEngineInput::IsDown('X'))
	{
		if (true == CanUseBullet && EMarioType::Fire == MarioType)
		{
			StateChange(EActorState::JumpFireThrow);
			return;
		}
	}
	
	if (UEngineInput::IsUp(VK_SPACE) || 0.3f < UEngineInput::GetPressTime(VK_SPACE))
	{
		SetGravityRatio(1.0f);
	}

	if (UEngineInput::IsPress(VK_LEFT))
	{
		AddHorizonVelocityVector(FVector::Left * _DeltaTime * 0.5);
	}

	if (UEngineInput::IsPress(VK_RIGHT))
	{
		AddHorizonVelocityVector(FVector::Right * _DeltaTime * 0.5);
	}

	ResultMovementUpdate(_DeltaTime);

	

	Color8Bit Color = UContentsFunction::GetCollisionMapImg()->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), UInGameValue::CollisionColor);

	if (UInGameValue::CollisionColor == Color)
	{
		JumpVelocityVector = FVector::Zero;
		if (true == UEngineInput::IsPress(VK_LEFT) || true == UEngineInput::IsPress(VK_RIGHT))
		{
			if (true == IsReverseMove())
			{
				StateChange(EActorState::ReverseMove);
				return;
			}

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
		BodyCollision->ActiveOn();
		Renderer->SetAlpha(1.0f);
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
	if (UEngineInput::IsDown('X'))
	{
		if (true == CanUseBullet && EMarioType::Fire == MarioType)
		{
			StateChange(EActorState::IdleFireThrow);
			return;
		}
	}
	
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

	if (UEngineInput::IsDown(VK_SPACE))
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
	static float DelayTime = 1.0f;

	DelayTime -= _DeltaTime;
	
	if (0.0f >= DelayTime)
	{
		GetWorld()->SetAllTimeScale(1.0f);
		DelayTime = 1.0f;
		SetActorState(PrevActorState);
		CollisionStateChange(ECollisionState::Invincible);
	}
}

void APlayerMario::Changing(float _DeltaTime)
{
	if (true == Renderer->IsCurAnimationEnd())
	{
		GetWorld()->SetAllTimeScale(1.0f);

		switch (PrevActorState)
		{
		case EActorState::Jump:
		case EActorState::CollisionJump:
			DirCheck();
			Renderer->ChangeAnimation(ChangeAnimationName("Jump"));
			SetActorState(PrevActorState);
			break;
		default:
			StateChange(PrevActorState);
			break;
		}
	}
}

void APlayerMario::Dead(float _DeltaTime)
{
	switch (DeadStep)
	{
	case 0:
	{
		DeadDelayTime -= _DeltaTime;


		if (0.0f >= DeadDelayTime)
		{
			++DeadStep;
			DeadDelayTime = 4.0f + DeadDelayTime;
			break;
		}
		
		break;
	}
	case 1:
	{
		DeadDelayTime -= _DeltaTime;


		if (0.0f >= DeadDelayTime)
		{
			++DeadStep;
			DeadDelayTime = 0.5f;
			break;
		}

		GravityVelocityVector += GravityAccVector * _DeltaTime;
		TotalVelocityVector = FVector::Zero;
		TotalVelocityVector = TotalVelocityVector + GravityVelocityVector + JumpVelocityVector;

		AddActorLocation(TotalVelocityVector * _DeltaTime);
		break;
	}
	case 2:
	{
		++DeadStep;

		std::string LevelName = GetWorld()->GetName();
		UPlayerInfoManager::GetInst().SetPrevStageLevel(LevelName);
		GEngine->DestroyLevel(LevelName);
		GEngine->CreateLevel<ULoadingLevel>("PlayerDead");
		GEngine->ChangeLevel("PlayerDead");
		break;
	}
	default:
		break;
	}
	

}

void APlayerMario::ReachingEndFlag(float _DeltaTime)
{
	static float DelayTime = 2.0f;

	switch (ReachingEndStep)
	{
	case 0:	// 첫 번째 단계 : 깃대를 잡고 내려감
	{
		DelayTime -= _DeltaTime;

		if (0.0f >= DelayTime)
		{
			// 지정 시간이 지나면 Player 반대편으로 도는 애니메이션 취하기
			SetActorLocation({ GetActorLocation().X + BodyCollision->GetTransform().GetScale().X + static_cast<float>(UInGameValue::EndFlagCollisionXScale), GetActorLocation().Y });
			Renderer->ChangeAnimation(ChangeAnimationName("StopClimbDownAndTurnRight", true));
			DelayTime = 0.5f;
			ReachingEndStep = 1;
			break;
		}

		Color8Bit Color = UContentsFunction::GetCollisionMapImg()->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), UInGameValue::CollisionColor);

		if (UInGameValue::CollisionColor == Color)
		{
			// Player 아래에 충돌체 만나면 내려가기 멈추고 시간이 다될때까지 대기
			Renderer->ChangeAnimation(ChangeAnimationName("StopClimbDown", true));
			break;
		}

		AddActorLocation(FVector::Down * 400.0f * _DeltaTime);
		break;
	}
	case 1:	// 도는 애니메이션 취하고 일정 시간 동안 대기하는 기능
	{
		DelayTime -= _DeltaTime;
		
		if (0.0f >= DelayTime)
		{
			USoundManager::GetInst().EffectSoundPlay("StageClear.wav");

			// 깃발을 잡고 내려간 후에 걸어서 성문 입구로 걸어가기 시작 (자동 - 조작 안먹힘)
			Renderer->ChangeAnimation(ChangeAnimationName("Move_Right", true));
			SetJumpZero();
			DelayTime = 2.0f;
			ReachingEndStep = 2;
			break;
		}

		break;
	}
	case 2: // 성문에 충돌할때까지 계속해서 오른쪽으로 걷기
	{
		if (IsReachingCastleGate)
		{
			// Stage종료
			StateChange(EActorState::ReachStageEnd);
			ReachingEndStep = -1;
			IsReachingCastleGate = false;
		}

		HorizonVelocityVector = FVector::Right * 150.0f;

		ResultMovementUpdate(_DeltaTime);
		break;
	}
	default:
		break;
	}

}

void APlayerMario::BossStageClear(float _DeltaTime)
{
	static float DelayTime = 0.5f;

	switch (BossStageClearStep)
	{
	case 0:
	{
		DelayTime -= _DeltaTime;

		if (0.0f >= DelayTime)
		{
			USoundManager::GetInst().EffectSoundPlay("ClearBoss.wav");

			DelayTime = 0.5f;
			BossStageClearStep = 1;
			SetJumpZero();
			CameraMoveOn();
			Renderer->ChangeAnimation(ChangeAnimationName("Move_Right", true));
			break;
		}

		break;
	}
	case 1:
	{
		if (true == IsMeetThePrincess())
		{
			BossStageClearStep = 2;
			SetSpeedZero();
			Renderer->ChangeAnimation(ChangeAnimationName("Idle_Right", true));
			break;
		}

		HorizonVelocityVector = FVector::Right * 120.0f;
		CameraPosUpdate(HorizonVelocityVector * _DeltaTime, true);
		CalGravityVelocityVector(_DeltaTime);
		GroundUp();
		CalTotalVelocityVector(_DeltaTime);
		ApplyMovement(_DeltaTime);
		break;
	}
	case 2:
	{
		if (GetWorld()->GetCameraPos().X >= UContentsFunction::GetCollisionMapImg()->GetScale().X - UInGameValue::ResultMainWindowXScale)
		{
			USoundManager::GetInst().EffectSoundPlay("SavePrincess.mp3");
			BossStageClearStep = 3;
			APrincess::PrintEndingMsg();
			return;
		}
		// 카메라위치가 맵 끝까지 갈때까지 기다리기
		HorizonVelocityVector = FVector::Right * 120.0f;
		CameraPosUpdate(HorizonVelocityVector * _DeltaTime, true);
		break;
	}
	default:
		break;
	}

}

void APlayerMario::ReachStageEnd(float _DeltaTime)
{
	static float DelayTime = 3.0f;

	if (true == AUI::IsCalTimeToScoreEnd())
	{
		DelayTime -= _DeltaTime;

		if (0.0f >= DelayTime)
		{
			DelayTime = 3.0f;
			UPlayerInfoManager::GetInst().SetPrevStageLevel(GetWorld()->GetName());
			GEngine->CreateLevel<ULoadingLevel>("NextLevel");
			GEngine->ChangeLevel("NextLevel");
		}
	}
}

void APlayerMario::FallDown(float _DeltaTime)
{
	static float FallingTime = 4.0f;

	FallingTime -= _DeltaTime;

	if (0.0f >= FallingTime)
	{
		FallingTime = 4.0f;
		SetGravityZero();
		
		UPlayerInfoManager::GetInst().AddPlayerLife(-1);
		
		std::string LevelName = GetWorld()->GetName();
		UPlayerInfoManager::GetInst().SetPrevStageLevel(LevelName);
		UPlayerInfoManager::GetInst().SetPlayerType(EMarioType::Small);
		UPlayerInfoManager::GetInst().SetPlayerColSize({ UInGameValue::PlayerCollisionScaleX, UInGameValue::PlayerCollisionScaleY });
		GEngine->DestroyLevel(LevelName);
		GEngine->CreateLevel<ULoadingLevel>("PlayerDead");
		GEngine->ChangeLevel("PlayerDead");
		return;
	}

	GravityVelocityVector += GravityAccVector * _DeltaTime * GravityRatio;
	CalTotalVelocityVector(_DeltaTime);
	ApplyMovement(_DeltaTime);
}

void APlayerMario::IdleFireThrow(float _DeltaTime)
{
	if (Renderer->IsCurAnimationEnd())
	{
		StateChange(EActorState::Idle);
		return;
	}

	ResultMovementUpdate(_DeltaTime);
}

void APlayerMario::MoveFireThrow(float _DeltaTime)
{
	if (Renderer->IsCurAnimationEnd())
	{
		StateChange(EActorState::Move);
		return;
	}

	if (UEngineInput::IsDown(VK_SPACE))
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

void APlayerMario::ReverseMoveFireThrow(float _DeltaTime)
{
	if (Renderer->IsCurAnimationEnd())
	{
		StateChange(EActorState::ReverseMove);
		return;
	}

	if (UEngineInput::IsDown(VK_SPACE))
	{
		StateChange(EActorState::Jump);
		return;
	}

	if (UEngineInput::IsPress(VK_LEFT))
	{
		if (HorizonVelocityVector.X < 0.0f)
		{
			StateChange(EActorState::Move);
			return;
		}

		AddHorizonVelocityVector(FVector::Left * _DeltaTime);

	}

	if (UEngineInput::IsPress(VK_RIGHT))
	{
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

void APlayerMario::JumpFireThrow(float _DeltaTime)
{
	if (Renderer->IsCurAnimationEnd())
	{
		Renderer->ChangeAnimation(ChangeAnimationName("Jump"));
		SetActorState(EActorState::Jump);
		return;
	}

	if (UEngineInput::IsUp(VK_SPACE) || 0.3f < UEngineInput::GetPressTime(VK_SPACE))
	{
		SetGravityRatio(1.0f);
	}

	if (UEngineInput::IsPress(VK_LEFT))
	{
		AddHorizonVelocityVector(FVector::Left * _DeltaTime * 0.5);
	}

	if (UEngineInput::IsPress(VK_RIGHT))
	{
		AddHorizonVelocityVector(FVector::Right * _DeltaTime * 0.5);
	}

	ResultMovementUpdate(_DeltaTime);



	Color8Bit Color = UContentsFunction::GetCollisionMapImg()->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), UInGameValue::CollisionColor);

	if (UInGameValue::CollisionColor == Color)
	{
		JumpVelocityVector = FVector::Zero;
		if (true == UEngineInput::IsPress(VK_LEFT) || true == UEngineInput::IsPress(VK_RIGHT))
		{
			if (true == IsReverseMove())
			{
				StateChange(EActorState::ReverseMove);
				return;
			}

			StateChange(EActorState::Move);
			return;
		}

		StateChange(EActorState::Idle);
		return;
	}
}


void APlayerMario::GetHitStart()
{
	USoundManager::GetInst().EffectSoundPlay("PipeTravel.wav");

	DirCheck();
	Renderer->ChangeAnimation(ChangeAnimationName("SizeDown"));

	BodyCollision->ActiveOff();
	Renderer->SetAlpha(0.7f);

	MarioType = EMarioType::Small;
	UPlayerInfoManager::GetInst().SetPlayerType(MarioType);

	BodyCollision->SetScale({ UInGameValue::PlayerCollisionScaleX, UInGameValue::PlayerCollisionScaleY });
	UPlayerInfoManager::GetInst().SetPlayerColSize({ UInGameValue::PlayerCollisionScaleX, UInGameValue::PlayerCollisionScaleY });
	BodyCollision->SetPosition({ 0, -(BodyCollision->GetTransform().GetScale().ihY()) });

	GetWorld()->SetOtherTimeScale(EActorType::Player, 0.0f);

	PrevActorState = ActorState;
}


void APlayerMario::MarioGrowUpStart()
{
	USoundManager::GetInst().EffectSoundPlay("GetUpgradeItem.wav");

	DirCheck();
	Renderer->ChangeAnimation(ChangeAnimationName("GrowUp", false, true));

	MarioType = EMarioType::Big;
	UPlayerInfoManager::GetInst().SetPlayerType(MarioType);

	BodyCollision->SetScale(UInGameValue::BigMarioColScale);
	UPlayerInfoManager::GetInst().SetPlayerColSize(UInGameValue::BigMarioColScale);
	BodyCollision->SetPosition({ 0, -(BodyCollision->GetTransform().GetScale().ihY()) });

	GetWorld()->SetOtherTimeScale(EActorType::Player, 0.0f);
	GetWorld()->SetTimeScale(EActorType::ScoreImg, 1.0f);
	PrevActorState = ActorState;

}

void APlayerMario::ChangingFireMarioStart()
{
	USoundManager::GetInst().EffectSoundPlay("GetUpgradeItem.wav");

	DirCheck();
	Renderer->ChangeAnimation(ChangeAnimationName("ChangingFireMario", false, true));

	MarioType = EMarioType::Fire;
	UPlayerInfoManager::GetInst().SetPlayerType(MarioType);

	BodyCollision->SetScale(UInGameValue::BigMarioColScale);
	UPlayerInfoManager::GetInst().SetPlayerColSize(UInGameValue::BigMarioColScale);
	BodyCollision->SetPosition({ 0, -(BodyCollision->GetTransform().GetScale().ihY()) });

	GetWorld()->SetOtherTimeScale(EActorType::Player, 0.0f);
	GetWorld()->SetTimeScale(EActorType::ScoreImg, 1.0f);
	PrevActorState = ActorState;
}

void APlayerMario::ReachingEndFlagStart()
{
	USoundManager::GetInst().BGMSoundStop();
	USoundManager::GetInst().EffectSoundPlay("FlagTouch.wav");
	Renderer->ChangeAnimation(ChangeAnimationName("ClimbDown", true));
}

void APlayerMario::ReachStageEndStart()
{
	DirCheck();
	Renderer->ChangeAnimation(ChangeAnimationName("Idle"));
	Renderer->ActiveOff();
	TotalVelocityVector = FVector::Zero;
}

void APlayerMario::BossStageClearStart()
{
	GetWorld()->SetTimeScale(EActorType::Player, 1.0f);
}

void APlayerMario::FallDownStart()
{
	USoundManager::GetInst().BGMSoundStop();
	USoundManager::GetInst().EffectSoundPlay("MarioDie.wav");
}

void APlayerMario::IdleFireThrowStart()
{
	DirCheck();
	Renderer->ChangeAnimation(ChangeAnimationName("IdleFireThrow"));
	BulletFire();
}

void APlayerMario::MoveFireThrowStart()
{
	DirCheck();

	int MoveAniFrame = Renderer->GetCurAnimationFrame();

	switch (MoveAniFrame)
	{
	case 0:
		Renderer->ChangeAnimation(ChangeAnimationName("MoveFireThrow2"));
		break;
	case 1:
		Renderer->ChangeAnimation(ChangeAnimationName("MoveFireThrow3"));
		break;
	case 2:
		Renderer->ChangeAnimation(ChangeAnimationName("MoveFireThrow1"));
		break;
	default:
		break;
	}
	BulletFire();
}

void APlayerMario::ReverseMoveFireThrowStart()
{
	DirCheck();
	Renderer->ChangeAnimation(ChangeAnimationName("ReverseMoveFireThrow"));
	BulletFire();
}

void APlayerMario::JumpFireThrowStart()
{
	DirCheck();
	Renderer->ChangeAnimation(ChangeAnimationName("JumpFireThrow"));
	BulletFire();
}

void APlayerMario::BlockBotHitStart()
{
	SetJumpZero();
	SetGravityRatio(1.0f);
	CollisionStateChange(ECollisionState::None);
}

void APlayerMario::InvincibleStart()
{
	BodyCollision->SetOrder(static_cast<int>(ECollisionOrder::Invincible));
	IsInvincible = true;
	CollisionStateChange(ECollisionState::None);
}

void APlayerMario::BlockSideHitStart()
{
	SetSpeedZero();
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




void APlayerMario::CameraPosUpdate(FVector _MovePos, bool _ExceptCheckRange)
{
	FVector CameraPos = GetWorld()->GetCameraPos();

	if (GetWorld()->GetCameraPos().X >= UContentsFunction::GetCollisionMapImg()->GetScale().X - UInGameValue::ResultMainWindowXScale)
	{
		GetWorld()->SetCameraPos(CameraPos);
		return;
	}


	if (false == _ExceptCheckRange)
	{
		float CheckRange = CameraPos.X + 2.0f * static_cast<float>(UInGameValue::ResultMainWindowXScale) / 5.0f;

		if (GetActorLocation().X >= CheckRange)
		{
			if (0 >= _MovePos.X)
			{
				_MovePos.X = 0.0f;
			}
			GetWorld()->AddCameraPos(_MovePos);
			return;
		}
	}
	else if (true == _ExceptCheckRange)
	{
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
	if (false == IsCameraMovePause())
	{
		CameraPosUpdate(HorizonVelocityVector * _DeltaTime);
	}

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
			AddActorLocation(FVector::Right * 2);
			break;
		case EActorDir::Left:
			AddActorLocation(FVector::Left * 2);
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
	CeilingCheck();
	CalJumpVelocityVector(_DeltaTime);
	CalTotalVelocityVector(_DeltaTime);
	ApplyMovement(_DeltaTime);
}

void APlayerMario::GroundUp()
{
	while (true)
	{
		std::vector<UCollision*> Result = std::vector<UCollision*>();
		Color8Bit Color = UContentsFunction::GetCollisionMapImg()->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), UInGameValue::CollisionColor);
		
		if (UInGameValue::CollisionColor == Color || true == FootCollision->CollisionCheck(ECollisionOrder::BlockTop, Result))
		{
			AddActorLocation(FVector::Up);
		}
		else
		{
			break;
		}
	}
}

void APlayerMario::CeilingCheck()
{
	Color8Bit Color = UContentsFunction::GetCollisionMapImg()->GetColor(GetActorLocation().iX(), GetActorLocation().iY() - BodyCollision->GetTransform().GetScale().ihY(), UInGameValue::CollisionColor);

	if (UInGameValue::CollisionColor == Color)
	{
		USoundManager::GetInst().EffectSoundPlay("BlockBottomHit.wav");
		SetJumpZero();
		SetGravityRatio(1.0f);
	}

}

void APlayerMario::CalGravityVelocityVector(float _DeltaTime)
{
	GravityVelocityVector += GravityAccVector * _DeltaTime * GravityRatio;

	std::vector<UCollision*> Result = std::vector<UCollision*>();
	Color8Bit Color = UContentsFunction::GetCollisionMapImg()->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), UInGameValue::CollisionColor);

	if (UInGameValue::CollisionColor == Color || true == FootCollision->CollisionCheck(ECollisionOrder::BlockTop, Result))
	{
		GravityVelocityVector = FVector::Zero;
	}
}


std::string APlayerMario::ChangeAnimationName(std::string _MainName, bool _DirExcept, bool _TypeExcept)
{

	std::string Dir = "";
	CurAnimationName = _MainName;

	if (!_DirExcept)
	{
		switch (ActorDir)
		{
		case EActorDir::Left:
			Dir = "_Left";
			break;
		case EActorDir::Right:
			Dir = "_Right";
			break;
		default:
			break;
		}
	}

	std::string Type = "";


	if (!_TypeExcept)
	{
		switch (MarioType)
		{
		case EMarioType::Small:
			Type = "Small_";
			break;
		case EMarioType::Big:
			Type = "Big_";
			break;
		case EMarioType::Fire:
			Type = "Fire_";
			break;
		default:
			break;
		}
	}

	return Type + CurAnimationName + Dir;
}


void APlayerMario::Invincible(float _DeltaTime)
{
	static float InvincibleTime = 2.0f;

	InvincibleTime -= _DeltaTime;

	if (0.0f >= InvincibleTime)
	{
		Renderer->SetAlpha(1.0f);
		BodyCollision->ActiveOn();
		BodyCollision->SetOrder(static_cast<int>(ECollisionOrder::Player));
		InvincibleTime = 2.0f;
		IsInvincible = false;
		CollisionStateChange(ECollisionState::None);
	}
}

void APlayerMario::DeadCollisionCheck()
{
	UStateUnit::DeadCollisionCheck();

	if (true == IsPlayerFallDown())
	{
		return;
	}

	Color8Bit Color = UContentsFunction::GetCollisionMapImg()->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), UInGameValue::CollisionColor);

	if (Color8Bit::YellowA == Color)
	{
		SetPlayerFallDown();
		StateChange(EActorState::FallDown);
		return;
	}
}

void APlayerMario::BulletFire()
{
	USoundManager::GetInst().EffectSoundPlay("FireBall.wav");

	EActorDir BulletDir = ActorDir;
	FVector BulletInitPos = FVector();

	switch (ActorDir)
	{
	case EActorDir::Left:
		BulletDir = EActorDir::Left;
		BulletInitPos.X = GetBodyCollision()->GetActorBaseTransform().Left();
		break;
	case EActorDir::Right:
		BulletDir = EActorDir::Right;
		BulletInitPos.X = GetBodyCollision()->GetActorBaseTransform().Right();
		break;
	default:
		break;
	}
	BulletInitPos.Y = GetBodyCollision()->GetActorBaseTransform().Top();

	NewFireBall = GetWorld()->SpawnActor<AMarioBullet>(EActorType::Bullet);
	NewFireBall->SetActorLocation(BulletInitPos);
	NewFireBall->SetDir(BulletDir);
	NewFireBall->StateChange(EActorState::FallDown);

	Bullets.push_back(NewFireBall);

	++ThrowBulletNum;
}

void APlayerMario::BulletListReleaseUpdate()
{
	std::list<AMarioBullet*>::iterator StartIter = Bullets.begin();
	std::list<AMarioBullet*>::iterator EndIter = Bullets.end();

	for (; StartIter != EndIter; )
	{
		AMarioBullet* Bullet = *StartIter;

		if (nullptr == Bullet)
		{
			MsgBoxAssert("MarioBullet이 nullptr 입니다.");
			return;
		}

		if (false == Bullet->IsDestroy())
		{
			++StartIter;
			continue;
		}

		StartIter = Bullets.erase(StartIter);
	}
}

void APlayerMario::BulletReloadUpdate(float _DeltaTime)
{
	if (2 <= ThrowBulletNum)
	{
		CanUseBullet = false;

		if (0.0f >= BulletReloadTime)
		{
			BulletReloadTime = 0.3f + BulletReloadTime;
			ThrowBulletNum = 0;
			CanUseBullet = true;
			return;
		}

		BulletReloadTime -= _DeltaTime;
	}
}