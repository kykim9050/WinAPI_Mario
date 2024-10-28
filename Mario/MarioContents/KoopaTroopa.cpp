#include "KoopaTroopa.h"

AKoopaTroopa::AKoopaTroopa()
{
	GravityVelocityVector = FVector::Down * 500.0f;
	HorizonVelocityVector = ActorMoveDir * 50.0f;
	Life = 3;
	SetScore(100);
}

AKoopaTroopa::~AKoopaTroopa()
{
}

void AKoopaTroopa::BeginPlay()
{
	AMonsterUnit::BeginPlay();

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

	FootCollision = CreateCollision(ECollisionOrder::Monster);
	FootCollision->SetTransform({ { 0,0 }, {UInGameValue::KoopaTroopaBodyCollisionScaleX, UInGameValue::FootCollisionScaleY} });
	FootCollision->SetPosition({ 0, -(static_cast<int>(UInGameValue::FootCollisionScaleY / 2)) });
	FootCollision->SetColType(ECollisionType::Rect);

	SetActorState(EActorState::Idle);
}

void AKoopaTroopa::Tick(float _DeltaTime)
{
	AMonsterUnit::Tick(_DeltaTime);
}


void AKoopaTroopa::Idle(float _DeltaTime)
{
	if (GetActorLocation().iX() - GetPlayer()->GetActorLocation().iX() < UInGameValue::ResultMainWindowXScale)
	{
		StateChange(EActorState::Move);
	}
}


void AKoopaTroopa::Move(float _DeltaTime)
{
	EActorDir CurDir = ActorDir;
	CalHorizonVelocityVector(_DeltaTime);

	if (ActorDir != CurDir)
	{
		StateChange(EActorState::Idle);
		return;
	}

	HorizonVelocityVector = ActorMoveDir * 50.0f;
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
	HorizonVelocityVector = ActorMoveDir * 600.0f;
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
	AMonsterUnit::CalHorizonVelocityVector(_DeltaTime);
}

void AKoopaTroopa::MoveStart()
{
	if(EActorDir::Left == ActorDir)
	{
		Renderer->ChangeAnimation("KoopaTroopa_Move_Left");
		return;
	}

	if (EActorDir::Right == ActorDir)
	{
		Renderer->ChangeAnimation("KoopaTroopa_Move_Right");
		return;
	}

}

void AKoopaTroopa::GetFirstHitStart()
{
	USoundManager::GetInst().EffectSoundPlay("Stomp.wav");
	Renderer->ChangeAnimation("KoopaTroopa_OneHit");
	ScoreImgOperator({ GetActorLocation().iX(), GetActorLocation().iY() - BodyCollision->GetTransform().GetScale().iY() }, GetScore());
	GiveScore(GetPlayer());
}

void AKoopaTroopa::GetSecondHitStart()
{
	USoundManager::GetInst().EffectSoundPlay("CrouchMoveAttack.wav");
	SetDirAfterCollision(GetActorLocation(), APlayerMario::GetMainPlayer()->GetActorLocation());
	Renderer->ChangeAnimation("KoopaTroopa_TwoHit");
	ScoreImgOperator({ GetActorLocation().iX(), GetActorLocation().iY() - BodyCollision->GetTransform().GetScale().iY() }, SecondHitScore);
	GiveScore(GetPlayer(), SecondHitScore);
}

void AKoopaTroopa::GetHitFromMonsterStart()
{
	USoundManager::GetInst().EffectSoundPlay("CrouchMoveAttack.wav");
	ScoreImgOperator({ GetActorLocation().iX(), GetActorLocation().iY() - BodyCollision->GetTransform().GetScale().iY() }, GetMonsterHitScore());
	GiveScore(GetPlayer(), GetMonsterHitScore());
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

void AKoopaTroopa::CollisionCheck()
{
	std::vector<UCollision*> Result = std::vector<UCollision*>();


	if (true == BodyCollision->CollisionCheck(ECollisionOrder::Player, Result))
	{
		float PlayerBottom = GetPlayer()->GetBodyCollision()->GetActorBaseTransform().Bottom();
		float MonsterBottom = BodyCollision->GetActorBaseTransform().Bottom();

		// ���� ������ Collision ScaleY�� �ݰ���ŭ Player�� Bottom ���� ���� �մٸ� ���͸� ���� ��
		float OffsetYValue = BodyCollision->GetActorBaseTransform().GetScale().hY();

		// ������ �Ӹ��� �¾����� �����ϴ� ���
		if (PlayerBottom < MonsterBottom - OffsetYValue)
		{
			GetPlayer()->StateChange(EActorState::CollisionJump);

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
			GetPlayer()->StateChange(EActorState::GetHit);
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
	if (true == BodyCollision->CollisionCheck(ECollisionOrder::AttackableMonster, Result))
	{
		// GetHit�� Collision ������
		BodyCollision->Destroy();
		GiveScore(GetPlayer());

		CollisionStateChange(ECollisionState::GetMonsterHit);
		return;
	}

	CollisionStateChange(ECollisionState::None);
}


void AKoopaTroopa::GetHitStart()
{
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
