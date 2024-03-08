#include "Koopa.h"

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
	AMonsterUnit::MoveStart();

	HorizonVelocityVector = ActorMoveDir * 100.0f;

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

void AKoopa::Move(float _DeltaTime)
{
	ChangeAnimationInPlayerDir();
	ResultMovementUpdate(_DeltaTime);

	if (GetActorLocation().iX() <= InitPos.iX() - UInGameValue::KoopaMoveDeadline_F)
	{
		ActorMoveDir = FVector::Right;
		AddActorLocation(FVector::Right * 4);
		StateChange(EActorState::Idle);
	}
	else if (GetActorLocation().iX() >= InitPos.iX() + UInGameValue::KoopaMoveDeadline_R)
	{
		ActorMoveDir = FVector::Left;
		AddActorLocation(FVector::Left * 4);
		StateChange(EActorState::Idle);
	}
}

void AKoopa::Idle(float _DeltaTime)
{
	StateChange(EActorState::Move);
}

void AKoopa::CollisionCheck()
{
	
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