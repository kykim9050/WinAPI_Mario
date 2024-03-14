#pragma once
#include <EngineCore/Level.h>

class AGameOverUI;
// Ό³Έν :
class UGameOverLevel : public ULevel
{
public:
	// constrcuter destructer
	UGameOverLevel();
	~UGameOverLevel();

	// delete Function
	UGameOverLevel(const UGameOverLevel& _Other) = delete;
	UGameOverLevel(UGameOverLevel&& _Other) noexcept = delete;
	UGameOverLevel& operator=(const UGameOverLevel& _Other) = delete;
	UGameOverLevel& operator=(UGameOverLevel&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	AGameOverUI* GameOverUI = nullptr;
};

