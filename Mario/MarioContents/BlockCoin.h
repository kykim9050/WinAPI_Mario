#pragma once
#include "ItemUnit.h"

// Ό³Έν :
class ABlockCoin : public AItemUnit
{
public:
	// constrcuter destructer
	ABlockCoin();
	~ABlockCoin();

	// delete Function
	ABlockCoin(const ABlockCoin& _Other) = delete;
	ABlockCoin(ABlockCoin&& _Other) noexcept = delete;
	ABlockCoin& operator=(const ABlockCoin& _Other) = delete;
	ABlockCoin& operator=(ABlockCoin&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

