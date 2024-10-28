#pragma once
#include "StateUnit.h"
#include "PlayerMario.h"
#include "MainPlayer.h"

// ���� :
class AMonsterUnit : public UStateUnit, public UMainPlayer
{
public:
	// constrcuter destructer
	AMonsterUnit();
	~AMonsterUnit();

	// delete Function
	AMonsterUnit(const AMonsterUnit& _Other) = delete;
	AMonsterUnit(AMonsterUnit&& _Other) noexcept = delete;
	AMonsterUnit& operator=(const AMonsterUnit& _Other) = delete;
	AMonsterUnit& operator=(AMonsterUnit&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void StateUpdate(float _DeltaTime) override;
	//void CollisionUpdate(float _DeltaTime);

	virtual void FirstInit(float _DeltaTime) {};
	virtual void Idle(float _DeltaTime) {};
	virtual void Move(float _DeltaTime) {};
	virtual void GetFirstHit(float _DeltaTime) {};
	virtual void GetSecondHit(float _DeltaTime) {};
	virtual void GetMonsterHit(float _DeltaTime) {};

	void CalHorizonVelocityVector(float _DeltaTime) override;

	FVector ActorMoveDir = FVector::Left;

private:

};

