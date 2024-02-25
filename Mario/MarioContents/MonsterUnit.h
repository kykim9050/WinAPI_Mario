#pragma once
#include "StateUnit.h"
#include "PlayerMario.h"

// ���� :
class UMonsterUnit : public UStateUnit
{
public:
	// constrcuter destructer
	UMonsterUnit();
	~UMonsterUnit();

	// delete Function
	UMonsterUnit(const UMonsterUnit& _Other) = delete;
	UMonsterUnit(UMonsterUnit&& _Other) noexcept = delete;
	UMonsterUnit& operator=(const UMonsterUnit& _Other) = delete;
	UMonsterUnit& operator=(UMonsterUnit&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void CalHorizonVelocityVector(float _DeltaTime) override;

	FVector ActorMoveDir = FVector::Left;
	bool KillPlayer = false;

private:

};

