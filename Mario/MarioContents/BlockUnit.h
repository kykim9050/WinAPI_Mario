#pragma once
#include "StateUnit.h"
#include "PlayerMario.h"

// ���� :
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
	void CollisionCheck();
	void CollisionStateChange(ECollisionState _CollisionState);

	void IdleStart();
	void MoveStart();
	void GetHitStart();

	void Idle(float _DeltaTime);
	void Move(float _DeltaTime);
	void ResultMovementUpdate(float _DeltaTime);

	FVector InitPos = FVector::Zero;

private:

};

