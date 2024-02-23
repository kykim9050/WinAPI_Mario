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
	{
		//GetFirstHit(_DeltaTime);
		int a = 0;
		break;
	}
	case EActorState::GetSecondHit:
	{
		//GetSecondHit(_DeltaTime);
		int a = 0;
		break;
	}
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

			// GetHit에서는 라이프가 몇개인지에 따라서 2개면 그냥 거북모양으로 바꾸고 플레이어가 맞아도 죽지않게
			// 라이프가 1개면 이미 쳐서 돌아댕기는거니까 플레이어가 맞으면 죽도록 만들기
			return;
		}

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
			// KoopaTroopa가 한번 맞아서 들어간 상태로 멈춰있을 때의 경우
			// 이때 플레이어가 발로찰 수 있기 때문에 CollisionState를 GetKick로 변경할 수 있을 것이다.
			// 그리고 GetKick이라는 상태에서는 플레이어의 어디에서 충돌했는지를 체크해서 해당 방향으로 날라가도록 구현
			// GetKick상태에서는 다른 몬스터, 플레이어 전부다 죽일 수 있음 (다른 몬스터들은 Koopatroopa의 충돌을 체크해야 함)
			// 해당 상태는 옆에서 밀었을때만 해당되는 상태
			int a = 0;
			break;
		}
		default:
			break;
		}
		// 만약 머리위를 떄리지 않았다면 Git로 ActorStateChange
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
		StateChange(EActorState::GetFirstHit);
		break;
	case 1:	// Life가 1일 때 -> 플레이어한테 한방 맞은 후에 또 맞았을 때 (밀거나 머리 맞거나)
		StateChange(EActorState::GetSecondHit);
		break;
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
			GetFirstHitStart();
			break;
		case EActorState::GetSecondHit:
			GetSecondHitStart();
			break;
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
	Renderer->ChangeAnimation("KoopaTroopa_TwoHit");
}