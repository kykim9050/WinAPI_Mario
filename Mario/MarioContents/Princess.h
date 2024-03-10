#pragma once
#include "StateUnit.h"

// Ό³Έν :
class APrincess : public UStateUnit
{
public:
	// constrcuter destructer
	APrincess();
	~APrincess();

	// delete Function
	APrincess(const APrincess& _Other) = delete;
	APrincess(APrincess&& _Other) noexcept = delete;
	APrincess& operator=(const APrincess& _Other) = delete;
	APrincess& operator=(APrincess&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

