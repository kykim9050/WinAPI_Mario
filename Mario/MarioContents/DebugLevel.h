#pragma once
#include <EngineCore/Level.h>

// Ό³Έν :
class UDebugLevel : public ULevel
{
public:
	// constrcuter destructer
	UDebugLevel();
	~UDebugLevel();

	// delete Function
	UDebugLevel(const UDebugLevel& _Other) = delete;
	UDebugLevel(UDebugLevel&& _Other) noexcept = delete;
	UDebugLevel& operator=(const UDebugLevel& _Other) = delete;
	UDebugLevel& operator=(UDebugLevel&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

