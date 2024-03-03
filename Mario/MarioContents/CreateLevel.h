#pragma once
#include <EngineCore/Level.h>

// Ό³Έν :
class UCreateLevel : public ULevel
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

private:

};

