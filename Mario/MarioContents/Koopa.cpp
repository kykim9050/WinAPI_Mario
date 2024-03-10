#include "Koopa.h"
#include "KoopaBullet.h"
#include "CastleBridge.h"

AKoopa::AKoopa()
{
	HorizonVelocityVector = ActorMoveDir * 50.0f;
}

AKoopa::~AKoopa()
{
}

void AKoopa::BeginPlay()
{
	AMonsterUnit::BeginPlay();

	Renderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::Monster));
	Renderer->SetImage("Koopa_Left.png");
	FVector KoopaScale = Renderer->GetImage()->GetScale();
	Renderer->SetTransform({ {0,0}, {KoopaScale.iX() / UInGameValue::KoopaImgXValue * UInGameValue::WindowSizeMulValue, KoopaScale.iY() / UInGameValue::KoopaImgYValue * UInGameValue::WindowSizeMulValue} });
	Renderer->CreateAnimation("Koopa_LeftMove", "Koopa_Left.png", 0, 1, 0.2f, true);
	Renderer->CreateAnimation("Koopa_RightMove", "Koopa_Right.png", 0, 1, 0.2f, true);
	Renderer->CreateAnimation("Koopa_RightFire", "Koopa_Right.png", 2, 2, 0.1f, false);
	Renderer->CreateAnimation("Koopa_LeftFire", "Koopa_Left.png", 2, 2, 0.1f, false);
	Renderer->CreateAnimation("Koopa_DeadMotion", "Koopa_Right.png", 0, 1, 0.1f, true);
	Renderer->CreateAnimation("Koopa_FallDown", "Koopa_Right.png", 0, 0, 0.1f, false);

	BodyCollision = CreateCollision(ECollisionOrder::Monster);
	BodyCollision->SetTransform({ { 0,0 }, { UInGameValue::KoopaBodyCollisionScaleX, UInGameValue::KoopaBodyCollisionScaleY} });
	BodyCollision->SetPosition({ 0, -(BodyCollision->GetTransform().GetScale().ihY()) });
	BodyCollision->SetColType(ECollisionType::Rect);

	FootCollision = CreateCollision(ECollisionOrder::Monster);
	FootCollision->SetTransform({ { 0,0 }, { UInGameValue::KoopaBodyCollisionScaleX, UInGameValue::FootCollisionScaleY} });
	FootCollision->SetPosition({ 0, -(static_cast<int>(UInGameValue::FootCollisionScaleY / 2))});
	FootCollision->SetColType(ECollisionType::Rect);

	SetActorState(EActorState::FirstInit);

}

void AKoopa::Tick(float _DeltaTime)
{
	AMonsterUnit::Tick(_DeltaTime);

	BulletListReleaseUpdate();
}

void AKoopa::FirstInit(float _Deltatime)
{
	InitPos = GetActorLocation();
	if (GetActorLocation().iX() - GetPlayer()->GetActorLocation().iX() < UInGameValue::ResultMainWindowXScale)
	{
		StateChange(EActorState::Move);
	}
}

void AKoopa::MoveStart()
{
	JumpVelocityVector = FVector::Zero;
	HorizonVelocityVector = ActorMoveDir * KoopaSpeed;

	if (EActorDir::Left == ActorDir)
	{
		Renderer->ChangeAnimation("Koopa_LeftMove");
		return;
	}

	if (EActorDir::Right == ActorDir)
	{
		Renderer->ChangeAnimation("Koopa_RightMove");
		return;
	}
}

void AKoopa::JumpStart()
{
	JumpVelocityVector = FVector::Up * KoopaJump;
	HorizonVelocityVector = ActorMoveDir * KoopaSpeed;

	if (EActorDir::Left == ActorDir)
	{
		Renderer->ChangeAnimation("Koopa_LeftMove");
		return;
	}

	if (EActorDir::Right == ActorDir)
	{
		Renderer->ChangeAnimation("Koopa_RightMove");
		return;
	}
}

void AKoopa::FireStart()
{
	HorizonVelocityVector = FVector::Zero;
	FVector BulletInitPosVal = FVector::Zero;

	NewBullet = GetWorld()->SpawnActor<AKoopaBullet>(static_cast<int>(EActorType::Bullet));
	
	switch (ActorDir)
	{
	case EActorDir::Left:
	{
		BulletInitPosVal = FVector::Left;
		Renderer->ChangeAnimation("Koopa_LeftFire");
		NewBullet->SetBulletDir(FVector::Left);
		break;
	}
	case EActorDir::Right:
	{
		BulletInitPosVal = FVector::Right;
		Renderer->ChangeAnimation("Koopa_RightFire");
		NewBullet->SetBulletDir(FVector::Right);
		break;
	}
	default:
		break;
	}

	NewBullet->SetActorLocation({ GetActorLocation().iX() + BulletInitPosVal.iX() * (BodyCollision->GetTransform().GetScale().ihX() + static_cast<int>(UInGameValue::KoopaBulletXColScale / 2))
		,GetActorLocation().iY() - BodyCollision->GetTransform().GetScale().ihY()});
	Bullets.push_back(NewBullet);
}

