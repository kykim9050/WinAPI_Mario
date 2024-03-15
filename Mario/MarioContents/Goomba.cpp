#include "Goomba.h"
#include "PlayerMario.h"



AGoomba::AGoomba()
{
	GravityVelocityVector = FVector::Down * 500.0f;
	HorizonVelocityVector = ActorMoveDir * 50.0f;
	SetScore(100);
}

AGoomba::~AGoomba()
{
}

void AGoomba::BeginPlay()
{
	AMonsterUnit::BeginPlay();

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


	FootCollision = CreateCollision(ECollisionOrder::MonsterFootCollision);
	FootCollision->SetTransform({ { 0,0 }, {UInGameValue::GoombaBodyCollisionScaleX, UInGameValue::FootCollisionScaleY} });
	FootCollision->SetPosition({ 0, -(static_cast<int>(UInGameValue::FootCollisionScaleY / 2)) });
	FootCollision->SetColType(ECollisionType::Rect);

	SetActorState(EActorState::Idle);
}

void AGoomba::Tick(float _DeltaTime)
{
	AMonsterUnit::Tick(_DeltaTime);
}


void AGoomba::CollisionCheck()
{
	std::vector<UCollision*> Result = std::vector<UCollision*>();


	if (true == BodyCollision->CollisionCheck(ECollisionOrder::Player, Result))
	{
		float PlayerBottom = GetPlayer()->GetBodyCollision()->GetActorBaseTransform().Bottom();
		float MonsterBottom = BodyCollision->GetActorBaseTransform().Bottom();

		// 현재 몬스터의 Collision ScaleY의 반값만큼 Player의 Bottom 값이 위에 잇다면 몬스터를 밟은 것
		float OffsetYValue = BodyCollision->GetActorBaseTransform().GetScale().hY();

		// 몬스터 밟은 것
		if (PlayerBottom < MonsterBottom - OffsetYValue)
		{
			BodyCollision->Destroy();
			GetPlayer()->StateChange(EActorState::CollisionJump);
			CollisionStateChange(ECollisionState::GetHit);
			return;
		}

		// 몬스터를 밟지 않고 충돌했을 경우 (플레이어 사망)
 		GetPlayer()->StateChange(EActorState::GetHit);
		return;
	}

	if (true == BodyCollision->CollisionCheck(ECollisionOrder::AttackableMonster, Result))
	{
		// GetHit시 Collision 삭제후
		BodyCollision->Destroy();
		// 몬스터의 상태를 GetHit로 변환
		CollisionStateChange(ECollisionState::GetMonsterHit);

		return;
	}

	if (true == PlayerBulletHitCheck())
	{
		return;
	}

	if (true == IsBlockHit())
	{
		BlockHit = false;
		StateChange(EActorState::GetBlockHit);
		return;
	}
}


void AGoomba::Idle(float _DeltaTime)
{
	if (GetActorLocation().iX() - GetPlayer()->GetActorLocation().iX() < UInGameValue::ResultMainWindowXScale)
	{
		SetActorState(EActorState::Move);
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


void AGoomba::GetHitStart()
{
	USoundManager::GetInst().EffectSoundPlay("Stomp.wav");
	StateChange(EActorState::GetHit);
}

void AGoomba::GetMonsterHitStart()
{
	USoundManager::GetInst().EffectSoundPlay("CrouchMoveAttack.wav");
	JumpVelocityVector = FVector::Up * 300.0f;
	StateChange(EActorState::GetMonsterHit);
}

void AGoomba::GetHitFromMonsterStart()
{
	GiveScore(GetPlayer(), GetMonsterHitScore());
	ScoreImgOperator({ GetActorLocation().iX(), GetActorLocation().iY() - BodyCollision->GetTransform().GetScale().iY() }, GetMonsterHitScore());
}

void AGoomba::GetHitFromPlayerStart()
{
	Renderer->ChangeAnimation("Goomba_Dead");
	GiveScore(GetPlayer());
	ScoreImgOperator({ GetActorLocation().iX(), GetActorLocation().iY() - BodyCollision->GetTransform().GetScale().iY() }, GetScore());
	Destroy(1.0f);
}


void AGoomba::CalHorizonVelocityVector(float _DeltaTime)
{
	AMonsterUnit::CalHorizonVelocityVector(_DeltaTime);
}
