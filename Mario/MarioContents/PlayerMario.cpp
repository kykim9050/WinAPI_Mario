#include "PlayerMario.h"
#include <EnginePlatform/EngineInput.h>
#include <EngineBase/EngineMath.h>
#include <EngineBase/EngineDebug.h>
#include <cmath>
#include <EngineCore/EngineDebug.h>

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

	Renderer->CreateAnimation("Small_Idle_Right", "Mario_Right.png", 0, 0, 0.1f, true);
	Renderer->CreateAnimation("Small_Idle_Left", "Mario_Left.png", 0, 0, 0.1f, true);
	Renderer->CreateAnimation("Small_Move_Right", "Mario_Right.png", 1, 3, 0.1f, true);
	Renderer->CreateAnimation("Small_Move_Left", "Mario_Left.png", 1, 3, 0.1f, true);
	Renderer->CreateAnimation("Small_Jump_Right", "Mario_Right.png", 5, 5, 0.1f, true);
	Renderer->CreateAnimation("Small_Jump_Left", "Mario_Left.png", 5, 5, 0.1f, true);
	Renderer->CreateAnimation("Small_ReverseMove_Right", "Mario_Right.png", 4, 4, 0.1f, true);
	Renderer->CreateAnimation("Small_ReverseMove_Left", "Mario_Left.png", 4, 4, 0.1f, true);
	Renderer->CreateAnimation("Small_GrowUp_Left", "Mario_Left.png", { 29, 30, 31, 30, 31 ,30, 31, 32 }, 0.15f, false);
	Renderer->CreateAnimation("Small_GrowUp_Right", "Mario_Right.png", { 29, 30, 31, 30, 31 , 30, 31, 32 }, 0.15f, false);
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
	Renderer->CreateAnimation("Big_ChangingFireMario_Right", "ChangingFireMario_Right.png", 0, 2, 0.1f, true);
	Renderer->CreateAnimation("Big_ChangingFireMario_Left", "ChangingFireMario_Left.png", 0, 2, 0.1f, true);


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

	Renderer->CreateAnimation("ClimbDown", "Mario_Right.png", 7, 8, 0.3f, true);
	Renderer->CreateAnimation("StopClimbDown", "Mario_Right.png", 7, 7, 0.1f, true);
	Renderer->CreateAnimation("StopClimbDownAndTurnRight", "Mario_Left.png", 7, 7, 0.1f, true);
	



	BodyCollision = CreateCollision(ECollisionOrder::Player);
	BodyCollision->SetScale({ UInGameValue::PlayerCollisionScaleX, UInGameValue::PlayerCollisionScaleY });
	BodyCollision->SetPosition({0, -(BodyCollision->GetTransform().GetScale().ihY())});
	BodyCollision->SetColType(ECollisionType::Rect);

	MarioType = EMarioType::Small;
	ActorState = EActorState::Idle;
}

void APlayerMario::Tick(float _DeltaTime)
{
	UStateUnit::Tick(_DeltaTime);

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
	default:
		break;
	}
}