void AKoopa::FallDownStart()
{
	// 죽는 발 동동 애니메이션 실행
	SetGravityZero();
	SetJumpZero();
	SetSpeedZero();

	Renderer->ChangeAnimation("Koopa_DeadMotion");
}


void AKoopa::FallDown(float _DeltaTime)
{
	if (false == FallingDown && true == ACastleBridge::IsBridgeDissapear())
	{
		Renderer->ChangeAnimation("Koopa_FallDown");
		FallingDown = true;
	}

	if (true == FallingDown)
	{
		ResultMovementUpdate(_DeltaTime);
	}
}


void AKoopa::Fire(float _DeltaTime)
{
	FiringTime -= _DeltaTime;

	ChangeAnimationInPlayerDir();
	ResultMovementUpdate(_DeltaTime);

	CheckScopeOfActivity();

	if (0.0f >= FiringTime)
	{
		NewBullet->ThrowBullet();
		FiringTime = 0.5f + FiringTime;
		StateChange(EActorState::Move);
		return;
	}
}

void AKoopa::Move(float _DeltaTime)
{
	MoveTime -= _DeltaTime;
	FireDelayTime -= _DeltaTime;

	ChangeAnimationInPlayerDir();
	ResultMovementUpdate(_DeltaTime);

	CheckScopeOfActivity();

	if (0.0f >= FireDelayTime)
	{
		FireDelayTime = 3.0f + FireDelayTime;
		StateChange(EActorState::Fire);
		return;
	}

	if (0.0f >= MoveTime)
	{
		MoveTime = 1.0f + MoveTime;
		StateChange(EActorState::Jump);
		return;
	}
}

void AKoopa::Jump(float _DeltaTime)
{
	ChangeAnimationInPlayerDir();
	ResultMovementUpdate(_DeltaTime);

	CheckScopeOfActivity();

	std::vector<UCollision*> Result = std::vector<UCollision*>();

	if (true == FootCollision->CollisionCheck(ECollisionOrder::BlockTop, Result))
	{
		StateChange(EActorState::Move);
		return;
	}
}

void AKoopa::CollisionCheck()
{


	if (true == ACastleBridge::PlayerIsTagBridgeFlag())
	{
		if (true == Dying)
		{
			return;
		}

		Dying = true;
		StateChange(EActorState::FallDown);
		return;
	}

	std::vector<UCollision*> Result = std::vector<UCollision*>();

	if (true == BodyCollision->CollisionCheck(ECollisionOrder::Player, Result))
	{
		GetPlayer()->StateChange(EActorState::GetHit);
		return;
	}
}

EActorDir AKoopa::DirCheckAndSet()
{
	EActorDir Dir = EActorDir::None;

	FVector PlayerPos = GetPlayer()->GetActorLocation();
	FVector KoopaPos = GetActorLocation();
	FVector KoopaDirOriginVec = PlayerPos - KoopaPos;

	if (KoopaDirOriginVec.X <= 0.0f)
	{
		Dir = EActorDir::Left;
	}
	else if (KoopaDirOriginVec.X > 0.0f)
	{
		Dir = EActorDir::Right;
	}

	return Dir;
}

void AKoopa::ChangeAnimationInPlayerDir()
{
	EActorDir CurDir = ActorDir;
	ActorDir = DirCheckAndSet();

	if (ActorDir != CurDir)
	{
		if (EActorDir::Left == ActorDir)
		{
			Renderer->ChangeAnimation("Koopa_LeftMove");
			return;
		}

		if (EActorDir::Right == ActorDir)
		{
			Renderer->ChangeAnimation("Koopa_RightMove");
			return;
		}
	}
}

void AKoopa::CheckScopeOfActivity()
{
	if (GetActorLocation().iX() <= InitPos.iX() - UInGameValue::KoopaMoveDeadline_F)
	{
		ActorMoveDir = FVector::Right;
		HorizonVelocityVector = ActorMoveDir * KoopaSpeed;
		AddActorLocation(FVector::Right * 4);
	}
	else if (GetActorLocation().iX() >= InitPos.iX() + UInGameValue::KoopaMoveDeadline_R)
	{
		ActorMoveDir = FVector::Left;
		HorizonVelocityVector = ActorMoveDir * KoopaSpeed;
		AddActorLocation(FVector::Left * 4);
	}
}

void AKoopa::BulletListReleaseUpdate()
{
	std::list<AKoopaBullet*>::iterator StartIter = Bullets.begin();
	std::list<AKoopaBullet*>::iterator EndIter = Bullets.end();

	for (; StartIter != EndIter; )
	{
		AKoopaBullet* Bullet = *StartIter;

		if (nullptr == Bullet)
		{
			MsgBoxAssert("KoopaBullet이 nullptr 입니다.");
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