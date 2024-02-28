#include "BlockUnit.h"

ABlockUnit::ABlockUnit()
{
}

ABlockUnit::~ABlockUnit()
{
}

void ABlockUnit::BeginPlay()
{
	UStateUnit::BeginPlay();

	SideCollision = CreateCollision(ECollisionOrder::Block);
	SideCollision->SetTransform({ { 0, 0 }, { UInGameValue::BlockCollisionScaleX, UInGameValue::BlockCollisionScaleY - SideColYoffset} });
	SideCollision->SetColType(ECollisionType::Rect);

	TopCollision = CreateCollision(ECollisionOrder::Block);
	TopCollision->SetTransform({ { ColInitXPos, -ColInitYPos }, { UInGameValue::BlockCollisionScaleX, UInGameValue::BlockCollisionScaleY - ColYoffset} });
	TopCollision->SetColType(ECollisionType::Rect);

	BodyCollision = CreateCollision(ECollisionOrder::CollisionBlock);
	BodyCollision->SetTransform({ { ColInitXPos, ColInitYPos }, { UInGameValue::BlockCollisionScaleX, UInGameValue::BlockCollisionScaleY - ColYoffset} });
	BodyCollision->SetColType(ECollisionType::Rect);
}

void ABlockUnit::Tick(float _DeltaTime)
{
	UStateUnit::Tick(_DeltaTime);
}


void ABlockUnit::CollisionStateChange(ECollisionState _CollisionState)
{
	if (ActorCollisionState != _CollisionState)
	{
		switch (_CollisionState)
		{
		case ECollisionState::GetHit:
			GetHitStart();
			break;
		default:
			break;
		}
	}

	SetCollisionState(_CollisionState);
}

void ABlockUnit::FirstInit(float _Deltatime)
{
	InitPos = GetActorLocation();
	StateChange(EActorState::Idle);
}

void ABlockUnit::ResultMovementUpdate(float _DeltaTime)
{
	GravityVelocityVector += GravityAccVector * _DeltaTime;
	CalTotalVelocityVector(_DeltaTime);
	AddActorLocation(TotalVelocityVector * _DeltaTime);
}

void ABlockUnit::StateUpdate(float _DeltaTime)
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
	case EActorState::Fixed:
		Fixed(_DeltaTime);
		break;
	default:
		break;
	}
}

void ABlockUnit::StateChange(EActorState _ActorState)
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
		case EActorState::Fixed:
			FixedStart();
			break;
		default:
			break;
		}
	}

	SetActorState(_ActorState);
}



void ABlockUnit::CollisionCheck()
{
	std::vector<UCollision*> Result = std::vector<UCollision*>();

	APlayerMario* Player = APlayerMario::GetMainPlayer();

	if (nullptr == Player)
	{
		MsgBoxAssert("플레이어가 존재하지 않습니다.");
	}

	//// Block의 바닥과 Player의 충돌일 때
	//if (true == BodyCollision->CollisionCheck(ECollisionOrder::Player, Result))
	//{
	//	const FTransform& PlayerColTrans = Player->GetBodyCollision()->GetActorBaseTransform();
	//	const FTransform& BlockColTrans = BodyCollision->GetActorBaseTransform();


	//	if (PlayerColTrans.GetPosition().X < BlockColTrans.Right() && PlayerColTrans.GetPosition().X > BlockColTrans.Left() && PlayerColTrans.GetPosition().Y < BlockColTrans.Bottom())
	//	{
	//		//UEngineDebug::OutPutDebugText("Occur Block Bot Collision");
	//		Player->CollisionStateChange(ECollisionState::BlockBotHit);

	//		CollisionStateChange(ECollisionState::GetHit);
	//		return;
	//	}
	//}

	//// Block의 측면과 Player의 충돌일 때
	//if (true == SideCollision->CollisionCheck(ECollisionOrder::Player, Result))
	//{
	//	const FTransform& PlayerColTrans = Player->GetBodyCollision()->GetActorBaseTransform();
	//	const FTransform& BlockColTrans = SideCollision->GetActorBaseTransform();

	//	if (PlayerColTrans.GetPosition().X < BlockColTrans.Left() || PlayerColTrans.GetPosition().X > BlockColTrans.Right())
	//	{
	//		UEngineDebug::OutPutDebugText("Occur Block Side Collision");
	//		Player->CollisionStateChange(ECollisionState::BlockSideHit);
	//		return;
	//	}
	//}

	// Block의 Top과 Player의 충돌일 때
	if (true == TopCollision->CollisionCheck(ECollisionOrder::Player, Result))
	{
		const FTransform& PlayerColTrans = Player->GetBodyCollision()->GetActorBaseTransform();
		const FTransform& BlockColTrans = TopCollision->GetActorBaseTransform();

		if (
			PlayerColTrans.GetPosition().X > BlockColTrans.Left() && PlayerColTrans.GetPosition().X < BlockColTrans.Right() &&
			PlayerColTrans.GetPosition().Y < BlockColTrans.Top())
		{
			//UEngineDebug::OutPutDebugText("Occur Block Top Collision");
			//Player->CollisionStateChange(ECollisionState::BlockTopHit);
			Player->StateChange(EActorState::Idle);
			return;
		}

	}

	Player->CollisionStateChange(ECollisionState::None);
	CollisionStateChange(ECollisionState::None);
}

void ABlockUnit::GetHitStart()
{
	if (EActorState::Fixed == ActorState)
	{
		return;
	}

	StateChange(EActorState::Move);
}



void ABlockUnit::MoveStart()
{
	JumpVelocityVector = FVector::Up * 200.0f;
}

void ABlockUnit::FixedStart()
{
	/*SetJumpZero();
	SetGravityZero();*/
}

void ABlockUnit::Idle(float _DeltaTime)
{

}

void ABlockUnit::Move(float _DeltaTime)
{
	ResultMovementUpdate(_DeltaTime);
}

void ABlockUnit::Fixed(float _DeltaTime)
{
	/*CalTotalVelocityVector(_DeltaTime);
	AddActorLocation(TotalVelocityVector * _DeltaTime);*/
}