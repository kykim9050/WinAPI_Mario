#pragma once
#include "StructureUnit.h"

// Ό³Έν :
class APipe : public AStructureUnit
{
public:
	// constrcuter destructer
	APipe();
	~APipe();

	// delete Function
	APipe(const APipe& _Other) = delete;
	APipe(APipe&& _Other) noexcept = delete;
	APipe& operator=(const APipe& _Other) = delete;
	APipe& operator=(APipe&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

