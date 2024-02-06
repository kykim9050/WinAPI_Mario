#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class ATitleCoin : public AActor
{
public:
	// constrcuter destructer
	ATitleCoin();
	~ATitleCoin();

	// delete Function
	ATitleCoin(const ATitleCoin& _Other) = delete;
	ATitleCoin(ATitleCoin&& _Other) noexcept = delete;
	ATitleCoin& operator=(const ATitleCoin& _Other) = delete;
	ATitleCoin& operator=(ATitleCoin&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

