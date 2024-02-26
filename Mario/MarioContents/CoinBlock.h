#pragma once
#include "BlockUnit.h"

// Ό³Έν :
class ACoinBlock : public ABlockUnit
{
public:
	// constrcuter destructer
	ACoinBlock();
	~ACoinBlock();

	// delete Function
	ACoinBlock(const ACoinBlock& _Other) = delete;
	ACoinBlock(ACoinBlock&& _Other) noexcept = delete;
	ACoinBlock& operator=(const ACoinBlock& _Other) = delete;
	ACoinBlock& operator=(ACoinBlock&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void IdleStart() override;
private:

};

