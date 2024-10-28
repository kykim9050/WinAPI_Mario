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
		MsgBoxAssert("�÷��̾ �������� �ʽ��ϴ�.");
	}

	if (false == KillPlayer && true == BodyCollision->CollisionCheck(ECollisionOrder::Player, Result))
	{
		float PlayerBottom = Player->GetBodyCollision()->GetActorBaseTransform().Bottom();
		float MonsterBottom = BodyCollision->GetActorBaseTransform().Bottom();

		// ���� ������ Collision ScaleY�� �ݰ���ŭ Player�� Bottom ���� ���� �մٸ� ���͸� ���� ��
		float OffsetYValue = BodyCollision->GetActorBaseTransform().GetScale().hY();

		if (PlayerBottom < MonsterBottom - OffsetYValue)
		{

			Player->StateChange(EActorState::CollisionJump);

			CollisionStateChange(ECollisionState::GetHit);

			// ���� �Ӹ����� ���ȴٸ� GetHit�� ActorStateChange
			// GetHit������ �������� ������� ���� 2���� �׳� �źϸ������ �ٲٰ� �÷��̾ �¾Ƶ� �����ʰ�
			// 
			// �������� 1���� �̹� �ļ� ���ƴ��°Ŵϱ� �÷��̾ ������ �׵��� �����
			// GetHitStart�� ���̺꿡 ���� �ٸ��� �۵��ǵ��� �����
			int a = 0;
			return;
		}

		// ���� �Ӹ����� ������ �ʾҴٸ� Git�� ActorStateChange
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
	case 2: // Life�� 2�� �� -> �÷��̾����� �Ӹ� �ѹ� �¾��� ��
	{
		Renderer->ChangeAnimation("KoopaTroopa_OneHit");
		StateChange(EActorState::GetFirstHit);
		break;
	}
	case 1:	// Life�� 1�� �� -> �÷��̾����� �ѹ� ���� �Ŀ� �� �¾��� �� (�аų� �Ӹ� �°ų�)
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