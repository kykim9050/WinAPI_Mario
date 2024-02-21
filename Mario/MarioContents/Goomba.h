#pragma once
#include <EngineCore/Actor.h>
#include "EnumClass.h"
#include "InGameValue.h"
#include "ContentsFunction.h"


// Ό³Έν :
class AGoomba : public AActor
{
public:
	// constrcuter destructer
	AGoomba();
	~AGoomba();

	// delete Function
	AGoomba(const AGoomba& _Other) = delete;
	AGoomba(AGoomba&& _Other) noexcept = delete;
	AGoomba& operator=(const AGoomba& _Other) = delete;
	AGoomba& operator=(AGoomba&& _Other) noexcept = delete;

	void StateUpdate(float _DeltaTime);

	void SetActorState(const EPlayerState _State)
	{
		ActorState = _State;
	}

	void Move(float _DeltaTime);

	void ResultMovementUpdate(float _DeltaTime);

	void CollisionUpdate(float _DeltaTime);

	void CollisionStateChange(ECollisionState _CollisionState);

	void SetCollisionState(ECollisionState _CollisionState)
	{
		ActorCollisionState = _CollisionState;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImageRenderer* Renderer = nullptr;
	UCollision* BodyCollision = nullptr;

	EPlayerState ActorState = EPlayerState::None;
	ECollisionState ActorCollisionState = ECollisionState::None;

	FVector HorizonVelocityVector = FVector::Zero;
	FVector GravityVelocityVector = FVector::Zero;
	FVector TotalVelocityVector = FVector::Zero;

};

