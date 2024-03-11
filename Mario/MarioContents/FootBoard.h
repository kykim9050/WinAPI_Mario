#pragma once
#include "MovingObjectUnit.h"


// Ό³Έν :
class AFootBoard : public AMovingObjectUnit
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

	void MoveStart() override;
	void FirstInit() override;
	void Idle(float _Deltatime) override;
	void Move(float _DeltaTime) override;

private:
	float MoveSpeed = 100.0f;
	FVector ActorMoveDir = FVector::Left;
};

