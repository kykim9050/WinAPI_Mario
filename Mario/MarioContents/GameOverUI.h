#pragma once
#include "UIBaseInfo.h"

// Ό³Έν :
class AGameOverUI : public AUIBaseInfo
{
public:
	// constrcuter destructer
	AGameOverUI();
	~AGameOverUI();

	// delete Function
	AGameOverUI(const AGameOverUI& _Other) = delete;
	AGameOverUI(AGameOverUI&& _Other) noexcept = delete;
	AGameOverUI& operator=(const AGameOverUI& _Other) = delete;
	AGameOverUI& operator=(AGameOverUI&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

