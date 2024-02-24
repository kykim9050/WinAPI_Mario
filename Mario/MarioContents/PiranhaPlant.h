#pragma once
#include "MonsterUnit.h"

// Ό³Έν :
class APiranhaPlant : public UMonsterUnit
{
public:
	// constrcuter destructer
	APiranhaPlant();
	~APiranhaPlant();

	// delete Function
	APiranhaPlant(const APiranhaPlant& _Other) = delete;
	APiranhaPlant(APiranhaPlant&& _Other) noexcept = delete;
	APiranhaPlant& operator=(const APiranhaPlant& _Other) = delete;
	APiranhaPlant& operator=(APiranhaPlant&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:


};

