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