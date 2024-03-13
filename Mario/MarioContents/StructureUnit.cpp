#include "StructureUnit.h"

AStructureUnit::AStructureUnit()
{
}

AStructureUnit::~AStructureUnit()
{
}

void AStructureUnit::BeginPlay()
{
	UStateUnit::BeginPlay();
}

void AStructureUnit::Tick(float _DeltaTime)
{
	UStateUnit::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);

	CollisionCheck();
}

void AStructureUnit::StateUpdate(float _DeltaTime)
{
	switch (ActorState)
	{
	case EActorState::FallDown:
		FallDown(_DeltaTime);
		break;
	case EActorState::ReachingEndFlag:
		ReachingEndFlag(_DeltaTime);
		break;
	case EActorState::Appear:
		Appear(_DeltaTime);
		break;
	default:
		break;
	}

}

void AStructureUnit::StateChange(EActorState _ActorState)
{
	if (ActorState != _ActorState)
	{
		switch (_ActorState)
		{
		case EActorState::FallDown:
			FallDownStart();
			break;
		case EActorState::ReachingEndFlag:
			ReachingEndFlagStart();
			break;
		case EActorState::Appear:
			AppearStart();
			break;
		default:
			break;
		}
	}

	SetActorState(_ActorState);
}
