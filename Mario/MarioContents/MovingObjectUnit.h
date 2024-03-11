#pragma once
#include "StateUnit.h"
#include "MainPlayer.h"

// Ό³Έν :
class AMovingObjectUnit : public UStateUnit, public UMainPlayer
{
public:
	// constrcuter destructer
	AMovingObjectUnit();
	~AMovingObjectUnit();

	// delete Function
	AMovingObjectUnit(const AMovingObjectUnit& _Other) = delete;
	AMovingObjectUnit(AMovingObjectUnit&& _Other) noexcept = delete;
	AMovingObjectUnit& operator=(const AMovingObjectUnit& _Other) = delete;
	AMovingObjectUnit& operator=(AMovingObjectUnit&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	virtual void StateUpdate(float _DeltaTime);
	virtual void StateChange(EActorState _ActorState);

	virtual void MoveStart() {};
	virtual void Idle(float _Deltatime) {};
	virtual void Move(float _DeltaTime) {};
	virtual void FirstInit() {};

	FVector InitPos = FVector::Zero;

private:

};

