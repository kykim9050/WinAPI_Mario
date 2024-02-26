#pragma once
#include "StateUnit.h"
#include "PlayerMario.h"

// Ό³Έν :
class ABlockUnit : public UStateUnit
{
public:
	// constrcuter destructer
	ABlockUnit();
	~ABlockUnit();

	// delete Function
	ABlockUnit(const ABlockUnit& _Other) = delete;
	ABlockUnit(ABlockUnit&& _Other) noexcept = delete;
	ABlockUnit& operator=(const ABlockUnit& _Other) = delete;
	ABlockUnit& operator=(ABlockUnit&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

