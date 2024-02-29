#include "ItemUnit.h"

AItemUnit::AItemUnit()
{
}

AItemUnit::~AItemUnit()
{
}

void AItemUnit::BeginPlay()
{
	//AActor::BeginPlay();
	UStateUnit::BeginPlay();


	Renderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::Item));
	Renderer->SetImage("Coin.png");

	FVector ItemScale = Renderer->GetImage()->GetScale();

	Renderer->SetTransform({ {0,0}, {ItemScale.iX() / UInGameValue::CoinImageXValue, ItemScale.iY() / UInGameValue::CoinImageYValue} });
	Renderer->CreateAnimation("Rotating_Coin", "Coin.png", 0, 3, 0.1f, true);
	Renderer->ChangeAnimation("Rotating_Coin");

	StateChange(EActorState::Idle);
}

void AItemUnit::Tick(float _DeltaTime)
{
	//AActor::Tick(_DeltaTime);
	UStateUnit::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);

}

void AItemUnit::StateUpdate(float _DeltaTime)
{
	switch (ActorState)
	{
	case EActorState::Idle:
		Idle(_DeltaTime);
		break;
	/*case EActorState::Move:
		Move(_DeltaTime);
		break;*/
	default:
		break;
	}

}


void AItemUnit::StateChange(EActorState _ActorState)
{
	if (ActorState != _ActorState)
	{
		//switch (_ActorState)
		//{
		//case EActorState::Move:
		//	MoveStart();
		//	break;
		//case EActorState::GetFirstHit:
		//	GetFirstHitStart();
		//	break;
		//case EActorState::GetSecondHit:
		//	GetSecondHitStart();
		//	break;
		//case EActorState::GetMonsterHit:
		//	GetHitFromMonsterStart();
		//	break;
		//case EActorState::Dead:
		//	Destroy();
		//	return;
		//default:
		//	break;
		//}
	}

	SetActorState(_ActorState);
}