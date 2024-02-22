#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class UStateUnit : public AActor
{
public:
	// constrcuter destructer
	UStateUnit();
	~UStateUnit();

	// delete Function
	UStateUnit(const UStateUnit& _Other) = delete;
	UStateUnit(UStateUnit&& _Other) noexcept = delete;
	UStateUnit& operator=(const UStateUnit& _Other) = delete;
	UStateUnit& operator=(UStateUnit&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

