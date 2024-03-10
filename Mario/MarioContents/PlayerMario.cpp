#include "PlayerMario.h"
#include <EnginePlatform/EngineInput.h>
#include <EngineBase/EngineMath.h>
#include <EngineBase/EngineDebug.h>
#include <cmath>
#include <EngineCore/EngineDebug.h>
#include "Koopa.h"
#include "Princess.h"


APlayerMario* APlayerMario::MainPlayer = nullptr;
bool APlayerMario::InTheBossRoom = false;


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
	BodyCollision->SetScale({ UInGameValue::PlayerCollisionScaleX, UInGameValue::PlayerCollisionScaleY });
	BodyCollision->SetPosition({0, -(BodyCollision->GetTransform().GetScale().ihY())});
	BodyCollision->SetColType(ECollisionType::Rect);

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
	case EActorState::BossStageClear:
		BossStageClear(_DeltaTime);
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

	if (true == BodyCollision->CollisionCheck(ECollisionOrder::MonsterBullet, Result))
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
	}

	if (true == AteFireFlower)
	{
		AteFireFlower = false;
		StateChange(EActorState::FireMario);
	}

	if (true == BlockBottomHit)
	{
		CollisionStateChange(ECollisionState::BlockBotHit);
		BlockBottomHit = false;
	}

	if (false == IsOnTheBlock && true == BodyCollision->CollisionCheck(ECollisionOrder::BlockTop, Result) && static_cast<int>(ECollisionOrder::Player) == BodyCollision->GetOrder())
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
	static float DelayTime = 2.0f;

	switch (EndStep)
	{
	case 0:	// 첫 번째 단계 : 깃대를 잡고 내려감
	{
		DelayTime -= _DeltaTime;

		if (0.0f >= DelayTime)
		{
			// 지정 시간이 지나면 Player 반대편으로 도는 애니메이션 취하기
			SetActorLocation({ GetActorLocation().X + BodyCollision->GetTransform().GetScale().X + static_cast<float>(UInGameValue::EndFlagCollisionXScale), GetActorLocation().Y });
			Renderer->ChangeAnimation(ChangeAnimationName("StopClimbDownAndTurnRight", true));
			DelayTime = 1.0f;
			EndStep = 1;
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
			// 깃발을 잡고 내려간 후에 걸어서 성문 입구로 걸어가기 시작 (자동 - 조작 안먹힘)
			Renderer->ChangeAnimation(ChangeAnimationName("Move_Right", true));
			SetJumpZero();
			DelayTime = 0.0f;
			EndStep = 2;
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
			EndStep = -1;
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
	static int EndStep = 0;
	static float DelayTime = 0.5f;

	switch (EndStep)
	{
	case 0:
	{
		DelayTime -= _DeltaTime;

		if (0.0f >= DelayTime)
		{
			DelayTime = 0.5f + DelayTime;
			EndStep = 1;
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
			EndStep = 2;
			SetSpeedZero();
			Renderer->ChangeAnimation(ChangeAnimationName("Idle_Right", true));
			break;
		}

		HorizonVelocityVector = FVector::Right * 150.0f;
		CameraPosUpdate(HorizonVelocityVector * _DeltaTime, true);
		ResultMovementUpdate(_DeltaTime);
		break;
	}
	case 2:
	{
		if (GetWorld()->GetCameraPos().X >= UContentsFunction::GetCollisionMapImg()->GetScale().X - UInGameValue::ResultMainWindowXScale)
		{
			EndStep = 3;
			APrincess::PrintEndingMsg();
			return;
		}
		// 카메라위치가 맵 끝까지 갈때까지 기다리기
		HorizonVelocityVector = FVector::Right * 150.0f;
		CameraPosUpdate(HorizonVelocityVector * _DeltaTime, true);
		break;
	}
	default:
		break;
	}

}



void APlayerMario::GetHitStart()
{
	DirCheck();
	Renderer->ChangeAnimation(ChangeAnimationName("SizeDown"));

	Renderer->SetAlpha(0.7f);

	MarioType = EMarioType::Small;
	UPlayerInfoManager::GetInst().SetPlayerType(MarioType);

	BodyCollision->SetScale({ UInGameValue::PlayerCollisionScaleX, UInGameValue::PlayerCollisionScaleY });
	BodyCollision->SetPosition({ 0, -(BodyCollision->GetTransform().GetScale().ihY()) });

	GetWorld()->SetOtherTimeScale(EActorType::Player, 0.0f);

	PrevActorState = ActorState;
}


void APlayerMario::MarioGrowUpStart()
{
	DirCheck();
	Renderer->ChangeAnimation(ChangeAnimationName("GrowUp", false, true));

	MarioType = EMarioType::Big;
	UPlayerInfoManager::GetInst().SetPlayerType(MarioType);

	BodyCollision->SetTransform({ { 0,-40 }, {32, 64} });
	GetWorld()->SetOtherTimeScale(EActorType::Player, 0.0f);
	PrevActorState = ActorState;

}

void APlayerMario::ChangingFireMarioStart()
{
	DirCheck();
	Renderer->ChangeAnimation(ChangeAnimationName("ChangingFireMario", false, true));

	MarioType = EMarioType::Fire;
	UPlayerInfoManager::GetInst().SetPlayerType(MarioType);

	BodyCollision->SetTransform({ { 0,-40 }, {32, 64} });
	GetWorld()->SetOtherTimeScale(EActorType::Player, 0.0f);
	PrevActorState = ActorState;
}

void APlayerMario::ReachingEndFlagStart()
{
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

void APlayerMario::CeilingCheck()
{
	Color8Bit Color = UContentsFunction::GetCollisionMapImg()->GetColor(GetActorLocation().iX(), GetActorLocation().iY() - BodyCollision->GetTransform().GetScale().ihY(), UInGameValue::CollisionColor);

	if (UInGameValue::CollisionColor == Color)
	{
		SetJumpZero();
		SetGravityRatio(1.0f);
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
		//BodyCollision->ActiveOn();
		BodyCollision->SetOrder(static_cast<int>(ECollisionOrder::Player));
		InvincibleTime = 2.0f;
		IsInvincible = false;
		CollisionStateChange(ECollisionState::None);
	}
}