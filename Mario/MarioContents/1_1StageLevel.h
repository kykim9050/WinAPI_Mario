#pragma once
#include "StageLevel.h"

// Ό³Έν :
class U1_1StageLevel : public UStageLevel
{
public:
	// constrcuter destructer
	U1_1StageLevel();
	~U1_1StageLevel();

	// delete Function
	U1_1StageLevel(const U1_1StageLevel& _Other) = delete;
	U1_1StageLevel(U1_1StageLevel&& _Other) noexcept = delete;
	U1_1StageLevel& operator=(const U1_1StageLevel& _Other) = delete;
	U1_1StageLevel& operator=(U1_1StageLevel&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

