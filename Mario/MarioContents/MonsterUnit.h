#pragma once
#include "StateUnit.h"

// Ό³Έν :
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

	FVector ActorMoveDir = FVector::Left;

private:

};

