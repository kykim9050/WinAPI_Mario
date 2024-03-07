#pragma once
#include "BlockUnit.h"

// Ό³Έν :
class ABridgeBlock : public ABlockUnit
{
public:
	// constrcuter destructer
	ABridgeBlock();
	~ABridgeBlock();

	// delete Function
	ABridgeBlock(const ABridgeBlock& _Other) = delete;
	ABridgeBlock(ABridgeBlock&& _Other) noexcept = delete;
	ABridgeBlock& operator=(const ABridgeBlock& _Other) = delete;
	ABridgeBlock& operator=(ABridgeBlock&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

