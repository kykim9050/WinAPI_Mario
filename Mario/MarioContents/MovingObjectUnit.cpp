﻿#include "MovingObjectUnit.h"

AMovingObjectUnit::AMovingObjectUnit()
{
}

AMovingObjectUnit::~AMovingObjectUnit()
{
}

void AMovingObjectUnit::BeginPlay()
{
	UStateUnit::BeginPlay();
}

void AMovingObjectUnit::Tick(float _DeltaTime)
{
	UStateUnit::Tick(_DeltaTime);
}

void AMovingObjectUnit::StateUpdate(float _DeltaTime)
{
	switch (ActorState)
	{
	case EActorState::FirstInit:
		FirstInit();
		break;
	case EActorState::Idle:
		Idle(_DeltaTime);
		break;
	case EActorState::Move:
		Move(_DeltaTime);
		break;
	case EActorState::Rotating:
		Rotating(_DeltaTime);
		break;
	default:
		break;
	}
}

void AMovingObjectUnit::StateChange(EActorState _ActorState)
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
		case EActorState::Rotating:
			RotatingStart();
			break;
		default:
			break;
		}
	}

	SetActorState(_ActorState);
}