void APlayerMario::CollisionUpdate(float _DeltaTime)
{
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

	if (true == AteMushroom)
	{
		StateChange(EActorState::MarioGrowUp);
		AteMushroom = false;
	}

	if (true == AteFireFlower)
	{
		StateChange(EActorState::FireMario);
		AteFireFlower = false;
	}

	if (true == BlockBottomHit)
	{
		CollisionStateChange(ECollisionState::BlockBotHit);
		BlockBottomHit = false;
	}

	if (false == IsOnTheBlock && true == BodyCollision->CollisionCheck(ECollisionOrder::BlockTop, Result))
	{
		IsOnTheBlock = true;
		SetGravityZero();
		SetJumpZero();
		StateChange(EActorState::Idle);
	}
	else if(true == IsOnTheBlock && true == BodyCollision->CollisionCheck(ECollisionOrder::BlockTop, Result))
	{
		IsOnTheBlock = true;
	}

	if (true == BodyCollision->CollisionCheck(ECollisionOrder::BlockSide, Result))
	{
		CollisionStateChange(ECollisionState::BlockSideHit);
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
	//BodyCollision->ActiveOff();
	BodyCollision->SetOrder(static_cast<int>(ECollisionOrder::Invincible));

	Renderer->ChangeAnimation("SmallMario_Dead");
	--Life;

	SetGravityZero();
	JumpVelocityVector = FVector::Up * 500.0f;
}

void APlayerMario::JumpStart()
{
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
	if (UEngineInput::IsDown('Z'))
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
	
	if (UEngineInput::IsUp('Z') || 0.3f < UEngineInput::GetPressTime('Z'))
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
	static float DelayTime = 1.0f;

	DelayTime -= _DeltaTime;
	
	if (0.0f >= DelayTime)
	{
		GetWorld()->SetAllTimeScale(1.0f);
		DelayTime = 1.0f;

		switch (PrevActorState)
		{
		case EActorState::Jump:
		case EActorState::CollisionJump:
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
	static float DelayTime = 0.5f;

	DelayTime -= _DeltaTime;

	if (0.0f >= DelayTime)
	{
		GravityVelocityVector += GravityAccVector * _DeltaTime;

		TotalVelocityVector = FVector::Zero;
		TotalVelocityVector = TotalVelocityVector + GravityVelocityVector + JumpVelocityVector;

		AddActorLocation(TotalVelocityVector * _DeltaTime);
	}
}

void APlayerMario::ReachingEndFlag(float _DeltaTime)
{
	static int EndStep = 0;
	static float DelayTime = 3.0f;

	switch (EndStep)
	{
	case 0:
	{
		DelayTime -= _DeltaTime;

		if (0.0f >= DelayTime)
		{
			SetActorLocation({ GetActorLocation().X + BodyCollision->GetTransform().GetScale().X, GetActorLocation().Y });
			Renderer->ChangeAnimation("StopClimbDownAndTurnRight");
			DelayTime = 1.0f;
			EndStep = 1;
			break;
		}

		Color8Bit Color = UContentsFunction::GetCollisionMapImg()->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), UInGameValue::CollisionColor);

		if (UInGameValue::CollisionColor == Color)
		{
			Renderer->ChangeAnimation("StopClimbDown");
			break;
		}

		AddActorLocation(FVector::Down * 200.0f * _DeltaTime);
		break;
	}
	case 1:
	{
		DelayTime -= _DeltaTime;

		if (0.0f >= DelayTime)
		{
			Renderer->ChangeAnimation("Small_Move_Right");
			DelayTime = 3.0f;
			EndStep = 2;
			break;
		}

		break;
	}
	case 2:
	{
		DelayTime -= _DeltaTime;

		if (0.0f >= DelayTime)
		{
			//Renderer->ActiveOff();
			DelayTime = 3.0f;
			EndStep = 3;
			break;
		}

		SetJumpZero();
		HorizonVelocityVector = FVector::Right * 100.0f;
		ResultMovementUpdate(_DeltaTime);
		break;
	}
	default:
	{
		// 다음 스테이지로 넘어가는 코드 추가 필요
		StateChange(EActorState::Idle);
		break;
	}
	}

}


void APlayerMario::GetHitStart()
{
	DirCheck();
	Renderer->ChangeAnimation(ChangeAnimationName("SizeDown"));

	Renderer->SetAlpha(0.7f);

	MarioType = EMarioType::Small;

	BodyCollision->SetScale({ UInGameValue::PlayerCollisionScaleX, UInGameValue::PlayerCollisionScaleY });
	BodyCollision->SetPosition({ 0, -(BodyCollision->GetTransform().GetScale().ihY()) });

	GetWorld()->SetOtherTimeScale(EActorType::Player, 0.0f);

	PrevActorState = ActorState;
}


void APlayerMario::MarioGrowUpStart()
{
	DirCheck();
	Renderer->ChangeAnimation(ChangeAnimationName("GrowUp"));

	MarioType = EMarioType::Big;
	BodyCollision->SetTransform({ { 0,-40 }, {32, 64} });
	GetWorld()->SetOtherTimeScale(EActorType::Player, 0.0f);
	PrevActorState = ActorState;

}

void APlayerMario::ChangingFireMarioStart()
{
	DirCheck();
	Renderer->ChangeAnimation(ChangeAnimationName("ChangingFireMario"));

	MarioType = EMarioType::Fire;
	BodyCollision->SetTransform({ { 0,-40 }, {32, 64} });
	GetWorld()->SetOtherTimeScale(EActorType::Player, 0.0f);
	PrevActorState = ActorState;
}

void APlayerMario::ReachingEndFlagStart()
{
	Renderer->ChangeAnimation("ClimbDown");
}


void APlayerMario::BlockBotHitStart()
{
	SetJumpZero();
	SetGravityRatio(1.0f);
	CollisionStateChange(ECollisionState::None);
}

void APlayerMario::InvincibleStart()
{
	//BodyCollision->ActiveOff();
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
		std::vector<UCollision*> Result = std::vector<UCollision*>();
		Color8Bit Color = UContentsFunction::GetCollisionMapImg()->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), UInGameValue::CollisionColor);
		
		if (UInGameValue::CollisionColor == Color || true == BodyCollision->CollisionCheck(ECollisionOrder::BlockTop, Result))
		{
			AddActorLocation(FVector::Up);
		}
		else
		{
			break;
		}
	}
}

void APlayerMario::CalGravityVelocityVector(float _DeltaTime)
{
	GravityVelocityVector += GravityAccVector * _DeltaTime * GravityRatio;

	std::vector<UCollision*> Result = std::vector<UCollision*>();
	Color8Bit Color = UContentsFunction::GetCollisionMapImg()->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), UInGameValue::CollisionColor);

	if (UInGameValue::CollisionColor == Color || true == BodyCollision->CollisionCheck(ECollisionOrder::BlockTop, Result))
	{
		GravityVelocityVector = FVector::Zero;
	}
}


std::string APlayerMario::ChangeAnimationName(std::string _MainName)
{
	std::string Dir = "";
	CurAnimationName = _MainName;

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

	std::string Type = "";

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

	return Type + CurAnimationName + Dir;
}


void APlayerMario::Invincible(float _DeltaTime)
{
	static float InvincibleTime = 2.0f;

	InvincibleTime -= _DeltaTime;

	if (0.0f >= InvincibleTime)
	{
		Renderer->SetAlpha(1.0f);
		//BodyCollision->ActiveOn();
		BodyCollision->SetOrder(static_cast<int>(ECollisionOrder::Player));
		InvincibleTime = 2.0f;
		IsInvincible = false;
		CollisionStateChange(ECollisionState::None);
	}
}