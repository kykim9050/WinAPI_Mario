#include "BrickBlock.h"

ABrickBlock::ABrickBlock()
{
}

ABrickBlock::~ABrickBlock()
{

}

void ABrickBlock::BeginPlay()
{
	ABlockUnit::BeginPlay();

	Renderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::Block));
	Renderer->SetImage("BrickBlock.png");

	FVector BrickBlockScale = Renderer->GetImage()->GetScale();

	Renderer->SetTransform({ {0,0}, {BrickBlockScale.iX() / UInGameValue::BrickBlockImageXValue * UInGameValue::WindowSizeMulValue, BrickBlockScale.iY() / UInGameValue::BrickBlockImageYValue * UInGameValue::WindowSizeMulValue} });
	Renderer->CreateAnimation("BrickBlock_Init", "BrickBlock.png", 0, 0, 0.1f, true);
	Renderer->CreateAnimation("BrickBlock_EmptyHit", "BrickBlock.png", 1, 1, 0.1f, true);
	Renderer->CreateAnimation("BrickBlock_Debris", "BrickBlock.png", 2, 2, 0.1f, true);
	Renderer->CreateAnimation("BrickBlock_Hit", "BrickBlock.png", 3, 3, 0.1f, true);
	Renderer->CreateAnimation("BrickBlock_AfterHit", "BrickBlock.png", 4, 4, 0.1f, true);


	SetActorState(EActorState::FirstInit);
}

void ABrickBlock::Tick(float _DeltaTime)
{
	ABlockUnit::Tick(_DeltaTime);
}

void ABrickBlock::CollisionCheck()
{
	ABlockUnit::CollisionCheck();

	std::vector<UCollision*> Result = std::vector<UCollision*>();

	// Block의 바닥과 Player의 충돌일 때
	if (true == BodyCollision->CollisionCheck(ECollisionOrder::Player, Result))
	{
		const FTransform& PlayerColTrans = GetPlayer()->GetBodyCollision()->GetActorBaseTransform();
		const FTransform& BlockColTrans = BodyCollision->GetActorBaseTransform();
		float PlayerTop = GetPlayer()->GetBodyCollision()->GetActorBaseTransform().Top();
		float BlockBotColTop = BodyCollision->GetActorBaseTransform().Top();
		float OffsetYValue = BodyCollision->GetActorBaseTransform().GetScale().hY();

		if (PlayerColTrans.GetPosition().X < BlockColTrans.Right()
			&& PlayerColTrans.GetPosition().X > BlockColTrans.Left()
			&& PlayerTop < BlockBotColTop + OffsetYValue + OffsetYValue / 2)
		{
			GetPlayer()->HitBlockBottom();

			CollisionStateChange(ECollisionState::GetHit);
			return;
		}
	}

	if (true == PlayerSideColCheck())
	{
		return;
	}

	CollisionStateChange(ECollisionState::None);
}


void ABrickBlock::IdleStart()
{
	ABlockUnit::IdleStart();
	Renderer->ChangeAnimation("BrickBlock_Init");
}

void ABrickBlock::MoveStart()
{
	ABlockUnit::MoveStart();

	Renderer->ChangeAnimation("BrickBlock_EmptyHit");
}


void ABrickBlock::Move(float _DeltaTime)
{
	ABlockUnit::Move(_DeltaTime);

	if (GetActorLocation().Y >= InitPos.Y)
	{
		GravityVelocityVector = FVector::Zero;
		JumpVelocityVector = FVector::Zero;
		SetActorLocation(InitPos);
		StateChange(EActorState::Idle);
	}
}

void ABrickBlock::Debris(float _DeltaTime)
{
	ABlockUnit::Debris(_DeltaTime);

	Debrisingtime -= _DeltaTime;

	if (0.0f >= Debrisingtime)
	{

		Debrisingtime = 0.375f;
		StateChange(EActorState::Release);
	}

	GravityVelocityVector += GravityAccVector * _DeltaTime;
	CalTotalVelocityVector(_DeltaTime);
	AddActorLocation(TotalVelocityVector * _DeltaTime);
	
	
}

void ABrickBlock::DebrisStart()
{
	ABlockUnit::DebrisStart();

	USoundManager::GetInst().EffectSoundPlay("BrickBreak.wav");

	OnTheBlockMonsterCheck();

	TopCollision->ActiveOff();
	SideCollision->ActiveOff();
	BodyCollision->ActiveOff();
	Renderer->ActiveOff();

	DebrisingRenderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::Block));
	DebrisingRenderer->SetImage("DebrisBlock.png");

	FVector DebrisBlockScale = DebrisingRenderer->GetImage()->GetScale();

	DebrisingRenderer->SetTransform({ {0,0}, {DebrisBlockScale.iX() / UInGameValue::DebrisBlockImageXValue * UInGameValue::WindowSizeMulValue, DebrisBlockScale.iY() / UInGameValue::DebrisBlockImageYValue * UInGameValue::WindowSizeMulValue} });
	DebrisingRenderer->CreateAnimation("BrickBlock_Debrising", "DebrisBlock.png", 0, 14, 0.025f, false);

	DebrisingRenderer->ChangeAnimation("BrickBlock_Debrising");
	DebrisingRenderer->ActiveOn();
	JumpVelocityVector = FVector::Up * 250.0f;

}

void ABrickBlock::FirstInit(float _Deltatime)
{
	ABlockUnit::FirstInit(_Deltatime);

	StateChange(EActorState::Idle);
}

void ABrickBlock::GetHitStart()
{
	ABlockUnit::GetHitStart();

	if (EActorState::Fixed == ActorState)
	{
		return;
	}

	EMarioType type = GetPlayer()->GetPlayerType();


	switch (type)
	{
	case EMarioType::Small:
		StateChange(EActorState::Move);
		break;
	case EMarioType::Big:
	case EMarioType::Fire:
		StateChange(EActorState::Debris);
		break;
	default:
		break;
	}


}