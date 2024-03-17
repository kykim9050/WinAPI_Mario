#pragma once
#include <EngineCore/Actor.h>

class UImageRenderer;
// Ό³Έν :
class AManual : public AActor
{
public:
	// constrcuter destructer
	AManual();
	~AManual();

	// delete Function
	AManual(const AManual& _Other) = delete;
	AManual(AManual&& _Other) noexcept = delete;
	AManual& operator=(const AManual& _Other) = delete;
	AManual& operator=(AManual&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void ManualDisplayCheck();
	
	UImageRenderer* ManualRenderer = nullptr;
	bool ManualDIsplay = false;
};

