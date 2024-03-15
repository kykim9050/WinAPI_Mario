#include "BulletUnit.h"

ABulletUnit::ABulletUnit()
{
}

ABulletUnit::~ABulletUnit()
{
}

void ABulletUnit::BeginPlay()
{
	UStateUnit::BeginPlay();
}

void ABulletUnit::Tick(float _DeltaTime)
{
	UStateUnit::Tick(_DeltaTime);


}

void ABulletUnit::StateUpdate(float _DeltaTime)
{
	switch (ActorState)
	{
	case EActorState::FirstInit:
		FirstInit(_DeltaTime);
		break;
	case EActorState::Move:
		Move(_DeltaTime);
		break;
	case EActorState::FallDown:
		FallDown(_DeltaTime);
		break;
	case EActorState::Explosion:
		Explosion(_DeltaTime);
		break;
	default:
		break;
	}
}

void ABulletUnit::StateChange(EActorState _ActorState)
{
	if (ActorState != _ActorState)
	{
		switch (_ActorState)
		{
		case EActorState::Move:
			MoveStart();
			break;
		case EActorState::FallDown:
			FallDownStart();
			break;
		case EActorState::Explosion:
			ExplosionStart();
			break;
		default:
			break;
		}
	}

	SetActorState(_ActorState);
}

void ABulletUnit::FirstInit(float _DeltaTime)
{
	if (IsBulletFire())
	{
		StateChange(EActorState::Move);
		return;
	}
}
