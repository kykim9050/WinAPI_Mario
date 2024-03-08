#include "Koopa.h"
#include "KoopaBullet.h"

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
	Renderer->CreateAnimation("Koopa_LeftMove", "Koopa_Left.png", 0, 1, 0.3f, true);
	Renderer->CreateAnimation("Koopa_RightMove", "Koopa_Right.png", 0, 1, 0.3f, true);
	Renderer->CreateAnimation("Koopa_RightFire", "Koopa_Right.png", 2, 2, 0.1f, true);
	Renderer->CreateAnimation("Koopa_LeftFire", "Koopa_Left.png", 2, 2, 0.1f, true);


	BodyCollision = CreateCollision(ECollisionOrder::Monster);
	BodyCollision->SetTransform({ { 0,0 }, { UInGameValue::KoopaBodyCollisionScaleX, UInGameValue::KoopaBodyCollisionScaleY} });
	BodyCollision->SetPosition({ 0, -(BodyCollision->GetTransform().GetScale().ihY()) });
	BodyCollision->SetColType(ECollisionType::Rect);

	SetActorState(EActorState::FirstInit);

}

void AKoopa::Tick(float _DeltaTime)
{
	AMonsterUnit::Tick(_DeltaTime);
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
		break;
	}
	case EActorDir::Right:
	{
		BulletInitPosVal = FVector::Right;
		Renderer->ChangeAnimation("Koopa_RightFire");
		break;
	}
	default:
		break;
	}

	NewBullet->SetActorLocation({ GetActorLocation().iX() + BulletInitPosVal.iX() * (BodyCollision->GetTransform().GetScale().ihX() + static_cast<int>(UInGameValue::KoopaBulletXColScale / 2))
		,GetActorLocation().iY() - BodyCollision->GetTransform().GetScale().ihY()});
	Bullets.push_back(NewBullet);

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

	if (true == BodyCollision->CollisionCheck(ECollisionOrder::BlockTop, Result))
	{
		StateChange(EActorState::Move);
		return;
	}
}

void AKoopa::CollisionCheck()
{
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