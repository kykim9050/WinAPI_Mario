#pragma once
#include "CreateLevel.h"

// Ό³Έν :
class UTestLevel : public UCreateLevel
{
public:
	// constrcuter destructer
	UTestLevel();
	~UTestLevel();

	// delete Function
	UTestLevel(const UTestLevel& _Other) = delete;
	UTestLevel(UTestLevel&& _Other) noexcept = delete;
	UTestLevel& operator=(const UTestLevel& _Other) = delete;
	UTestLevel& operator=(UTestLevel&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

