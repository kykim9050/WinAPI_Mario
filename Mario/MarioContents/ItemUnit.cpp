#include "ItemUnit.h"
#include "TextUnit.h"

AItemUnit::AItemUnit()
{
}

AItemUnit::~AItemUnit()
{
}

void AItemUnit::BeginPlay()
{
	AActor::BeginPlay();
}

void AItemUnit::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);

	CollisionCheck();
}

void AItemUnit::StateUpdate(float _DeltaTime)
{

	switch (ActorState)
	{
	case EActorState::FirstInit:
		FirstInit(_DeltaTime);
		break;
	case EActorState::Idle:
		Idle(_DeltaTime);
		break;
	case EActorState::Appear:
		Appear(_DeltaTime);
		break;
	case EActorState::Move:
		Move(_DeltaTime);
		break;
	default:
		break;
	}

}

void AItemUnit::StateChange(EActorState _ActorState)
{

	if (ActorState != _ActorState)
	{
		switch (_ActorState)
		{
		case EActorState::Idle:
			IdleStart();
			break;
		case EActorState::Appear:
			AppearStart();
			break;
		case EActorState::Move:
			MoveStart();
			break;
		case EActorState::Release:
			ReleaseStart();
			break;
		default:
			break;
		}
	}

	SetActorState(_ActorState);
}

void AItemUnit::CollisionStateChange(ECollisionState _CollisionState)
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

void AItemUnit::GetHitStart()
{
	BodyCollision->ActiveOff();
	StateChange(EActorState::Release);
}

void AItemUnit::ReleaseStart()
{
	//Destroy();
	Renderer->ActiveOff();
	AddActorLocation(FVector::Zero);
}

void AItemUnit::FirstInit(float _DeltaTime)
{
	InitPos = GetActorLocation();
}

void AItemUnit::ScoreImgOperator(FVector _InitPos, int _Score, float _DestoryTime)
{
	if (nullptr != Score)
	{
		MsgBoxAssert("�̹� Score �� �ֽ��ϴ�. Ȥ�� �������� �ʾҴ��� Ȯ���Ͻʽÿ�.");
		return;
	}

	// ���ھ� ������ ���� Ŭ���� ����
	Score = GetWorld()->SpawnActor<ATextUnit>(static_cast<int>(EActorType::ScoreImg));
	// ���ھ� �������� ���۵� ��ġ ����
	Score->SetLocation(_InitPos);
	// ���ھ� ���������� ����ϰ��� �ϴ� ���� ���
	Score->SetScoreAnimation(_Score);
	// ������ ���ÿ� ������ �ð� ����
	Score->Destroy(_DestoryTime);
	Score = nullptr;
}