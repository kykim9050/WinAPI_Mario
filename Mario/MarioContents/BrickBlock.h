#pragma once
#include "BlockUnit.h"

// Ό³Έν :
class ABrickBlock : public ABlockUnit
{
public:
	// constrcuter destructer
	ABrickBlock();
	~ABrickBlock();

	// delete Function
	ABrickBlock(const ABrickBlock& _Other) = delete;
	ABrickBlock(ABrickBlock&& _Other) noexcept = delete;
	ABrickBlock& operator=(const ABrickBlock& _Other) = delete;
	ABrickBlock& operator=(ABrickBlock&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void StateUpdate(float _DeltaTime) override;
	void StateChange(EActorState _ActorState) override;
	void CollisionCheck() override;
	void CollisionStateChange(ECollisionState _CollisionState) override;

	void IdleStart() override;
	void MoveStart() override;
	void GetHitStart() override;

	void Idle(float _DeltaTime) override;
	void Move(float _DeltaTime) override;

	void ResultMovementUpdate(float _DeltaTime);

private:

};

