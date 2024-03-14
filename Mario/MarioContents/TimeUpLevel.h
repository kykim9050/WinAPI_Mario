#pragma once
#include <EngineCore/Level.h>

class ATimeUpUI;
// Ό³Έν :
class UTimeUpLevel : public ULevel
{
public:
	// constrcuter destructer
	UTimeUpLevel();
	~UTimeUpLevel();

	// delete Function
	UTimeUpLevel(const UTimeUpLevel& _Other) = delete;
	UTimeUpLevel(UTimeUpLevel&& _Other) noexcept = delete;
	UTimeUpLevel& operator=(const UTimeUpLevel& _Other) = delete;
	UTimeUpLevel& operator=(UTimeUpLevel&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void ReturnToStage(float _DeltaTime);

private:
	ATimeUpUI* TimeUpUI = nullptr;
};

