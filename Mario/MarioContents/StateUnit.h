#pragma once
#include <EngineCore/Actor.h>
#include "EnumClass.h"
#include "ContentsFunction.h"
#include "InGameValue.h"

// Ό³Έν :
class UStateUnit : public AActor
{
public:
	// constrcuter destructer
	UStateUnit();
	virtual ~UStateUnit();

	// delete Function
	UStateUnit(const UStateUnit& _Other) = delete;
	UStateUnit(UStateUnit&& _Other) noexcept = delete;
	UStateUnit& operator=(const UStateUnit& _Other) = delete;
	UStateUnit& operator=(UStateUnit&& _Other) noexcept = delete;

	UCollision* GetBodyCollision() const
	{
		return BodyCollision;
	}

	UImageRenderer* GetRenderer() const
	{
		return Renderer;
	}

	const void SetJumpZero()
	{
		JumpVelocityVector = FVector::Zero;
	}

	const void SetGravityZero()
	{
		GravityVelocityVector = FVector::Zero;
	}

	const void SetGravityRatio(float _RatioValue)
	{
		GravityRatio = _RatioValue;
	}

	const void SetSpeedZero()
	{
		HorizonVelocityVector = FVector::Zero;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	virtual void IdleStart() {}
	virtual void MoveStart() {}
	virtual void JumpStart() {}
	virtual void GetHitStart() {}

	virtual void Idle(float _DeltaTime) {}
	virtual void Move(float _DeltaTime) {}
	virtual void Jump(float _DeltaTime) {}
	virtual void GetHit(float _DeltaTime) {}

	virtual void StateChange(EActorState _ActorState) {}
	virtual void StateUpdate(float _DeltaTime) {}
	void SetActorState(const EActorState _State)
	{
		ActorState = _State;
	}
	void SetActorDir(const EActorDir _Dir)
	{
		ActorDir = _Dir;
	}
	
	
	virtual void CollisionUpdate(float _DeltaTime);
	virtual void CollisionStateChange(ECollisionState _CollisionState) {}
	virtual void CollisionCheck() {}
	void SetCollisionState(ECollisionState _CollisionState)
	{
		ActorCollisionState = _CollisionState;
	}

	virtual void ResultMovementUpdate(float _DeltaTime) {}
	virtual void AddHorizonVelocityVector(const FVector& _DirDelta) {}
	virtual void ApplyMovement(float _DeltaTime) {}
	virtual void CalHorizonVelocityVector(float _DeltaTime) {}
	virtual void CalJumpVelocityVector(float _DeltaTime) {}

	virtual void CalGravityVelocityVector(float _DeltaTime) {}
	void CalTotalVelocityVector(float _DeltaTime);




	EActorState ActorState = EActorState::None;
	EActorDir ActorDir = EActorDir::Left;
	ECollisionState ActorCollisionState = ECollisionState::None;

	FVector HorizonVelocityVector = FVector::Zero;
	FVector GravityVelocityVector = FVector::Zero;
	FVector GravityAccVector = FVector::Down * 1500.0f;
	FVector TotalVelocityVector = FVector::Zero;
	FVector JumpVelocityVector = FVector::Zero;

	UImageRenderer* Renderer = nullptr;
	UCollision* BodyCollision = nullptr;
	std::string CurAnimationName = "None";

	float GravityRatio = 1.0f;

	int Life = 1;

private:
};

