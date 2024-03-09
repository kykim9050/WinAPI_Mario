#pragma once
#include "StateUnit.h"
#include "MainPlayer.h"

// Ό³Έν :
class AFootBoard : public UStateUnit, public UMainPlayer
{
public:
	// constrcuter destructer
	AFootBoard();
	~AFootBoard();

	// delete Function
	AFootBoard(const AFootBoard& _Other) = delete;
	AFootBoard(AFootBoard&& _Other) noexcept = delete;
	AFootBoard& operator=(const AFootBoard& _Other) = delete;
	AFootBoard& operator=(AFootBoard&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void StateUpdate(float _DeltaTime);
	void StateChange(EActorState _ActorState);

	void MoveStart() override;
	void Idle(float _Deltatime) override;
	void Move(float _DeltaTime) override;

private:
	FVector InitPos = FVector::Zero;

	float MoveSpeed = 100.0f;
	FVector ActorMoveDir = FVector::Left;
};

