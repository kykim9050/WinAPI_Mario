#pragma once
#include "StructureUnit.h"

// Ό³Έν :
class AEndFlag : public AStructureUnit
{
public:
	// constrcuter destructer
	AEndFlag();
	~AEndFlag();

	// delete Function
	AEndFlag(const AEndFlag& _Other) = delete;
	AEndFlag(AEndFlag&& _Other) noexcept = delete;
	AEndFlag& operator=(const AEndFlag& _Other) = delete;
	AEndFlag& operator=(AEndFlag&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void CollisionCheck() override;

private:
	UImageRenderer* FlagRenderer = nullptr;
	int ActorBaseFlagXPos = -9 * UInGameValue::WindowSizeMulValue;
	int ActorBaseFlagYPos = -67 * UInGameValue::WindowSizeMulValue;
};

