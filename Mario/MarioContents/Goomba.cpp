#include "Goomba.h"
#include "PlayerMario.h"

AGoomba::AGoomba()
{
}

AGoomba::~AGoomba()
{
}

void AGoomba::BeginPlay()
{
	AActor::BeginPlay();

	Renderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::Monster));
	Renderer->SetImage("Goomba.png");

	FVector GoombaScale = Renderer->GetImage()->GetScale();

	Renderer->SetTransform({ {0,0}, {GoombaScale.iX() / UInGameValue::GoombaImageXValue * UInGameValue::WindowSizeMulValue, GoombaScale.iY() / UInGameValue::GoombaImageYValue * UInGameValue::WindowSizeMulValue} });
	Renderer->CreateAnimation("Goomba_Move", "Goomba.png", 0, 1, 0.1f, true);
	Renderer->CreateAnimation("Goomba_Dead", "Goomba.png", 2, 2, 0.1f, true);
	Renderer->ChangeAnimation("Goomba_Move");


	BodyCollision = CreateCollision(ECollisionOrder::Monster);
	BodyCollision->SetTransform({ { 0,0 }, { UInGameValue::GoombaBodyCollisionScaleX, UInGameValue::GoombaBodyCollisionScaleY } });
	BodyCollision->SetPosition({ 0, -(BodyCollision->GetTransform().GetScale().ihY()) });
	BodyCollision->SetColType(ECollisionType::Rect);


	GravityVelocityVector = FVector::Down * 500.0f;
	HorizonVelocityVector = FVector::Left * 50.0f;

	SetActorState(EActorState::Move);
}

void AGoomba::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

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
	default:
		break;
	}

}

void AGoomba::Move(float _DeltaTime)
{
	ResultMovementUpdate(_DeltaTime);
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

void AGoomba::CollisionUpdate(float _DeltaTime)
{
	std::vector<UCollision*> Result = std::vector<UCollision*>();
	
	APlayerMario* Player = APlayerMario::GetMainPlayer();
	if (nullptr == Player)
	{
		MsgBoxAssert("플레이어가 존재하지 않습니다.");
	}

	if (true == BodyCollision->CollisionCheck(ECollisionOrder::Player, Result))
	{
		float PlayerBottom = Player->GetBodyCollision()->GetActorBaseTransform().Bottom();
		float MonsterBottom = BodyCollision->GetActorBaseTransform().Bottom();
		
		// 현재 몬스터의 Collision ScaleY의 반값만큼 Player의 Bottom 값이 위에 잇다면 몬스터를 밟은 것
		float OffsetYValue = BodyCollision->GetActorBaseTransform().GetScale().hY();

		// 몬스터 밟은 것
		if (PlayerBottom < MonsterBottom - OffsetYValue)
		{

			// GetHit시 Collision 삭제후
			BodyCollision->Destroy();
			// 본인도 삭제하는 함수 실행

			// 몬스터의 상태를 GetHit로 변환
			CollisionStateChange(ECollisionState::GetHit);
			
			Destroy(1.0f);

			// Player의 State에서 CollisionJump 추가해서 구현하기
			Player->StateChange(EActorState::CollisionJump);

			return;
		}

		// 몬스터를 밟지 않고 충돌했을 경우 (플레이어 사망)
		Player->CollisionStateChange(ECollisionState::GetHit);
	}

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
		default:
			break;
		}
	}

	SetCollisionState(_CollisionState);
}

void AGoomba::GetHitStart()
{
	// GetHit시 짜부 랜더링 실시
	Renderer->ChangeAnimation("Goomba_Dead");
	TotalVelocityVector = FVector::Zero;
}
