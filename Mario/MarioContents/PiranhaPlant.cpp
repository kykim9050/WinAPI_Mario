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
}


void APiranhaPlant::CollisionCheck()
{
	std::vector<UCollision*> Result = std::vector<UCollision*>();

	if (true == BodyCollision->CollisionCheck(ECollisionOrder::Player, Result))
	{
		GetPlayer()->StateChange(EActorState::GetHit);
		return;
	}

	if (true == PlayerBulletHitCheck())
	{
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
	InitPos = GetActorLocation();
	StateChange(EActorState::Idle);
}

void APiranhaPlant::Idle(float _DeltaTime)
{
	IdleDelayTime -= _DeltaTime;
	
	if (0.0f >= IdleDelayTime)
	{
		IdleDelayTime = 1.0f;
		StateChange(EActorState::Move);
		return;
	}
}

void APiranhaPlant::Move(float _DeltaTime)
{
	ResultMovementUpdate(_DeltaTime);

	if (GetActorLocation().Y <= InitPos.Y - static_cast<float>(UInGameValue::PiranhaPlantBodyCollisionScaleY))
	{
		SetActorLocation({ InitPos.X, InitPos.Y - static_cast<float>(UInGameValue::PiranhaPlantBodyCollisionScaleY) });
		StateChange(EActorState::Idle);
		return;
	}
	else if (GetActorLocation().Y >= InitPos.Y + static_cast<float>(UInGameValue::PiranhaPlantBodyCollisionScaleY))
	{
		SetActorLocation({ InitPos.X, InitPos.Y + static_cast<float>(UInGameValue::PiranhaPlantBodyCollisionScaleY) });
		StateChange(EActorState::Idle);
		return;
	}

}

void APiranhaPlant::ResultMovementUpdate(float _DeltaTime)
{
	CalTotalVelocityVector(_DeltaTime);
	AddActorLocation(TotalVelocityVector * _DeltaTime);
}

void APiranhaPlant::GetMonsterHitStart()
{
	USoundManager::GetInst().EffectSoundPlay("CrouchMoveAttack.wav");
	GiveScore(GetPlayer(), GetMonsterHitScore());
	ScoreImgOperator({ GetActorLocation().iX(), GetActorLocation().iY() - BodyCollision->GetTransform().GetScale().iY() }, GetMonsterHitScore());
	BodyCollision->ActiveOff();
	Renderer->ActiveOff();
	StateChange(EActorState::GetMonsterHit);
}

void APiranhaPlant::GetMonsterHit(float _DeltaTime)
{
	StateChange(EActorState::Dead);
}
