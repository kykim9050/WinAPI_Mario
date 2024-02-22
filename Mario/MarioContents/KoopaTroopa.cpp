#include "KoopaTroopa.h"
#include "PlayerMario.h"

AKoopaTroopa::AKoopaTroopa()
{
	GravityVelocityVector = FVector::Down * 500.0f;
	HorizonVelocityVector = FVector::Left * 50.0f;
	Life = 3;
}

AKoopaTroopa::~AKoopaTroopa()
{
}

void AKoopaTroopa::BeginPlay()
{
	UStateUnit::BeginPlay();

	Renderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::Monster));
	Renderer->SetImage("KoopaTroopa_Left.png");

	FVector KoopaTroopaScale = Renderer->GetImage()->GetScale();

	Renderer->SetTransform({ {0,0}, {KoopaTroopaScale.iX() / UInGameValue::KoopaTroopaImageXValue * UInGameValue::WindowSizeMulValue, KoopaTroopaScale.iY() / UInGameValue::KoopaTroopaImageYValue * UInGameValue::WindowSizeMulValue} });
	Renderer->CreateAnimation("KoopaTroopa_Right_Move", "KoopaTroopa_Right.png", 0, 1, 0.3f, true);
	Renderer->CreateAnimation("KoopaTroopa_Left_Move", "KoopaTroopa_Left.png", 0, 1, 0.3f, true);
	Renderer->CreateAnimation("KoopaTroopa_OneHit", "KoopaTroopa_Left.png", 5, 5, 0.1f, true);
	Renderer->CreateAnimation("KoopaTroopa_TwoHit", "KoopaTroopa_Left.png", 4, 4, 0.1f, true);

	Renderer->ChangeAnimation("KoopaTroopa_Left_Move");


	BodyCollision = CreateCollision(ECollisionOrder::Monster);
	BodyCollision->SetTransform({ { 0,0 }, { UInGameValue::KoopaTroopaBodyCollisionScaleX, UInGameValue::KoopaTroopaBodyCollisionScaleY} });
	BodyCollision->SetPosition({ 0, -(BodyCollision->GetTransform().GetScale().ihY()) });
	BodyCollision->SetColType(ECollisionType::Rect);

	SetActorState(EActorState::Move);
}

void AKoopaTroopa::Tick(float _DeltaTime)
{
	UStateUnit::Tick(_DeltaTime);

	CollisionUpdate(_DeltaTime);

	if (ECollisionState::GetHit == ActorCollisionState)
	{
		return;
	}

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
	default:
		break;
	}

}

void AKoopaTroopa::Move(float _DeltaTime)
{
	ResultMovementUpdate(_DeltaTime);
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

		if (PlayerBottom < MonsterBottom - OffsetYValue)
		{

			Player->StateChange(EActorState::CollisionJump);

			CollisionStateChange(ECollisionState::GetHit);

			// 만약 머리위를 때렸다면 GetHit로 ActorStateChange
			// GetHit에서는 라이프가 몇개인지에 따라서 2개면 그냥 거북모양으로 바꾸고 플레이어가 맞아도 죽지않게
			// 
			// 라이프가 1개면 이미 쳐서 돌아댕기는거니까 플레이어가 맞으면 죽도록 만들기
			// GetHitStart는 라이브에 따라서 다르게 작동되도록 만들기
			int a = 0;
			return;
		}

		// 만약 머리위를 떄리지 않았다면 Git로 ActorStateChange
		int a = 0;
		return;
	}
	
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
		default:
			break;
		}
	}

	SetCollisionState(_CollisionState);
}

void AKoopaTroopa::GetHitStart()
{
	UEngineDebug::OutPutDebugText("GetHitStart");
	--Life;

	switch (Life)
	{
	case 2: // Life가 2일 때 -> 플레이어한테 머리 한방 맞았을 때
	{
		Renderer->ChangeAnimation("KoopaTroopa_OneHit");
		StateChange(EActorState::GetFirstHit);
		break;
	}
	case 1:	// Life가 1일 때 -> 플레이어한테 한방 맞은 후에 또 맞았을 때 (밀거나 머리 맞거나)
	{
		Renderer->ChangeAnimation("KoopaTroopa_TwoHit");
		StateChange(EActorState::GetSecondHit);
		break;
	}
	default:
	{
		Life = 0;
		break;
	}
	}

}

void AKoopaTroopa::StateChange(EActorState _ActorState)
{
	if (ActorState != _ActorState)
	{
		switch (_ActorState)
		{
		case EActorState::GetFirstHit:
		{
			int a = 0;
			break;
		}
		case EActorState::GetSecondHit:
		{
			int a = 0;
			break;
		}
		default:
			break;
		}
	}

	SetActorState(_ActorState);
}