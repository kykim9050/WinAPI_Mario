#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class ATextUnit : public AActor
{
public:
	// constrcuter destructer
	ATextUnit();
	~ATextUnit();

	// delete Function
	ATextUnit(const ATextUnit& _Other) = delete;
	ATextUnit(ATextUnit&& _Other) noexcept = delete;
	ATextUnit& operator=(const ATextUnit& _Other) = delete;
	ATextUnit& operator=(ATextUnit&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

