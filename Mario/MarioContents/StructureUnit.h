#pragma once
#include "StateUnit.h"

// Ό³Έν :
class AStructureUnit : public UStateUnit
{
public:
	// constrcuter destructer
	AStructureUnit();
	~AStructureUnit();

	// delete Function
	AStructureUnit(const AStructureUnit& _Other) = delete;
	AStructureUnit(AStructureUnit&& _Other) noexcept = delete;
	AStructureUnit& operator=(const AStructureUnit& _Other) = delete;
	AStructureUnit& operator=(AStructureUnit&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

