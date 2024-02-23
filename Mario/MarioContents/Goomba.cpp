#include "Goomba.h"
#include "PlayerMario.h"

AGoomba::AGoomba()
{
	GravityVelocityVector = FVector::Down * 500.0f;
	HorizonVelocityVector = ActorMoveDir * 50.0f;
}

AGoomba::~AGoomba()
{
}

void AGoomba::BeginPlay()
{
	UMonsterUnit::BeginPlay();

	Renderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::Monster));
	Renderer->SetImage("Goomba.png");

	FVector GoombaScale = Renderer->GetImage()->GetScale();

	Renderer->SetTransform({ {0,0}, {GoombaScale.iX() / UInGameValue::GoombaImageXValue * UInGameValue::WindowSizeMulValue, GoombaScale.iY() / UInGameValue::GoombaImageYValue * UInGameValue::WindowSizeMulValue} });
	Renderer->CreateAnimation("Goomba_Move", "Goomba.png", 0, 1, 0.2f, true);
	Renderer->CreateAnimation("Goomba_Dead", "Goomba.png", 2, 2, 0.1f, true);
	Renderer->ChangeAnimation("Goomba_Move");


	BodyCollision = CreateCollision(ECollisionOrder::Monster);
	BodyCollision->SetTransform({ { 0,0 }, { UInGameValue::GoombaBodyCollisionScaleX, UInGameValue::GoombaBodyCollisionScaleY } });
	BodyCollision->SetPosition({ 0, -(BodyCollision->GetTransform().GetScale().ihY()) });
	BodyCollision->SetColType(ECollisionType::Rect);

	SetActorState(EActorState::Move);
}

void AGoomba::Tick(float _DeltaTime)
{
	UMonsterUnit::Tick(_DeltaTime);

	CollisionUpdate(_DeltaTime);

	if (ECollisionState::GetHit == ActorCollisionState)
	{
		return;
	}

	StateUpdate(_DeltaTime);
}

void AGoomba::StateUpdate(float _DeltaTime)
{
	switch (ActorState)
	{
	/*case EPlayerState::Idle:
		Idle(_DeltaTime);
		break;*/
	case EActorState::Move:
		Move(_DeltaTime);
		break;
	case EActorState::GetMonsterHit:
		GetMonsterHit(_DeltaTime);
		break;
	case EActorState::GetHit:
	default:
		break;
	}

}

void AGoomba::CollisionUpdate(float _DeltaTime)
{
	CollisionCheck();
}

void AGoomba::CollisionCheck()
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

		// 몬스터 밟은 것
		if (PlayerBottom < MonsterBottom - OffsetYValue)
		{
			BodyCollision->Destroy();

			Player->StateChange(EActorState::CollisionJump);

			CollisionStateChange(ECollisionState::GetHit);

			return;
		}

		// 몬스터를 밟지 않고 충돌했을 경우 (플레이어 사망)
		Player->StateChange(EActorState::GetHit);
		// 플레이어를 한번 죽였다.
		KillPlayer = true;
		return;
	}

	if (false == KillPlayer && true == BodyCollision->CollisionCheck(ECollisionOrder::AttackableMonster, Result))
	{
		--Life;

		// GetHit시 Collision 삭제후
		BodyCollision->Destroy();

		// 몬스터의 상태를 GetHit로 변환
		CollisionStateChange(ECollisionState::GetMonsterHit);

		return;
	}
}


void AGoomba::Move(float _DeltaTime)
{
	CalHorizonVelocityVector(_DeltaTime);
	HorizonVelocityVector = ActorMoveDir * 50.0f;
	ResultMovementUpdate(_DeltaTime);
}

void AGoomba::GetMonsterHit(float _DeltaTime)
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

void AGoomba::ResultMovementUpdate(float _DeltaTime)
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


void AGoomba::CollisionStateChange(ECollisionState _CollisionState)
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

void AGoomba::GetHitStart()
{
	StateChange(EActorState::GetHit);
	--Life;
}

void AGoomba::GetMonsterHitStart()
{
	JumpVelocityVector = FVector::Up * 300.0f;
	StateChange(EActorState::GetMonsterHit);
}

void AGoomba::GetHitFromMonsterStart()
{

}

void AGoomba::GetHitFromPlayerStart()
{
	Renderer->ChangeAnimation("Goomba_Dead");
	Destroy(1.0f);
}

void AGoomba::StateChange(EActorState _ActorState)
{
	if (ActorState != _ActorState)
	{
		switch (_ActorState)
		{
		case EActorState::GetHit:
			GetHitFromPlayerStart();
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

void AGoomba::CalHorizonVelocityVector(float _DeltaTime)
{
	UMonsterUnit::CalHorizonVelocityVector(_DeltaTime);
}
