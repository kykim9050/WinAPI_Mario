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
	//case EActorState::Move:
	//	Move(_DeltaTime);
	//	break;
	default:
		break;
	}
}

void ABulletUnit::StateChange(EActorState _ActorState)
{
	//if (ActorState != _ActorState)
	//{
	//	switch (_ActorState)
	//	{
	//	//case EActorState::Move:
	//	//	MoveStart();
	//	//	break;
	//	default:
	//		break;
	//	}
	//}

	SetActorState(_ActorState);
}
