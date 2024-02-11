#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class UCollisionMap : public AActor
{
public:
	// constrcuter destructer
	UCollisionMap();
	~UCollisionMap();

	// delete Function
	UCollisionMap(const UCollisionMap& _Other) = delete;
	UCollisionMap(UCollisionMap&& _Other) noexcept = delete;
	UCollisionMap& operator=(const UCollisionMap& _Other) = delete;
	UCollisionMap& operator=(UCollisionMap&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

