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
	//CalHorizonVelocityVector(_DeltaTime);
	ResultMovementUpdate(_DeltaTime);
}

void AKoopaTroopa::GetFirstHit(float _DeltaTime)
{
	HorizonVelocityVector = FVector::Zero;
	ResultMovementUpdate(_DeltaTime);
}

void AKoopaTroopa::GetSecondHit(float _DeltaTime)
{
	HorizonVelocityVector = FVector::Right * 500.0f;
	CalHorizonVelocityVector(_DeltaTime);
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
	FVector CheckPos = GetActorLocation();
	CheckPos.Y -= UInGameValue::ColOffSetY;

	switch (ActorDir)
	{
	case EActorDir::Right:
		CheckPos.X += UInGameValue::ColOffSetX;
		break;
	case EActorDir::Left:
		CheckPos.X -= UInGameValue::ColOffSetX;
		break;
	default:
		break;
	}

	Color8Bit Color = UContentsFunction::GetCollisionMapImg()->GetColor(CheckPos.iX(), CheckPos.iY(), UInGameValue::CollisionColor);

	if (Color == UInGameValue::CollisionColor)
	{
		HorizonVelocityVector = FVector::Zero;
	}
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
	Renderer->ChangeAnimation("KoopaTroopa_TwoHit");
}

void AKoopaTroopa::GetHitFromMonsterStart()
{

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
		MsgBoxAssert("�÷��̾ �������� �ʽ��ϴ�.");
	}

	if (false == KillPlayer && true == BodyCollision->CollisionCheck(ECollisionOrder::Player, Result))
	{
		float PlayerBottom = Player->GetBodyCollision()->GetActorBaseTransform().Bottom();
		float MonsterBottom = BodyCollision->GetActorBaseTransform().Bottom();

		// ���� ������ Collision ScaleY�� �ݰ���ŭ Player�� Bottom ���� ���� �մٸ� ���͸� ���� ��
		float OffsetYValue = BodyCollision->GetActorBaseTransform().GetScale().hY();

		// ������ �Ӹ��� �¾����� �����ϴ� ���
		if (PlayerBottom < MonsterBottom - OffsetYValue)
		{
			Player->StateChange(EActorState::CollisionJump);

			CollisionStateChange(ECollisionState::GetHit);

			return;
		}

		// ���ݾ����� �Ӹ����� �ƴ� ������ �浹�� �Ͼ�� ��
		switch (Life)
		{
		case 1:
		case 3:
		{
			// KoopaTroopa�� ������� �� Ȥ�� ����� ����ٴҶ� �浹�� ���
			// �̶��� �÷��̾� ����ؾ� ��
			Player->StateChange(EActorState::GetHit);
			// �÷��̾ �׿���.
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
	
	// ���� ���ݾ����� �����ٴҶ� �浹�ϸ� �浹�� ����
	if (false == KillPlayer && true == BodyCollision->CollisionCheck(ECollisionOrder::AttackableMonster, Result))
	{
		// GetHit�� Collision ������
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
	case 3: // Life�� 3�ε� �÷��̾����� �Ӹ� �ѹ� �¾��� ��
	{
		StateChange(EActorState::GetFirstHit);
		--Life;
		break;
	}
	case 2:	// Life�� 2�� �� -> �÷��̾����� �ѹ� ���� �Ŀ� �� �¾��� �� (�аų� �Ӹ� �°ų��ϴ� �ൿ ���� �� ����)
	{
		// GetSecondHit���¿����� �ٸ� ����, �÷��̾� ���δ� ���� �� ���� (�ٸ� ���͵��� Koopatroopa�� �浹�� üũ�ؾ� ��)
		StateChange(EActorState::GetSecondHit);

		// �ٸ� ���͵鵵 ���� �� �ֵ��� Order�� ECollisionOrder::AttackableMonster�� ����
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







