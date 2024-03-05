#pragma once
#include "StateUnit.h"
#include "PlayerMario.h"
#include "ItemUnit.h"

// Ό³Έν :
class ABlockUnit : public UStateUnit
{
public:
	// constrcuter destructer
	ABlockUnit();
	~ABlockUnit();

	// delete Function
	ABlockUnit(const ABlockUnit& _Other) = delete;
	ABlockUnit(ABlockUnit&& _Other) noexcept = delete;
	ABlockUnit& operator=(const ABlockUnit& _Other) = delete;
	ABlockUnit& operator=(ABlockUnit&& _Other) noexcept = delete;

	virtual void FirstInit(float _Deltatime);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void StateUpdate(float _DeltaTime);
	void StateChange(EActorState _ActorState);
	void CollisionStateChange(ECollisionState _CollisionState);
	virtual void CollisionCheck() {}

	virtual void IdleStart() { }
	virtual void MoveStart();
	virtual void FixedStart() { }
	virtual void DebrisStart() {	}
	virtual void GetHitStart() { }

	void Idle(float _DeltaTime);
	virtual void Move(float _DeltaTime);
	void Fixed(float _DeltaTime);
	virtual void Debris(float _DeltaTime) { }
	virtual void Wait(float _DeltaTime) {	}
	void ResultMovementUpdate(float _DeltaTime);

	FVector InitPos = FVector::Zero;

	UCollision* SideCollision = nullptr;
	UCollision* TopCollision = nullptr;
	APlayerMario* Player = nullptr;

private:

	const int ColInitXPos = 0;
	const int ColInitYPos = 16;
	const int ColXoffset = 8;
	const int ColYoffset = 32;
	const int SideColYoffset = 8;


};

