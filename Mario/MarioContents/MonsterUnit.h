#pragma once
#include "StateUnit.h"
#include "PlayerMario.h"

// Ό³Έν :
class AMonsterUnit : public UStateUnit
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

	void CalHorizonVelocityVector(float _DeltaTime) override;

	FVector ActorMoveDir = FVector::Left;

private:

};

