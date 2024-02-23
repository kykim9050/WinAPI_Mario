#include "KoopaTroopa.h"
#include "PlayerMario.h"

AKoopaTroopa::AKoopaTroopa()
{
	GravityVelocityVector = FVector::Down * 500.0f;
	HorizonVelocityVector = ActorMoveDir * 50.0f;
	Life = 3;
}

AKoopaTroopa::~AKoopaTroopa()
{
}

void AKoopaTroopa::BeginPlay()
{
	UMonsterUnit::BeginPlay();

	Renderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::Monster));
	Renderer->SetImage("KoopaTroopa_Left.png");

	FVector KoopaTroopaScale = Renderer->GetImage()->GetScale();

	Renderer->SetTransform({ {0,0}, {KoopaTroopaScale.iX() / UInGameValue::KoopaTroopaImageXValue * UInGameValue::WindowSizeMulValue, KoopaTroopaScale.iY() / UInGameValue::KoopaTroopaImageYValue * UInGameValue::WindowSizeMulValue} });
	Renderer->CreateAnimation("KoopaTroopa_Move_Right", "KoopaTroopa_Right.png", 0, 1, 0.3f, true);
	Renderer->CreateAnimation("KoopaTroopa_Move_Left", "KoopaTroopa_Left.png", 0, 1, 0.3f, true);
	Renderer->CreateAnimation("KoopaTroopa_OneHit", "KoopaTroopa_Left.png", 5, 5, 0.1f, true);
	Renderer->CreateAnimation("KoopaTroopa_TwoHit", "KoopaTroopa_Left.png", 4, 4, 0.1f, true);

	Renderer->ChangeAnimation("KoopaTroopa_Move_Left");


	BodyCollision = CreateCollision(ECollisionOrder::Monster);
	BodyCollision->SetTransform({ { 0,0 }, { UInGameValue::KoopaTroopaBodyCollisionScaleX, UInGameValue::KoopaTroopaBodyCollisionScaleY} });
	BodyCollision->SetPosition({ 0, -(BodyCollision->GetTransform().GetScale().ihY()) });
	BodyCollision->SetColType(ECollisionType::Rect);

	SetActorState(EActorState::Move);
}

void AKoopaTroopa::Tick(float _DeltaTime)
{
	UMonsterUnit::Tick(_DeltaTime);

	CollisionUpdate(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void AKoopaTroopa::StateUpdate(float _DeltaTime)
{
	switch (ActorState)
	{
		/*case EPlayerState::Idle:
			Idle(_DeltaTime);
			break;*/
	case EActorState::Move:
		Move(_DeltaTime);
		break;
	case EActorState::GetFirstHit:
		GetFirstHit(_DeltaTime);
		break;
	case EActorState::GetSecondHit:
		GetSecondHit(_DeltaTime);
		break;
	case EActorState::GetMonsterHit:
		GetMonsterHit(_DeltaTime);
		break;
	default:
		break;
	}

}

void AKoopaTroopa::Move(float _DeltaTime)
{
	CalHorizonVelocityVector(_DeltaTime);
	ResultMovementUpdate(_DeltaTime);
}

void AKoopaTroopa::GetFirstHit(float _DeltaTime)
{
	HorizonVelocityVector = FVector::Zero;
	ResultMovementUpdate(_DeltaTime);
}

void AKoopaTroopa::GetSecondHit(float _DeltaTime)
{
	CalHorizonVelocityVector(_DeltaTime);
	HorizonVelocityVector = ActorMoveDir * 500.0f;
	ResultMovementUpdate(_DeltaTime);
}

void AKoopaTroopa::GetMonsterHit(float _DeltaTime)
{
	GravityVelocityVector += GravityAccVector * _DeltaTime;

	TotalVelocityVector = FVector::Zero;
	TotalVelocityVector = TotalVelocityVector + GravityVelocityVector + JumpVelocityVector;

	AddActorLocation(TotalVelocityVector * _DeltaTime);

	if (900.0f <= GetActorLocation().Y)
	{
		StateChange(EActorState::Dead);
	}
}

void AKoopaTroopa::CalHorizonVelocityVector(float _DeltaTime)
{
	UMonsterUnit::CalHorizonVelocityVector(_DeltaTime);
}

void AKoopaTroopa::ResultMovementUpdate(float _DeltaTime)
{
	Color8Bit Color = UContentsFunction::GetCollisionMapImg()->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), UInGameValue::CollisionColor);

	if (UInGameValue::CollisionColor == Color)
	{
		GravityVelocityVector = FVector::Zero;
	}

	TotalVelocityVector = FVector::Zero;
	TotalVelocityVector = TotalVelocityVector + GravityVelocityVector + HorizonVelocityVector;
	AddActorLocation(TotalVelocityVector * _DeltaTime);
}




void AKoopaTroopa::StateChange(EActorState _ActorState)
{
	if (ActorState != _ActorState)
	{
		switch (_ActorState)
		{
		case EActorState::GetFirstHit:
			GetFirstHitStart();
			break;
		case EActorState::GetSecondHit:
			GetSecondHitStart();
			break;
		case EActorState::GetMonsterHit:
			GetHitFromMonsterStart();
			break;
		case EActorState::Dead:
			Destroy();
			return;
		default:
			break;
		}
	}

	SetActorState(_ActorState);
}

