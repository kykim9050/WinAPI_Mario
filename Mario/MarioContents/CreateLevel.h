#pragma once
#include "DebugLevel.h"

// Ό³Έν :
class UCreateLevel : public UDebugLevel
{
public:
	// constrcuter destructer
	UCreateLevel();
	~UCreateLevel();

	// delete Function
	UCreateLevel(const UCreateLevel& _Other) = delete;
	UCreateLevel(UCreateLevel&& _Other) noexcept = delete;
	UCreateLevel& operator=(const UCreateLevel& _Other) = delete;
	UCreateLevel& operator=(UCreateLevel&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

