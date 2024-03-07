#pragma once
#include "BlockUnit.h"

// Ό³Έν :
class ACastleBridge : ABlockUnit
{
public:
	// constrcuter destructer
	ACastleBridge();
	~ACastleBridge();

	// delete Function
	ACastleBridge(const ACastleBridge& _Other) = delete;
	ACastleBridge(ACastleBridge&& _Other) noexcept = delete;
	ACastleBridge& operator=(const ACastleBridge& _Other) = delete;
	ACastleBridge& operator=(ACastleBridge&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

