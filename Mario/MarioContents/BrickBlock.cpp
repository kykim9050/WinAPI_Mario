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

	BodyCollision = CreateCollision(ECollisionOrder::Block);
	BodyCollision->SetTransform({ { 0,0 }, { UInGameValue::BlockCollisionScaleX, UInGameValue::BlockCollisionScaleY} });
	BodyCollision->SetColType(ECollisionType::Rect);

	SetActorState(EActorState::FirstInit);
}

void ABrickBlock::Tick(float _DeltaTime)
{
	ABlockUnit::Tick(_DeltaTime);
}

//void ABrickBlock::StateUpdate(float _DeltaTime)
//{
//	ABlockUnit::StateUpdate(_DeltaTime);
//
//	switch (ActorState)
//	{
//	case EActorState::FirstInit:
//		FirstInit(_DeltaTime);
//		break;
//	case EActorState::Idle:
//		Idle(_DeltaTime);
//		break;
//	case EActorState::Move:
//		Move(_DeltaTime);
//		break;
//	default:
//		break;
//	}
//}
//
//void ABrickBlock::StateChange(EActorState _ActorState)
//{
//	ABlockUnit::StateChange(_ActorState);
//
//	if (ActorState != _ActorState)
//	{
//		switch (_ActorState)
//		{
//		case EActorState::Idle:
//			IdleStart();
//			break;
//		case EActorState::Move:
//			MoveStart();
//			break;
//		default:
//			break;
//		}
//	}
//
//	SetActorState(_ActorState);
//}
//
//
//
//void ABrickBlock::CollisionCheck()
//{
//	ABlockUnit::CollisionCheck();
//
//	std::vector<UCollision*> Result = std::vector<UCollision*>();
//
//	APlayerMario* Player = APlayerMario::GetMainPlayer();
//
//	if (nullptr == Player)
//	{
//		MsgBoxAssert("플레이어가 존재하지 않습니다.");
//	}
//
//	if (true == BodyCollision->CollisionCheck(ECollisionOrder::Player, Result))
//	{
//		const FTransform& PlayerColTrans = Player->GetBodyCollision()->GetActorBaseTransform();
//		const FTransform& BlockColTrans = BodyCollision->GetActorBaseTransform();
//
//		if (PlayerColTrans.GetPosition().X <= BlockColTrans.Right() && PlayerColTrans.GetPosition().X >= BlockColTrans.Left() && PlayerColTrans.Top() < BlockColTrans.Bottom())
//		{
//			Player->SetJumpZero();
//			Player->SetGravityZero();
//			CollisionStateChange(ECollisionState::GetHit);
//			return;
//		}
//		
//		return;
//	}
//
//	CollisionStateChange(ECollisionState::None);
//}
//
//void ABrickBlock::CollisionStateChange(ECollisionState _CollisionState)
//{
//	ABlockUnit::CollisionStateChange(_CollisionState);
//}
//
//void ABrickBlock::GetHitStart()
//{
//	ABlockUnit::GetHitStart();
//	StateChange(EActorState::Move);
//}
//
//
//
//
//
//void ABrickBlock::IdleStart()
//{
//	ABlockUnit::IdleStart();
//	Renderer->ChangeAnimation("BrickBlock_Init");
//}
//
//void ABrickBlock::MoveStart()
//{
//	ABlockUnit::MoveStart();
//
//	JumpVelocityVector = FVector::Up * 400.0f;
//	Renderer->ChangeAnimation("BrickBlock_EmptyHit");
//}
//
//void ABrickBlock::Idle(float _DeltaTime)
//{
//	ABlockUnit::Idle(_DeltaTime);
//}
//
//void ABrickBlock::Move(float _DeltaTime)
//{
//	ResultMovementUpdate(_DeltaTime);
//
//	if (GetActorLocation().Y >= InitPos.Y)
//	{
//		GravityVelocityVector = FVector::Zero;
//		JumpVelocityVector = FVector::Zero;
//		SetActorLocation(InitPos);
//		StateChange(EActorState::Idle);
//	}
//}




