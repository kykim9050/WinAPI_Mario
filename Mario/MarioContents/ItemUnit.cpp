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
		MsgBoxAssert("이미 Score 가 있습니다. 혹은 정리되지 않았는지 확인하십시오.");
		return;
	}

	// 스코어 랜더러 관련 클래스 생성
	Score = GetWorld()->SpawnActor<ATextUnit>(static_cast<int>(EActorType::ScoreImg));
	// 스코어 랜더러가 시작될 위치 지정
	Score->SetLocation(_InitPos);
	// 스코어 랜더러에서 출력하고자 하는 점수 출력
	Score->SetScoreAnimation(_Score);
	// 생성과 동시에 삭제될 시간 지정
	Score->Destroy(_DestoryTime);
	Score = nullptr;
}