void AKoopaTroopa::GetFirstHitStart()
{
	Renderer->ChangeAnimation("KoopaTroopa_OneHit");
}

void AKoopaTroopa::GetSecondHitStart()
{
	SetDirAfterCollision(GetActorLocation(), APlayerMario::GetMainPlayer()->GetActorLocation());
	Renderer->ChangeAnimation("KoopaTroopa_TwoHit");
}

void AKoopaTroopa::GetHitFromMonsterStart()
{

}

void AKoopaTroopa::SetDirAfterCollision(const FVector _MyFVector, const FVector _OtherFVector)
{
	if (_MyFVector.X < _OtherFVector.X)
	{
		ActorMoveDir = FVector::Left;
		ActorDir = EActorDir::Left;
		return;
	}

	if (_MyFVector.X > _OtherFVector.X)
	{
		ActorMoveDir = FVector::Right;
		ActorDir = EActorDir::Right;
		return;
	}

	ActorMoveDir = FVector::Zero;
	ActorDir = EActorDir::None;
	return;
}





void AKoopaTroopa::CollisionUpdate(float _DeltaTime)
{
	CollisionCheck();
}

void AKoopaTroopa::CollisionCheck()
{
	std::vector<UCollision*> Result = std::vector<UCollision*>();

	APlayerMario* Player = APlayerMario::GetMainPlayer();

	if (nullptr == Player)
	{
		MsgBoxAssert("플레이어가 존재하지 않습니다.");
	}

	if (false == KillPlayer && true == BodyCollision->CollisionCheck(ECollisionOrder::Player, Result))
	{
		float PlayerBottom = Player->GetBodyCollision()->GetActorBaseTransform().Bottom();
		float MonsterBottom = BodyCollision->GetActorBaseTransform().Bottom();

		// 현재 몬스터의 Collision ScaleY의 반값만큼 Player의 Bottom 값이 위에 잇다면 몬스터를 밟은 것
		float OffsetYValue = BodyCollision->GetActorBaseTransform().GetScale().hY();

		// 몬스터의 머리를 맞았을때 실행하는 경우
		if (PlayerBottom < MonsterBottom - OffsetYValue)
		{
			Player->StateChange(EActorState::CollisionJump);

			CollisionStateChange(ECollisionState::GetHit);

			return;
		}

		// 엉금엉금의 머리위가 아닌 곳에서 충돌이 일어났을 때
		switch (Life)
		{
		case 1:
		case 3:
		{
			// KoopaTroopa가 살아있을 때 혹은 등껍질로 날라다닐때 충돌의 경우
			// 이때는 플레이어 사망해야 함
			Player->StateChange(EActorState::GetHit);
			// 플레이어를 죽였다.
			KillPlayer = true;
			break;
		}
		case 2:
		{
			CollisionStateChange(ECollisionState::GetHit);
			break;
		}
		default:
			break;
		}

		return;
	}
	
	// 만약 엉금엉금이 굴러다닐때 충돌하면 충돌로 인지
	if (false == KillPlayer && true == BodyCollision->CollisionCheck(ECollisionOrder::AttackableMonster, Result))
	{
		// GetHit시 Collision 삭제후
		BodyCollision->Destroy();

		CollisionStateChange(ECollisionState::GetMonsterHit);
		return;
	}

	//UEngineDebug::OutPutDebugText(std::to_string(Life));
	CollisionStateChange(ECollisionState::None);
}

void AKoopaTroopa::CollisionStateChange(ECollisionState _CollisionState)
{
	if (ActorCollisionState != _CollisionState)
	{
		switch (_CollisionState)
		{
		case ECollisionState::Hit:
			//HitStart();
			break;
		case ECollisionState::GetHit:
			GetHitStart();
			break;
		case ECollisionState::GetMonsterHit:
			GetMonsterHitStart();
			break;
		default:
			break;
		}
	}

	SetCollisionState(_CollisionState);
}

void AKoopaTroopa::GetHitStart()
{
	//UEngineDebug::OutPutDebugText("GetHitStart");

	switch (Life)
	{
	case 3: // Life가 3인데 플레이어한테 머리 한방 맞았을 때
	{
		StateChange(EActorState::GetFirstHit);
		--Life;
		break;
	}
	case 2:	// Life가 2일 때 -> 플레이어한테 한방 맞은 후에 또 맞았을 때 (밀거나 머리 맞거나하는 행동 취할 수 있음)
	{
		// GetSecondHit상태에서는 다른 몬스터, 플레이어 전부다 죽일 수 있음 (다른 몬스터들은 Koopatroopa의 충돌을 체크해야 함)
		StateChange(EActorState::GetSecondHit);

		// 다른 몬스터들도 죽일 수 있도록 Order를 ECollisionOrder::AttackableMonster로 변경
		BodyCollision->SetOrder(static_cast<int>(ECollisionOrder::AttackableMonster));
		--Life;
		break;
	}
	default:
	{
		Life = 1;
		break;
	}
	}

}

void AKoopaTroopa::GetMonsterHitStart()
{
	JumpVelocityVector = FVector::Up * 300.0f;
	StateChange(EActorState::GetMonsterHit);
}







