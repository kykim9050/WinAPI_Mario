#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class AGoomba : public AActor
{
public:
	// constrcuter destructer
	AGoomba();
	~AGoomba();

	// delete Function
	AGoomba(const AGoomba& _Other) = delete;
	AGoomba(AGoomba&& _Other) noexcept = delete;
	AGoomba& operator=(const AGoomba& _Other) = delete;
	AGoomba& operator=(AGoomba&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

