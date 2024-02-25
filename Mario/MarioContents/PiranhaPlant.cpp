#include "PiranhaPlant.h"

APiranhaPlant::APiranhaPlant()
{
	ActorMoveDir = FVector::Up;
	Life = 1;
}

APiranhaPlant::~APiranhaPlant()
{
}

void APiranhaPlant::BeginPlay()
{
	AMonsterUnit::BeginPlay();

	Renderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::Monster));
	Renderer->SetImage("PiranhaPlant.png");

	FVector PiranhaPlantScale = Renderer->GetImage()->GetScale();

	Renderer->SetTransform({ {0,0}, {PiranhaPlantScale.iX() / UInGameValue::PiranhaPlantImageXValue * UInGameValue::WindowSizeMulValue, PiranhaPlantScale.iY() / UInGameValue::PiranhaPlantImageYValue * UInGameValue::WindowSizeMulValue} });
	Renderer->CreateAnimation("PiranhaPlant_Move", "PiranhaPlant.png", 0, 1, 0.2f, true);
	Renderer->ChangeAnimation("PiranhaPlant_Move");

	BodyCollision = CreateCollision(ECollisionOrder::Monster);
	BodyCollision->SetTransform({ { 0,0 }, { UInGameValue::PiranhaPlantBodyCollisionScaleX, UInGameValue::PiranhaPlantBodyCollisionScaleY} });
	BodyCollision->SetPosition({ 0, -(BodyCollision->GetTransform().GetScale().ihY()) });
	BodyCollision->SetColType(ECollisionType::Rect);

	SetActorState(EActorState::FirstInit);
}

void APiranhaPlant::Tick(float _DeltaTime)
{
	AMonsterUnit::Tick(_DeltaTime);

	CollisionUpdate(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void APiranhaPlant::StateUpdate(float _DeltaTime)
{
	switch (ActorState)
	{
	case EActorState::FirstInit:
		FirstInit(_DeltaTime);
		break;
	case EActorState::Idle:
		Idle(_DeltaTime);
		break;
	case EActorState::Move:
		Move(_DeltaTime);
		break;
	default:
		break;
	}
}

void APiranhaPlant::StateChange(EActorState _ActorState)
{
	if (ActorState != _ActorState)
	{
		switch (_ActorState)
		{
		case EActorState::Idle:
			IdleStart();
			break;
		case EActorState::Move:
			MoveStart();
			break;
		default:
			break;
		}
	}
	SetActorState(_ActorState);
}


void APiranhaPlant::CollisionUpdate(float _DeltaTime)
{
	CollisionCheck();
}

void APiranhaPlant::CollisionCheck()
{
	std::vector<UCollision*> Result = std::vector<UCollision*>();

	APlayerMario* Player = APlayerMario::GetMainPlayer();

	if (nullptr == Player)
	{
		MsgBoxAssert("플레이어가 존재하지 않습니다.");
	}

	if (false == KillPlayer && true == BodyCollision->CollisionCheck(ECollisionOrder::Player, Result))
	{
		Player->StateChange(EActorState::GetHit);
		// 플레이어를 죽였다.
		KillPlayer = true;
		return;
	}

}




void APiranhaPlant::IdleStart()
{
	JumpVelocityVector = FVector::Zero;
}

void APiranhaPlant::MoveStart()
{
	ActorMoveDir *= -1;
	JumpVelocityVector = ActorMoveDir * 50.0f;
}


void APiranhaPlant::FirstInit(float _Deltatime)
{
	InitYPos = GetActorLocation().Y;
	StateChange(EActorState::Idle);
}

void APiranhaPlant::Idle(float _DeltaTime)
{
	IdleDelayTime -= _DeltaTime;
	
	if (0.0f >= IdleDelayTime)
	{
		StateChange(EActorState::Move);
		IdleDelayTime = 1.0f;
	}
}

void APiranhaPlant::Move(float _DeltaTime)
{
	ResultMovementUpdate(_DeltaTime);

	if (GetActorLocation().Y <= InitYPos - static_cast<float>(UInGameValue::PiranhaPlantBodyCollisionScaleY))
	{
		StateChange(EActorState::Idle);
	}
	else if(GetActorLocation().Y >= InitYPos + static_cast<float>(UInGameValue::PiranhaPlantBodyCollisionScaleY))
	{
		StateChange(EActorState::Idle);
	}

}

void APiranhaPlant::ResultMovementUpdate(float _DeltaTime)
{
	CalTotalVelocityVector(_DeltaTime);
	AddActorLocation(TotalVelocityVector * _DeltaTime);
}