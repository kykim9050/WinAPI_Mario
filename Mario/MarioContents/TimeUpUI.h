#pragma once
#include "UIBaseInfo.h"

// Ό³Έν :
class ATimeUpUI : public AUIBaseInfo
{
public:
	// constrcuter destructer
	ATimeUpUI();
	~ATimeUpUI();

	// delete Function
	ATimeUpUI(const ATimeUpUI& _Other) = delete;
	ATimeUpUI(ATimeUpUI&& _Other) noexcept = delete;
	ATimeUpUI& operator=(const ATimeUpUI& _Other) = delete;
	ATimeUpUI& operator=(ATimeUpUI&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

