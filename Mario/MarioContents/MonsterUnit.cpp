#include "MonsterUnit.h"
#include "TextUnit.h"
#include "MarioBullet.h"

AMonsterUnit::AMonsterUnit()
{
}

AMonsterUnit::~AMonsterUnit()
{
}

void AMonsterUnit::BeginPlay()
{
	UStateUnit::BeginPlay();
}

void AMonsterUnit::Tick(float _DeltaTime)
{
	UStateUnit::Tick(_DeltaTime);
}

void AMonsterUnit::CalHorizonVelocityVector(float _DeltaTime)
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
		switch (ActorDir)
		{
		case EActorDir::Right:
		{
			ActorDir = EActorDir::Left;
			ActorMoveDir = FVector::Left;
			break;
		}
		case EActorDir::Left:
		{
			ActorDir = EActorDir::Right;
			ActorMoveDir = FVector::Right;
			break;
		}
		default:
			break;
		}
	}
}

void AMonsterUnit::StateUpdate(float _DeltaTime)
{
	switch (ActorState)
	{
	case EActorState::FirstInit:
		FirstInit(_DeltaTime);
		break;
	case EActorState::Idle:
		Idle(_DeltaTime);
		break;
	case EActorState::Move:
		Move(_DeltaTime);
		break;
	case EActorState::Jump:
		Jump(_DeltaTime);
		break;
	case EActorState::FallDown:
		FallDown(_DeltaTime);
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
	case EActorState::Fire:
		Fire(_DeltaTime);
		break;
	case EActorState::GetHit:
	default:
		break;
	}

}

void AMonsterUnit::StateChange(EActorState _ActorState)
{
	if (ActorState != _ActorState)
	{
		switch (_ActorState)
		{
		case EActorState::Idle:
			IdleStart();
			break;
		case EActorState::Move:
			MoveStart();
			break;
		case EActorState::Jump:
			JumpStart();
			break;
		case EActorState::GetFirstHit:
			GetFirstHitStart();
			break;
		case EActorState::GetSecondHit:
			GetSecondHitStart();
			break;
		case EActorState::GetHit:
			GetHitFromPlayerStart();
			break;
		case EActorState::GetMonsterHit:
			GetHitFromMonsterStart();
			break;
		case EActorState::Fire:
			FireStart();
			break;
		case EActorState::FallDown:
			FallDownStart();
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

void AMonsterUnit::CollisionStateChange(ECollisionState _CollisionState)
{
	if (ActorCollisionState != _CollisionState)
	{
		switch (_CollisionState)
		{
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

void AMonsterUnit::DeadCollisionCheck()
{
	UStateUnit::DeadCollisionCheck();
	
	if (true == IsMonsterDead())
	{
		return;
	}

	Color8Bit Color = UContentsFunction::GetCollisionMapImg()->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), UInGameValue::CollisionColor);

	if (Color8Bit::YellowA == Color)
	{
		SetMonsterDead();
		Destroy(1.0f);
	}
}

void AMonsterUnit::CalGravityVelocityVector(float _DeltaTime)
{
	std::vector<UCollision*> Result = std::vector<UCollision*>();
	Color8Bit Color = UContentsFunction::GetCollisionMapImg()->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), UInGameValue::CollisionColor);

	if (false == MonsterDead && UInGameValue::CollisionColor == Color || true == FootCollision->CollisionCheck(ECollisionOrder::BlockTop, Result))
	{
		GravityVelocityVector = FVector::Zero;
		SetGravityRatio(0.0f);
	}
	else
	{
		SetGravityRatio(0.5f);
	}

	GravityVelocityVector += GravityAccVector * _DeltaTime * GravityRatio;
}

void AMonsterUnit::ResultMovementUpdate(float _DeltaTime)
{
	CalGravityVelocityVector(_DeltaTime);
	CalTotalVelocityVector(_DeltaTime);
	AddActorLocation(TotalVelocityVector * _DeltaTime);
}

void AMonsterUnit::ScoreImgOperator(FVector _InitPos, int _Score, float _DestoryTime)
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

bool AMonsterUnit::PlayerBulletHitCheck()
{
	std::vector<UCollision*> Result = std::vector<UCollision*>();

	if (true == BodyCollision->CollisionCheck(ECollisionOrder::PlayerBullet, Result))
	{
		AMarioBullet* PlayerBullet = dynamic_cast<AMarioBullet*>(Result[0]->GetOwner());

		if (nullptr == PlayerBullet)
		{
			MsgBoxAssert("해당 변수의 본래 자료형이 아닙니다.");
			return false;
		}

		PlayerBullet->KillMonster();
		BodyCollision->Destroy();
		CollisionStateChange(ECollisionState::GetMonsterHit);
		return true;
	}
	return false;
}