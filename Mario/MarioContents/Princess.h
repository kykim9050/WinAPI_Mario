#pragma once
#include "StateUnit.h"
#include "MainPlayer.h"

class UImageRenderer;
// Ό³Έν :
class APrincess : public UStateUnit , public UMainPlayer
{
public:
	// constrcuter destructer
	APrincess();
	~APrincess();

	// delete Function
	APrincess(const APrincess& _Other) = delete;
	APrincess(APrincess&& _Other) noexcept = delete;
	APrincess& operator=(const APrincess& _Other) = delete;
	APrincess& operator=(APrincess&& _Other) noexcept = delete;

	static void PrintEndingMsg()
	{
		PrintMsg = true;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void CollisionCheck() override;

private:
	UImageRenderer* MessageHideRenderer = nullptr;

	static bool PrintMsg;
	bool IsCanPrintMsg() const
	{
		return PrintMsg;
	}
};

