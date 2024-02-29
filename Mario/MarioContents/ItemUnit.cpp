#include "ItemUnit.h"

AItemUnit::AItemUnit()
{
}

AItemUnit::~AItemUnit()
{
}

void AItemUnit::BeginPlay()
{
	AActor::BeginPlay();


	Renderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::Item));
	Renderer->SetImage("Coin.png");

	FVector ItemScale = Renderer->GetImage()->GetScale();

	Renderer->SetTransform({ {0,0}, {ItemScale.iX() / UInGameValue::CoinImageXValue, ItemScale.iY() / UInGameValue::CoinImageYValue} });
	Renderer->CreateAnimation("Rotating_Coin", "Coin.png", 0, 3, 0.05f, true);
	Renderer->ChangeAnimation("Rotating_Coin");

	StateChange(EActorState::Idle);
}

void AItemUnit::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void AItemUnit::StateUpdate(float _DeltaTime)
{

	switch (ActorState)
	{
	case EActorState::Idle:
		Idle(_DeltaTime);
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


void AItemUnit::Idle(float _DeltaTime)
{

}

void AItemUnit::Move(float _DeltaTime)
{
	// 동전의 경우
	CoinRenderingTime -= _DeltaTime;

	if (false == RenderingEnd && 0.0f >= CoinRenderingTime)
	{
		RenderingEnd = true;
		GravityVelocityVector = FVector::Zero;
		JumpVelocityVector = FVector::Zero;
		StateChange(EActorState::Release);
	}

	GravityVelocityVector += GravityAccVector * _DeltaTime;
	CalTotalVelocityVector(_DeltaTime);
	AddActorLocation(TotalVelocityVector * _DeltaTime);

}

void AItemUnit::IdleStart()
{
	Renderer->ActiveOff();
}

void AItemUnit::MoveStart()
{
	JumpVelocityVector = FVector::Up * 600.0f;
	Renderer->ActiveOn();
}

void AItemUnit::ReleaseStart()
{
	// 랜더링만 Destroy
	// 액터 자체를 Destory하면 BlockUnit에서 사용할 수가 없음
	Renderer->Destroy();
}